#ifndef TCP_ECHO_H
#define TCP_ECHO_H

#include "lwip/err.h"
#include "lwip/sockets.h"

void lwip_echo_task(void *pvParameters);
void tcp_echo_socket_task(void *arg);

#endif /* TCP_ECHO_H */
