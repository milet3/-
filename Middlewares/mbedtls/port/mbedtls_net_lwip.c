#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "lwip/api.h"
#include "lwip/dns.h"
#include "lwip/tcp.h"
#include <string.h>

typedef struct {
    struct netconn *conn;
    ip_addr_t remote_ip;
    volatile int dns_done;
} netconn_tls_ctx_t;

static netconn_tls_ctx_t g_ctx;

static void dns_cb(const char *name, const ip_addr_t *ipaddr, void *arg)
{
    netconn_tls_ctx_t *ctx = (netconn_tls_ctx_t *)arg;
    if (ipaddr) {
        ctx->remote_ip = *ipaddr;
        ctx->dns_done = 1;
    } else {
        ctx->dns_done = -1;
    }
}

int netconn_tls_connect(const char *host, uint16_t port)
{
    err_t err;
    g_ctx.dns_done = 0;
    err = dns_gethostbyname(host, &g_ctx.remote_ip, dns_cb, &g_ctx);
    if (err == ERR_INPROGRESS) {
        while (g_ctx.dns_done == 0) {
            sys_msleep(10);
        }
    }
    if (g_ctx.dns_done < 0) {
        return -1;
    }

    g_ctx.conn = netconn_new(NETCONN_TCP);
    if (!g_ctx.conn) {
        return -1;
    }    err = netconn_connect(g_ctx.conn, &g_ctx.remote_ip, port);
    if (err != ERR_OK) {
        netconn_delete(g_ctx.conn);
        g_ctx.conn = NULL;
        return -1;
    }
    return 0;
}

void netconn_tls_disconnect(void)
{
    if (g_ctx.conn) {
        netconn_close(g_ctx.conn);
        netconn_delete(g_ctx.conn);
        g_ctx.conn = NULL;
    }
}

static int netconn_tls_send(void *ctx, const unsigned char *buf, size_t len)
{
    netconn_tls_ctx_t *c = (netconn_tls_ctx_t *)ctx;
    if (c->conn == NULL) {
        return MBEDTLS_ERR_NET_SEND_FAILED;
    }

    err_t err = netconn_write(c->conn, buf, len, NETCONN_COPY | NETCONN_MORE);
    if (err == ERR_OK) {
        return (int)len;
    }
    if (err == ERR_TIMEOUT) {
        return MBEDTLS_ERR_SSL_WANT_WRITE;
    }
    return MBEDTLS_ERR_NET_SEND_FAILED;
}

static int netconn_tls_recv(void *ctx, unsigned char *buf, size_t len)
{
    netconn_tls_ctx_t *c = (netconn_tls_ctx_t *)ctx;
    struct netbuf *nb = NULL;
    if (c->conn == NULL) {
        return MBEDTLS_ERR_NET_RECV_FAILED;
    }

    err_t err = netconn_recv(c->conn, &nb);
    if (err == ERR_TIMEOUT) {
        return MBEDTLS_ERR_SSL_WANT_READ;
    }
    if (err == ERR_CLSD || err == ERR_RST) {
        return MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY;
    }
    if (err != ERR_OK) {
        return MBEDTLS_ERR_NET_RECV_FAILED;
    }

    size_t total = netbuf_len(nb);
    size_t copy = (len < total) ? len : total;
    netbuf_copy(nb, buf, copy);
    netbuf_delete(nb);
    return (int)copy;
}

void netconn_tls_bind_bio(mbedtls_ssl_context *ssl)
{
    mbedtls_ssl_set_bio(ssl, &g_ctx,
                        netconn_tls_send, netconn_tls_recv, NULL);
}
