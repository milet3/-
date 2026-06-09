#include "TCP_ECHO.h"
#include "lwip/api.h"
#include "lwip/err.h"
#include "lwip/dhcp.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

#define ECHO_SERVER_PORT 7
#define ECHO_BUFFER_SIZE 1024

void lwip_echo_task(void *pvParameters)
{
  struct netconn *conn, *newconn;
  struct netbuf *buf;
  char *data;
  u16_t len;
  err_t err;

  // 1. ���� TCP ����
  conn = netconn_new(NETCONN_TCP);
  if (conn == NULL)
  {
    printf("Failed to create netconn\n");
    vTaskDelete(NULL);
    return;
  }

  // 2. �󶨶˿�
  err = netconn_bind(conn, IP_ADDR_ANY, ECHO_SERVER_PORT);
  if (err != ERR_OK)
  {
    printf("netconn_bind failed: %d\n", err);
    netconn_delete(conn);
    vTaskDelete(NULL);
    return;
  }

  // 3. ��������
  err = netconn_listen(conn);
  if (err != ERR_OK)
  {
    printf("netconn_listen failed: %d\n", err);
    netconn_delete(conn);
    vTaskDelete(NULL);
    return;
  }
  printf("ECHO server is listening on port %d\n", ECHO_SERVER_PORT);

  while (1)
  {
    // 4�������ȴ��ͻ�������
    err = netconn_accept(conn, &newconn);
    if (err != ERR_OK)
    {
      printf("netconn_accept failed: %d\n", err);
      continue; // �����ȴ���һ������
    }

    // 5���������ݲ�����
    printf("Client connected\r\n");

    do
    {
      // 6��������������
      err = netconn_recv(newconn, &buf);
      if (err != ERR_OK)
      {
        printf("netconn_recv failed: %d\n", err);
        break; // �˳�����ѭ�����ر�����
      }
      // 7����ȡ����ָ��ͳ���
      netbuf_data(buf, (void **)&data, &len);

      // 8����������
      if (len > 0)
      {
        err = netconn_write(newconn, data, len, NETCONN_COPY);
        if (err != ERR_OK)
        {
          printf("netconn_write failed: %d\n", err);
          break; // �˳�����ѭ�����ر�����
        }
      }
      // 9���ͷŽ��ջ�����
      netbuf_delete(buf);

    } while (err == ERR_OK);
    // 10���ر�����
    printf("Client disconnected\r\n");
    netconn_close(newconn);
    netconn_delete(newconn);
  }
}

void tcp_echo_socket_task(void *arg)
{
  int listen_fd, client_fd;
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  char buf[ECHO_BUFFER_SIZE];
  int len;

  // 1. ���� TCP socket
  listen_fd = lwip_socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd < 0)
  {
    printf("Failed to create socket\n");
    vTaskDelete(NULL);
    return;
  }

  // 2. �󶨶˿�
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = lwip_htons(ECHO_SERVER_PORT);

  if (lwip_bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    printf("Failed to bind socket\n");
    lwip_close(listen_fd);
    vTaskDelete(NULL);
    return;
  }

  // 3. ��������
  if (lwip_listen(listen_fd, 1) < 0)
  {
    printf("Failed to listen on socket\n");
    lwip_close(listen_fd);
    vTaskDelete(NULL);
    return;
  }
  printf("ECHO server is listening on port %d\n", ECHO_SERVER_PORT);

  while (1)
  {
    // 4����������
    client_fd = lwip_accept(listen_fd, (struct sockaddr *)&addr, &addr_len);
    if (client_fd < 0)
    {
      printf("Failed to accept connection\n");
      continue; // �����ȴ���һ������
    }
    printf("Client connected\r\n");

    // 5���������ݲ�����
    while ((len = lwip_recv(client_fd, buf, sizeof(buf), 0)) > 0)
    {
      lwip_send(client_fd, buf, len, 0);
    }
    printf("Client disconnected\r\n");
    lwip_close(client_fd);
  }
}

void start_dhcp(struct netif *netif)
{
  err_t err;

  // 1������Ĭ��IP��ַ����ѡ��DHCP�Ḳ������
  IP4_ADDR(&netif->ip_addr, 0, 0, 0, 0);
  IP4_ADDR(&netif->netmask, 0, 0, 0, 0);
  IP4_ADDR(&netif->gw, 0, 0, 0, 0);

  // 2������ DHCP �ͻ���
  err = dhcp_start(netif);
  if (err != ERR_OK)
  {
    printf("Failed to start DHCP: %d\n", err);
    return;
  }

  printf("DHCP client started for %c%c%d, waiting for IP address...\r\n",
         netif->name[0], netif->name[1], netif->num);
}

// DHCP ״̬�������
void dhcp_monitor_task(void *arg)
{
  struct netif *netif = (struct netif *)arg;
  uint8_t got_ip = 0;

  printf("[DHCP] Waiting for IP address...\r\n");

  while (1)
  {
    if (dhcp_supplied_address(netif))
    {
      if (!got_ip)
      {
        got_ip = 1;
        printf("[DHCP] Got IP:  %s\r\n", ip4addr_ntoa(netif_ip4_addr(netif)));
        printf("[DHCP] Mask:    %s\r\n", ip4addr_ntoa(netif_ip4_netmask(netif)));
        printf("[DHCP] Gateway: %s\r\n", ip4addr_ntoa(netif_ip4_gw(netif)));
      }
    }
    else
    {
      if (got_ip)
      {
        got_ip = 0;
        printf("[DHCP] IP lost, waiting for new lease...\r\n");
      }
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
