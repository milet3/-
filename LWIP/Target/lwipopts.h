/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : Target/lwipopts.h
  * Description        : This file overrides LwIP stack default configuration
  *                      done in opt.h file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __LWIPOPTS__H__
#define __LWIPOPTS__H__

#include "main.h"

/*-----------------------------------------------------------------------------*/
/* Current version of LwIP supported by CubeMx: 2.1.2 -*/
/*-----------------------------------------------------------------------------*/

/* Within 'USER CODE' section, code will be kept by default at each generation */
/* USER CODE BEGIN 0 */

/* ==================== 锟节达拷锟斤拷锟斤拷锟?==================== */
/* pbuf 锟结构锟斤拷兀锟矫匡拷锟?TCP/UDP 锟秸凤拷锟斤拷锟斤拷要一锟斤拷 pbuf 锟结构锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟捷★拷
   默锟斤拷 16锟斤拷锟斤拷锟角碉拷锟斤拷协锟介并锟斤拷锟斤拷HTTP+MQTT+锟斤拷锟斤拷锟斤拷锟接ｏ拷锟斤拷16 锟斤拷锟矫★拷
   锟斤拷锟斤拷时锟结报 ERR_MEM锟斤拷症状锟斤拷锟铰斤拷锟斤拷锟斤拷失锟杰★拷 */
#define MEMP_NUM_PBUF            16

/* TCP 锟斤拷锟接匡拷锟狡匡拷(PCB)锟斤拷锟斤拷锟斤拷每锟斤拷 TCP 锟斤拷锟接讹拷要占锟斤拷一锟斤拷 PCB锟斤拷
   默锟斤拷只锟斤拷 4锟斤拷锟斤拷锟斤拷锟揭?HTTP Server + MQTT Client + 锟斤拷锟斤拷锟斤拷锟接ｏ拷锟斤拷锟皆匡拷 8锟斤拷
   锟斤拷锟斤拷时 tcp_new() 锟斤拷锟斤拷 NULL锟斤拷锟斤拷锟斤拷为锟睫凤拷锟铰斤拷锟斤拷锟接★拷 */
#define MEMP_NUM_TCP_PCB         8

/* TCP 锟斤拷锟侥讹拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?锟窖凤拷锟酵碉拷未确锟较碉拷 TCP 锟斤拷锟侥段★拷
   默锟斤拷 16锟斤拷锟竭诧拷锟斤拷锟斤拷锟斤拷时锟斤拷木锟斤拷锟矫匡拷锟?tcp_write 锟斤拷锟斤拷锟斤拷锟侥憋拷锟侥段★拷
   锟斤拷锟斤拷时 tcp_write() 锟斤拷锟斤拷 ERR_MEM锟斤拷锟斤拷锟捷凤拷锟斤拷锟斤拷去锟斤拷锟斤拷锟斤拷锟筋常锟斤拷锟斤拷瓶锟斤拷锟斤拷 */
#define MEMP_NUM_TCP_SEG         32

/* pbuf 锟斤拷锟捷筹拷锟斤拷锟斤拷锟斤拷每锟斤拷 pbuf 锟接筹拷锟叫凤拷锟斤拷一锟斤拷潭锟斤拷锟叫★拷诖妫拷锟叫★拷锟?PBUF_POOL_BUFSIZE锟斤拷锟斤拷
   默锟斤拷 16锟斤拷一锟姐够锟矫★拷锟竭诧拷锟斤拷锟斤拷锟斤拷时锟斤拷要锟斤拷锟接★拷
   锟斤拷锟斤拷时 pbuf_alloc(PBUF_POOL) 锟斤拷锟斤拷 NULL锟斤拷锟秸帮拷失锟杰★拷 */
#define PBUF_POOL_SIZE           16

/* ==================== TCP 锟斤拷锟斤拷 ==================== */
/* TCP 锟斤拷锟秸达拷锟节达拷小锟斤拷锟斤拷示一锟斤拷锟杰斤拷锟秸讹拷锟斤拷锟街节碉拷锟斤拷锟捷★拷
   默锟斤拷 2*TCP_MSS = 2920 锟街节ｏ拷锟斤拷锟教★拷锟斤拷锟斤拷锟斤拷贫苑锟斤拷锟斤拷锟斤拷锟斤拷剩锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷喜锟饺ワ拷锟?
   锟斤拷为 4*TCP_MSS = 5840 锟街节ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟皆革拷锟狡★拷
   注锟解：锟斤拷锟斤拷越锟斤拷每锟斤拷锟斤拷锟斤拷占锟矫碉拷 RAM 越锟洁（锟斤拷锟斤拷锟斤拷锟捷达拷锟斤拷 MEM_SIZE 锟斤）锟斤拷 */
#define TCP_WND                  (4 * TCP_MSS)

/* TCP Keep-Alive 锟斤拷锟斤拷锟斤拷疲锟斤拷锟斤拷涌锟斤拷锟绞憋拷锟斤拷锟教斤拷锟斤拷锟斤拷锟斤拷锟皆讹拷锟角否还伙拷锟脚★拷
   0=锟截闭ｏ拷默锟较ｏ拷锟斤拷1=锟斤拷锟斤拷锟斤拷
   MQTT 锟斤拷锟斤拷锟接憋拷锟诫开锟斤拷锟斤拷锟斤拷锟斤拷 WiFi/锟斤拷锟竭断匡拷锟斤拷 STM32 锟斤拷知锟斤拷锟斤拷锟斤拷一直占锟斤拷 PCB 锟斤拷锟酵放★拷
   探锟斤拷锟斤拷锟斤拷 TCP_KEEPIDLE锟斤拷2小时锟斤拷锟斤拷TCP_KEEPINTVL锟斤拷75锟诫）锟斤拷TCP_KEEPCNT锟斤拷9锟轿ｏ拷锟斤拷锟狡★拷
   锟斤拷 lwipopts.h 锟阶诧拷锟斤拷锟皆革拷锟斤拷些值锟斤拷也锟斤拷锟斤拷锟斤拷默锟较的★拷 */
#define LWIP_TCP_KEEPALIVE       1

/* ==================== 锟斤拷锟斤拷锟斤拷统锟斤拷 ==================== */
/* 统锟斤拷锟斤拷息锟斤拷示锟斤拷锟斤拷 stats_display() 锟斤拷锟斤拷锟矫ｏ拷锟斤拷锟皆达拷印锟斤拷锟斤拷锟秸凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷诖锟绞癸拷玫取锟?
   锟节匡拷锟斤拷锟节达拷锟斤拷诺锟斤拷锟侥匡拷锟斤拷锟斤拷 stats_display() 锟斤拷锟斤拷印锟斤拷锟斤拷锟较拷锟斤拷邪锟斤拷锟斤拷锟?
   锟斤拷锟斤拷锟芥本锟斤拷锟斤拷乇锟斤拷锟轿?0锟斤拷锟斤拷锟皆斤拷省一锟斤拷 RAM锟斤拷 */
/* LWIP_STATS_DISPLAY handled by opt.h since LWIP_STATS=0 */

/* USER CODE END 0 */
/* USER CODE END 0 */

