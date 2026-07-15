/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "lwip/opt.h"
#include "lwip/init.h"
#include "netif/etharp.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#if LWIP_DHCP
#include "lwip/dhcp.h"
#endif
#include "ethernetif.h"
#include "main.h"
#include "app_ethernet.h"
#include "lwip/udp.h"     /* LwIP UDP stack interface */
#include <string.h>       /* String manipulations */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#if defined(__ICCARM__)
#include <LowLevelIOInterface.h>
#endif /* __ICCARM__ */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
#if defined(__ICCARM__)
/* New definition from EWARM V9, compatible with EWARM8 */
int iar_fputc(int ch);
#define PUTCHAR_PROTOTYPE int iar_fputc(int ch)
#elif defined ( __CC_ARM ) || defined(__ARMCC_VERSION)
/* ARM Compiler 5/6*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif /* __ICCARM__ */

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct netif gnetif;
UART_HandleTypeDef huart3;

/* UDP handler variables */
struct udp_pcb *upcb;
UDP_Packet_t tx_packet;
UDP_Packet_t rx_packet;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void BSP_Config(void);
static void Netif_Config(void);
static void USART3_UART_Init(void);
static void CACHE_Enable(void);

/* Custom UDP Protocols */
void Custom_UDP_Init(void);
void Custom_UDP_Send(void);
void udp_receive_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  uint32_t last_send_time = 0;

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Enable the CPU Cache */
  CACHE_Enable();

  /* Initialize all configured peripherals */
  USART3_UART_Init();

  /* Configure the LEDs ...*/
  BSP_Config();

  printf("UDP Echo Client Application \r\n");
  printf("STM32H563ZI board \r\n");
  printf("State: Ethernet Initialization ... \r\n");

  /* Initialize the LwIP stack */
  lwip_init();

  /* Configure the Network interface */
  Netif_Config();

  /* Initialize our custom UDP settings instead of standard echo */
  Custom_UDP_Init();

  /* Infinite loop */
  while (1)
  {
    /* Read a received packet from the Ethernet buffers and send it
       to the lwIP for handling */
    ethernetif_input(&gnetif);

    /* Handle timeouts */
    sys_check_timeouts();

#if LWIP_NETIF_LINK_CALLBACK
    Ethernet_Link_Periodic_Handle(&gnetif);
#endif

#if LWIP_DHCP
    DHCP_Periodic_Handle(&gnetif);
#endif

    /* Automatically Send a packet to your Laptop every 1000 milliseconds (1 Second) */
    if (HAL_GetTick() - last_send_time >= 1000)
    {
      last_send_time = HAL_GetTick();
      Custom_UDP_Send();
    }
  }
}

/* ========================================================================== */
/* CUSTOM UDP FUNCTIONS                             */
/* ========================================================================== */

/**
  * @brief  Initialize UDP port routing
  */
void Custom_UDP_Init(void) {
  ip_addr_t DestIPaddr;

  /* Create a new UDP control block pointer */
  upcb = udp_new();

  if (upcb != NULL) {
    /* Bind the STM32 to listen locally on port 50002 */
    err_t err = udp_bind(upcb, IP_ADDR_ANY, UDP_CLIENT_PORT);

    if(err == ERR_OK) {
      /* Map target destination IP (192.168.0.10) */
      IP4_ADDR(&DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3);

      /* Establish remote path targeting laptop's port 50001 */
      udp_connect(upcb, &DestIPaddr, UDP_SERVER_PORT);

      /* Set up parser callback to trigger whenever data arrives */
      udp_recv(upcb, udp_receive_callback, NULL);
      printf("Custom UDP successfully bound and configured!\r\n");
    } else {
      printf("Failed to bind UDP socket!\r\n");
    }
  }
}

/**
  * @brief  Send struct packed UDP message to your Laptop
  */
void Custom_UDP_Send(void) {
  struct pbuf *p;
  static uint32_t id_counter = 0;

  /* Fill structural data values */
  tx_packet.message_id = id_counter++;
  tx_packet.sensor_value = 23.5f; // Static simulation sensor metric
  strncpy(tx_packet.status_flag, "OK", sizeof(tx_packet.status_flag));

  /* Allocate buffer from pool memory matching struct size */
  p = pbuf_alloc(PBUF_TRANSPORT, sizeof(UDP_Packet_t), PBUF_RAM);

  if (p != NULL) {
    /* Copy data stream structure directly into pbuf payload block */
    pbuf_take(p, &tx_packet, sizeof(UDP_Packet_t));

    /* Push package downstream */
    udp_send(upcb, p);

    /* Free allocation from RAM */
    pbuf_free(p);
  }
}

/**
  * @brief  Callback function executed instantly on incoming UDP receipt
  */
void udp_receive_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) {
  /* Verify incoming payload matches expectations */
  if (p->len == sizeof(UDP_Packet_t)) {
    /* Copy incoming memory straight into our rx_packet struct structure */
    pbuf_copy_partial(p, &rx_packet, sizeof(UDP_Packet_t), 0);

    /* Successfully parsed variables: */
    uint32_t r_id = rx_packet.message_id;
    float r_val = rx_packet.sensor_value;

    /* Console serial print check */
    printf("[Incoming Packet]: ID=%lu, Value=%.2f, Flag=%s\r\n", r_id, r_val, rx_packet.status_flag);

    /* Check command status: Switch Green LED when "LED" command string is matched */
    if (strncmp(rx_packet.status_flag, "LED", 3) == 0) {
      BSP_LED_Toggle(LED_GREEN);
    }
  }

  /* Essential: Free the allocation to prevent memory leaks */
  pbuf_free(p);
}


/* ========================================================================== */
/* EXISTING HAL CALLBACKS                           */
/* ========================================================================== */

static void BSP_Config(void)
{
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_YELLOW);
  BSP_LED_Init(LED_RED);

  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);
}

/**
  * @brief  Setup the network interface
  * @param  None
  * @retval None
  */
static void Netif_Config(void)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

#if LWIP_DHCP
  ip_addr_set_zero_ip4(&ipaddr);
  ip_addr_set_zero_ip4(&netmask);
  ip_addr_set_zero_ip4(&gw);
#else

  /* IP address default setting */
  IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
  IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);

#endif

  /* add the network interface */
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

  /* Registers the default network interface */
  netif_set_default(&gnetif);

  ethernet_link_status_updated(&gnetif);

#if LWIP_NETIF_LINK_CALLBACK
  netif_set_link_callback(&gnetif, ethernet_link_status_updated);
#endif
}

/**
  * @brief  BSP Push Button callback
  * @param  Button Specifies the pin connected EXTI line
  * @retval None.
  */
void BSP_PB_Callback(Button_TypeDef Button)
{
  if (Button == BUTTON_USER)
  {
    /* Force dynamic transmission manual push */
    Custom_UDP_Send();
  }
}

static void USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DIGITAL;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 250;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2| RCC_CLOCKTYPE_PCLK3);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void CACHE_Enable(void)
{
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
}

#if defined(__ICCARM__)
size_t __write(int file, unsigned char const *ptr, size_t len)
{
  size_t idx;
  unsigned char const *pdata = ptr;

  for (idx = 0; idx < len; idx++)
  {
    iar_fputc((int)*pdata);
    pdata++;
  }
  return len;
}
#endif /* __ICCARM__ */

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  printf("Critical Error \r\n");
  BSP_LED_Off(LED_YELLOW);
  while (1)
  {
    BSP_LED_Toggle(LED_RED);
    HAL_Delay(500);
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */
