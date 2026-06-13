/**
 * @file dns_server.h
 * @brief DNS Server + HTTP Server for lwIP (Netconn API)
 */

#ifndef __DNS_SERVER_H__
#define __DNS_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

void dns_server_start(void);
void dns_server_stop(void);
void http_server_start(void);
void http_server_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* __DNS_SERVER_H__ */