#ifdef __cplusplus
 extern "C" {
#endif

/* STM32CubeMX Specific Parameters (not defined in opt.h) ---------------------*/
/* Parameters set in STM32CubeMX LwIP Configuration GUI -*/
/*----- WITH_RTOS enabled (Since FREERTOS is set) -----*/
#define WITH_RTOS 1
/*----- CHECKSUM_BY_HARDWARE disabled for stability test -----*/
#define CHECKSUM_BY_HARDWARE 0
/*-----------------------------------------------------------------------------*/

/* LwIP Stack Parameters (modified compared to initialization value in opt.h) -*/
/* Parameters set in STM32CubeMX LwIP Configuration GUI -*/
/*----- Value in opt.h for LWIP_DHCP: 0 -----*/
#define LWIP_DHCP 1
/*----- Default Value for LWIP_DNS: 0 ---*/
#define LWIP_DNS 1
/*----- Value in opt.h for MEM_ALIGNMENT: 1 -----*/
#define MEM_ALIGNMENT 4
/*----- Default Value for MEM_SIZE: 1600 ---*/
#define MEM_SIZE 32000
/*----- Default Value for MEMP_NUM_TCP_PCB_LISTEN: 8 ---*/
#define MEMP_NUM_TCP_PCB_LISTEN 10
/*----- Default Value for PBUF_POOL_BUFSIZE: 592 ---*/
#define PBUF_POOL_BUFSIZE 1524
/*----- Value in opt.h for LWIP_ETHERNET: LWIP_ARP || PPPOE_SUPPORT -*/
#define LWIP_ETHERNET 1
/*----- Value in opt.h for LWIP_DNS_SECURE: (LWIP_DNS_SECURE_RAND_XID | LWIP_DNS_SECURE_NO_MULTIPLE_OUTSTANDING | LWIP_DNS_SECURE_RAND_SRC_PORT) -*/
#define LWIP_DNS_SECURE 7
/*----- Default Value for TCP_MSS: 536 ---*/
#define TCP_MSS 1460
/*----- Default Value for TCP_SND_BUF: 2920 ---*/
#define TCP_SND_BUF 5840
/*----- Default Value for TCP_SND_QUEUELEN: 17 ---*/
#define TCP_SND_QUEUELEN 8
/*----- Value in opt.h for TCP_SNDQUEUELOWAT: LWIP_MAX(TCP_SND_QUEUELEN)/2, 5) -*/
#define TCP_SNDQUEUELOWAT 5
/*----- Value in opt.h for LWIP_NETIF_LINK_CALLBACK: 0 -----*/
#define LWIP_NETIF_LINK_CALLBACK 1
/*----- Value in opt.h for TCPIP_THREAD_STACKSIZE: 0 -----*/
#define TCPIP_THREAD_STACKSIZE 1024
/*----- Value in opt.h for TCPIP_THREAD_PRIO: 1 -----*/
#define TCPIP_THREAD_PRIO 24
/*----- Value in opt.h for TCPIP_MBOX_SIZE: 0 -----*/
#define TCPIP_MBOX_SIZE 32
/*----- Value in opt.h for SLIPIF_THREAD_STACKSIZE: 0 -----*/
#define SLIPIF_THREAD_STACKSIZE 1024
/*----- Value in opt.h for SLIPIF_THREAD_PRIO: 1 -----*/
#define SLIPIF_THREAD_PRIO 3
/*----- Value in opt.h for DEFAULT_THREAD_STACKSIZE: 0 -----*/
#define DEFAULT_THREAD_STACKSIZE 1024
/*----- Value in opt.h for DEFAULT_THREAD_PRIO: 1 -----*/
#define DEFAULT_THREAD_PRIO 3
/*----- Value in opt.h for DEFAULT_UDP_RECVMBOX_SIZE: 0 -----*/
#define DEFAULT_UDP_RECVMBOX_SIZE 16
/*----- Value in opt.h for DEFAULT_TCP_RECVMBOX_SIZE: 0 -----*/
#define DEFAULT_TCP_RECVMBOX_SIZE 16
/*----- Value in opt.h for DEFAULT_ACCEPTMBOX_SIZE: 0 -----*/
#define DEFAULT_ACCEPTMBOX_SIZE 16
/*----- Value in opt.h for RECV_BUFSIZE_DEFAULT: INT_MAX -----*/
#define RECV_BUFSIZE_DEFAULT 2000000000
/*----- Default Value for LWIP_HTTPD: 0 ---*/
#define LWIP_HTTPD 1
#define LWIP_ICMP 1
/*----- Value in opt.h for LWIP_STATS: 1 -----*/
#define LWIP_STATS 0
/*----- Value in opt.h for CHECKSUM_GEN_IP: 1 -----*/
#define CHECKSUM_GEN_IP 1
/*----- Value in opt.h for CHECKSUM_GEN_UDP: 1 -----*/
#define CHECKSUM_GEN_UDP 1
/*----- Value in opt.h for CHECKSUM_GEN_TCP: 1 -----*/
#define CHECKSUM_GEN_TCP 1
/*----- Value in opt.h for CHECKSUM_GEN_ICMP: 1 -----*/
#define CHECKSUM_GEN_ICMP 1
/*----- Value in opt.h for CHECKSUM_GEN_ICMP6: 1 -----*/
#define CHECKSUM_GEN_ICMP6 1
/*----- Value in opt.h for CHECKSUM_CHECK_IP: 1 -----*/
#define CHECKSUM_CHECK_IP 1
/*----- Value in opt.h for CHECKSUM_CHECK_UDP: 1 -----*/
#define CHECKSUM_CHECK_UDP 1
/*----- Value in opt.h for CHECKSUM_CHECK_TCP: 1 -----*/
#define CHECKSUM_CHECK_TCP 1
/*----- Value in opt.h for CHECKSUM_CHECK_ICMP: 1 -----*/
#define CHECKSUM_CHECK_ICMP 1
/*----- Value in opt.h for CHECKSUM_CHECK_ICMP6: 1 -----*/
#define CHECKSUM_CHECK_ICMP6 1
/*-----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /*__LWIPOPTS__H__ */
