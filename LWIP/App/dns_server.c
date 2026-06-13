/**
 * @file dns_server.c
 * @brief DNS Server + HTTP Server (Netconn API)
 *
 * Both servers run in their own FreeRTOS tasks using Netconn API
 * for thread safety.
 */

#include "dns_server.h"
#include "lwip/api.h"
#include "lwip/prot/dns.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "cmsis_os.h"
#include "task.h"
#include <string.h>
#include <stdio.h>

#define DNS_SERVER_PORT     53
#define HTTP_SERVER_PORT    80

static volatile int dns_running = 0;
static volatile int http_running = 0;

/* ========== DNS Server ========== */

static u16_t dns_name_len(const u8_t *name)
{
    u16_t len = 0;
    while (*name != 0) {
        u8_t label_len = *name;
        if ((label_len & 0xC0) == 0xC0) {
            return len + 2;
        }
        len += label_len + 1;
        name += label_len + 1;
    }
    return len + 1;
}

static void dns_server_task(void *arg)
{
    (void)arg;
    err_t err;
    struct netbuf *buf;
    void *data;
    u16_t len;

    struct netconn *conn = netconn_new(NETCONN_UDP);
    if (conn == NULL) {
        printf("[DNS] Failed to create netconn\r\n");
        dns_running = 0;
        vTaskDelete(NULL);
        return;
    }

    err = netconn_bind(conn, IP_ADDR_ANY, DNS_SERVER_PORT);
    if (err != ERR_OK) {
        printf("[DNS] Failed to bind port %d, err=%d\r\n", DNS_SERVER_PORT, err);
        netconn_delete(conn);
        dns_running = 0;
        vTaskDelete(NULL);
        return;
    }

    printf("[DNS] Server started on port %d\r\n", DNS_SERVER_PORT);

    while (dns_running) {
        err = netconn_recv(conn, &buf);
        if (err != ERR_OK) continue;

        netbuf_data(buf, &data, &len);
        if (len < SIZEOF_DNS_HDR) { netbuf_delete(buf); continue; }

        struct dns_hdr *query_hdr = (struct dns_hdr *)data;
        if ((query_hdr->flags1 & DNS_FLAG1_RESPONSE) != 0) { netbuf_delete(buf); continue; }
        if (lwip_ntohs(query_hdr->numquestions) < 1) { netbuf_delete(buf); continue; }

        const ip4_addr_t *device_ip = netif_ip4_addr(netif_default);
        if (device_ip == NULL || ip4_addr_isany(device_ip)) { netbuf_delete(buf); continue; }

        const u8_t *qname = (const u8_t *)query_hdr + SIZEOF_DNS_HDR;
        u16_t qname_len = dns_name_len(qname);
        u16_t resp_len = SIZEOF_DNS_HDR + qname_len + 4 + 2 + 2 + 2 + 4 + 2 + 4;

        struct netbuf *resp_buf = netbuf_new();
        if (resp_buf == NULL) { netbuf_delete(buf); continue; }

        void *resp_data = netbuf_alloc(resp_buf, resp_len);
        if (resp_data == NULL) { netbuf_delete(resp_buf); netbuf_delete(buf); continue; }

        u8_t *rbuf = (u8_t *)resp_data;
        u16_t offset = 0;

        struct dns_hdr *resp_hdr = (struct dns_hdr *)rbuf;
        resp_hdr->id           = query_hdr->id;
        resp_hdr->flags1       = DNS_FLAG1_RESPONSE | DNS_FLAG1_RD;
        resp_hdr->flags2       = DNS_FLAG2_ERR_NONE;
        resp_hdr->numquestions = lwip_htons(1);
        resp_hdr->numanswers   = lwip_htons(1);
        resp_hdr->numauthrr    = 0;
        resp_hdr->numextrarr   = 0;
        offset = SIZEOF_DNS_HDR;

        memcpy(&rbuf[offset], qname, qname_len);
        offset += qname_len;
        rbuf[offset++] = (DNS_RRTYPE_A >> 8) & 0xFF; rbuf[offset++] = DNS_RRTYPE_A & 0xFF;
        rbuf[offset++] = (DNS_RRCLASS_IN >> 8) & 0xFF; rbuf[offset++] = DNS_RRCLASS_IN & 0xFF;

        rbuf[offset++] = 0xC0 | ((SIZEOF_DNS_HDR >> 8) & 0x3F);
        rbuf[offset++] = SIZEOF_DNS_HDR & 0xFF;
        rbuf[offset++] = (DNS_RRTYPE_A >> 8) & 0xFF; rbuf[offset++] = DNS_RRTYPE_A & 0xFF;
        rbuf[offset++] = (DNS_RRCLASS_IN >> 8) & 0xFF; rbuf[offset++] = DNS_RRCLASS_IN & 0xFF;
        rbuf[offset++] = 0; rbuf[offset++] = 0; rbuf[offset++] = 0; rbuf[offset++] = 60;
        rbuf[offset++] = 0; rbuf[offset++] = 4;
        memcpy(&rbuf[offset], &device_ip->addr, 4);

        netconn_connect(conn, netbuf_fromaddr(buf), netbuf_fromport(buf));
        netconn_send(conn, resp_buf);
        printf("[DNS] Query -> %s\r\n", ip4addr_ntoa(device_ip));

        netbuf_delete(resp_buf);
        netbuf_delete(buf);
    }

    netconn_delete(conn);
    dns_running = 0;
    vTaskDelete(NULL);
}

/* ========== HTTP Server ========== */

static const char http_response[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html>\r\n"
    "<html lang=\"zh\">\r\n"
    "<head>\r\n"
    "<meta charset=\"UTF-8\">\r\n"
    "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\r\n"
    "<title>STM32F407 Dashboard</title>\r\n"
    "<style>\r\n"
    "*{margin:0;padding:0;box-sizing:border-box}\r\n"
    "body{min-height:100vh;display:flex;align-items:center;justify-content:center;background:#0f172a;background-image:radial-gradient(ellipse at 50% 0%,#1e3a5f 0%,#0f172a 70%);font-family:system-ui,-apple-system,sans-serif;padding:20px}\r\n"
    ".c{width:100%;max-width:420px;background:rgba(30,41,59,.85);backdrop-filter:blur(10px);border-radius:20px;border:1px solid rgba(100,116,139,.3);padding:40px 32px;box-shadow:0 25px 60px rgba(0,0,0,.4)}\r\n"
    ".h{text-align:center;margin-bottom:32px}\r\n"
    ".h h1{color:#f8fafc;font-size:1.6rem;font-weight:700;letter-spacing:-.5px}\r\n"
    ".h .l{width:48px;height:3px;background:linear-gradient(90deg,#3b82f6,#8b5cf6);border-radius:2px;margin:12px auto 0}\r\n"
    ".s{display:flex;align-items:center;justify-content:center;gap:10px;padding:14px;background:rgba(34,197,94,.1);border:1px solid rgba(34,197,94,.2);border-radius:12px;margin-bottom:24px}\r\n"
    ".s .d{width:10px;height:10px;background:#22c55e;border-radius:50%;box-shadow:0 0 12px rgba(34,197,94,.6);animation:p 2s ease-in-out infinite}\r\n"
    "@keyframes p{0%,100%{opacity:1;transform:scale(1)}50%{opacity:.5;transform:scale(.85)}}\r\n"
    ".s span{color:#86efac;font-size:.9rem;font-weight:500}\r\n"
    ".i{display:flex;flex-direction:column;gap:14px}\r\n"
    ".r{display:flex;justify-content:space-between;align-items:center;padding:12px 16px;background:rgba(15,23,42,.5);border-radius:10px;border:1px solid rgba(51,65,85,.5)}\r\n"
    ".r .k{color:#94a3b8;font-size:.82rem}\r\n"
    ".r .v{color:#e2e8f0;font-size:.88rem;font-weight:600;font-family:ui-monospace,monospace}\r\n"
    ".f{text-align:center;margin-top:28px;padding-top:20px;border-top:1px solid rgba(71,85,105,.4);color:#64748b;font-size:.75rem}\r\n"
    "</style>\r\n"
    "</head>\r\n"
    "<body>\r\n"
    "<div class=\"c\">\r\n"
    "<div class=\"h\"><h1>STM32F407VET6</h1><div class=\"l\"></div></div>\r\n"
    "<div class=\"s\"><div class=\"d\"></div><span>System Running</span></div>\r\n"
    "<div class=\"i\">\r\n"
    "<div class=\"r\"><span class=\"k\">Platform</span><span class=\"v\">LwIP + FreeRTOS</span></div>\r\n"
    "<div class=\"r\"><span class=\"k\">Service</span><span class=\"v\">HTTP Server :80</span></div>\r\n"
    "<div class=\"r\"><span class=\"k\">Network</span><span class=\"v\">Ethernet DHCP</span></div>\r\n"
    "</div>\r\n"
    "<div class=\"f\">Powered by STM32 &bull; LwIP HTTP Server</div>\r\n"
    "</div>\r\n"
    "</body>\r\n"
    "</html>\r\n"
    ;

static void http_server_task(void *arg)
{
    (void)arg;
    err_t err;
    struct netconn *conn, *newconn;
    struct netbuf *buf;
    void *data;
    u16_t len;

    conn = netconn_new(NETCONN_TCP);
    if (conn == NULL) {
        printf("[HTTP] Failed to create netconn\r\n");
        http_running = 0;
        vTaskDelete(NULL);
        return;
    }

    err = netconn_bind(conn, IP_ADDR_ANY, HTTP_SERVER_PORT);
    if (err != ERR_OK) {
        printf("[HTTP] Failed to bind port %d, err=%d\r\n", HTTP_SERVER_PORT, err);
        netconn_delete(conn);
        http_running = 0;
        vTaskDelete(NULL);
        return;
    }

    netconn_listen(conn);
    printf("[HTTP] Server started on port %d\r\n", HTTP_SERVER_PORT);

    while (http_running) {
        err = netconn_accept(conn, &newconn);
        if (err != ERR_OK) continue;

        printf("[HTTP] Client connected\r\n");

        err = netconn_recv(newconn, &buf);
        if (err == ERR_OK) {
            netbuf_data(buf, &data, &len);
            /* Check if it's a GET request */
            if (len >= 3 && memcmp(data, "GET", 3) == 0) {
                netconn_write(newconn, http_response, sizeof(http_response) - 1, NETCONN_COPY);
                printf("[HTTP] Served page\r\n");
            }
            netbuf_delete(buf);
        }

        netconn_close(newconn);
        netconn_delete(newconn);
    }

    netconn_delete(conn);
    http_running = 0;
    vTaskDelete(NULL);
}

/* ========== Public API ========== */

void dns_server_start(void)
{
    if (dns_running) return;
    dns_running = 1;
    osThreadAttr_t attr = {
        .name = "dns_srv",
        .stack_size = 512 * 4,
        .priority = (osPriority_t) osPriorityBelowNormal,
    };
    osThreadNew(dns_server_task, NULL, &attr);
}

void dns_server_stop(void)
{
    dns_running = 0;
}

void http_server_start(void)
{
    if (http_running) return;
    http_running = 1;
    osThreadAttr_t attr = {
        .name = "http_srv",
        .stack_size = 512 * 4,
        .priority = (osPriority_t) osPriorityBelowNormal,
    };
    osThreadNew(http_server_task, NULL, &attr);
}

void http_server_stop(void)
{
    http_running = 0;
}
