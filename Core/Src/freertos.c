/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "lwip.h"
#include "lwip/dhcp.h"
#include "dns_server.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

extern struct netif gnetif;
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for LWIP */
  printf("[OK] Default task started, init LWIP...\r\n");
  MX_LWIP_Init();
  printf("[OK] LWIP init done, waiting for DHCP IP...\r\n");

  /* USER CODE BEGIN StartDefaultTask */
  uint32_t dhcp_timeout = 0;

  /* === Phase 1: Wait for DHCP === */
  for (;;)
  {
    if (netif_is_link_up(&gnetif)) {
        if (dhcp_supplied_address(&gnetif))
        {
          printf("\r\n[DHCP] Success! Network is ready.\r\n");
          printf("[DHCP] IP Address:  %s\r\n", ip4addr_ntoa(netif_ip4_addr(&gnetif)));
          printf("[DHCP] Subnet Mask: %s\r\n", ip4addr_ntoa(netif_ip4_netmask(&gnetif)));
          printf("[DHCP] Gateway:     %s\r\n", ip4addr_ntoa(netif_ip4_gw(&gnetif)));
          printf("[ETH] MAC Address:  %02X:%02X:%02X:%02X:%02X:%02X\r\n",
                 gnetif.hwaddr[0], gnetif.hwaddr[1], gnetif.hwaddr[2],
                 gnetif.hwaddr[3], gnetif.hwaddr[4], gnetif.hwaddr[5]);
          printf("================================================\r\n");
           dns_server_start();
          http_server_start();
          break;
        }
        else
        {
          dhcp_timeout++;
          printf("[DHCP] Waiting... (%ds)\r", (int)(dhcp_timeout * 2));
          if (dhcp_timeout > 30) {
             printf("\r\n[DHCP] Warning: DHCP taking too long, check your server/cable.\r\n");
             dhcp_timeout = 0;
          }
        }
    } else {
        printf("[LINK] Ethernet cable is DISCONNECTED! Please check.\r\n");
    }
    osDelay(2000);
  }

  /* === Phase 2: Network monitoring loop === */
  printf("[NETMON] Network monitor started\r\n");
  for (;;)
  {
    if (!netif_is_link_up(&gnetif))
    {
      printf("[NETMON] Link DOWN, waiting for cable...\r\n");
      while (!netif_is_link_up(&gnetif))
      {
        osDelay(1000);
      }
      printf("[NETMON] Link restored, restarting DHCP...\r\n");
      dhcp_stop(&gnetif);
      dhcp_start(&gnetif);

      uint32_t wait = 0;
      while (!dhcp_supplied_address(&gnetif) && wait < 30)
      {
        osDelay(2000);
        wait++;
      }
      if (dhcp_supplied_address(&gnetif))
      {
        printf("[NETMON] DHCP re-acquired: %s\r\n",
               ip4addr_ntoa(netif_ip4_addr(&gnetif)));
      }
      else
      {
        printf("[NETMON] DHCP timeout after link restore\r\n");
      }
      continue;
    }

    if (!dhcp_supplied_address(&gnetif))
    {
      printf("[NETMON] DHCP lease lost, restarting...\r\n");
      dhcp_stop(&gnetif);
      dhcp_start(&gnetif);
    }

    /* Print status every 60 seconds (6 cycles * 10s) to reduce UART load */
    static uint32_t mon_cycle = 0;
    if (++mon_cycle >= 6)
    {
      printf("[NETMON] OK | IP: %-15s | Link: UP\r\n",
             ip4addr_ntoa(netif_ip4_addr(&gnetif)));
      mon_cycle = 0;
    }

    osDelay(10000);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */
