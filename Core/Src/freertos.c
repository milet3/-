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
/* USER CODE BEGIN Includes */
#include "TCP_ECHO.h"
#include "lwip/dhcp.h"
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
extern void MX_LWIP_Init(void);
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
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* LWIP initialized, now create echo task */
  osThreadNew(lwip_echo_task, NULL, &(osThreadAttr_t){
                                        .name = "echoTask",
                                        .stack_size = 1024,
                                        .priority = osPriorityNormal,
                                    });
  /* Infinite loop */
  printf("\r\n================================================\r\n");
  printf("LwIP Stack Initialized, starting DHCP...\r\n");
  printf("================================================\r\n");
  
  uint32_t dhcp_timeout = 0;
  for (;;)
  {
    // 检查网线连接状态 (注意：如果 ethernet_link_thread 为空，这里可能需要手动维护)
    if (netif_is_link_up(&gnetif)) {
        // 如果 DHCP 分配到 IP
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
          break; // 获取到 IP 后退出循环
        }
        else
        {
          dhcp_timeout++;
          printf("[DHCP] Waiting... (%ds)\r", (int)(dhcp_timeout * 2));
          if (dhcp_timeout > 30) { // 60秒超时
             printf("\r\n[DHCP] Warning: DHCP taking too long, check your server/cable.\r\n");
             dhcp_timeout = 0;
          }
        }
    } else {
        printf("[LINK] Ethernet cable is DISCONNECTED! Please check.\r\n");
        // 如果驱动没更新 link 状态，我们尝试强制设置为 UP 以便 DHCP 继续
        // netif_set_link_up(&gnetif); 
    }
    
    osDelay(2000);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

