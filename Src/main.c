/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "core_cm33.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TX_PACKET_SIZE 60

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ETH_TxPacketConfigTypeDef TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;

/* USER CODE BEGIN PV */
// Allocate a buffer pool. ETH_RX_DESC_CNT is typically 4 (defined by CubeMX)
// 4 buffers * 1536 bytes each = a dedicated space in RAM for incoming frames
__attribute__((aligned(4))) uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE];
/* USER CODE END PV */


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_ICACHE_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_ICACHE_Init();
  /* USER CODE BEGIN 2 */


  if (HAL_ETH_Start(&heth) == HAL_OK)
  {

  } else {
	  while(1){
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(5000);
	  }
  }

  uint32_t phy_reg_id1 = 0;
  uint32_t phy_reg_id2 = 0;
  uint32_t target_phy_addr = 0; // Try 0 first. If it fails, try 1.

  // Read PHY Register 2 and Register 3 (PHY Identifier Registers)
  HAL_ETH_ReadPHYRegister(&heth, target_phy_addr, 2, &phy_reg_id1);
  HAL_ETH_ReadPHYRegister(&heth, target_phy_addr, 3, &phy_reg_id2);

  // For a genuine LAN8742:
  // phy_reg_id1 should equal 0x0007
  // phy_reg_id2 should equal 0xC130 (lower bits might vary slightly by silicon stepping)
  if (phy_reg_id1 == 0x0007 && (phy_reg_id2 & 0xFFF0) == 0xC130) {
      // SUCCESS: MDIO interface works, and the PHY address matches perfectly!
  } else {
      // FAIL: Check your MDIO/MDC pull-up resistors or verify your strap-pin PHY address.
	  while(1)
	  {
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(1000);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(1000);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(1000);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(2000);
	  }
  }

  // Loopback test
  uint32_t phy_reg_val = 0;

  // 1. Read current Register 0 value from LAN8742A (Default PHY Address is usually 0)
  HAL_ETH_ReadPHYRegister(&heth, 0, 0, &phy_reg_val);

  // 2. Set Bit 14 (Loopback) high
  phy_reg_val |= (1 << 14);

  // 3. Write back to Register 0
  HAL_ETH_WritePHYRegister(&heth, 0, 0, phy_reg_val);

  // 4. (Optional) Read back to verify the bit was written successfully
  HAL_ETH_ReadPHYRegister(&heth, 0, 0, &phy_reg_val);
  if (phy_reg_val & (1 << 14)) {
      // PHY loopback is enabled successfully!
  } else {
	  while(1)
	  {
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(1000);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(1000);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(1000);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(1000);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(1000);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(2000);
	  }
  }

  // Enable MAC-level loopback (Bit 12 'LM' in ETH_MACCR)
  heth.Instance->MACCR |= ETH_MACCR_LM;


//   1. Prepare a dummy frame buffer (Minimum Ethernet frame size is 60 bytes)
  ETH_BufferTypeDef TxConfig;
  ETH_TxPacketConfig TxPacketConfig;
  uint8_t TxBuffer[TX_PACKET_SIZE];

  /* 1. Build a dummy Ethernet Frame */
  /* Destination MAC (6 bytes) - e.g., Broadcast */
  memset(&TxBuffer[0], 0xFF, 6);
  /* Source MAC (6 bytes) */
  memset(&TxBuffer[6], 0x02, 6);
  /* Length/Type field (2 bytes) - Custom experimental type */
  TxBuffer[12] = 0x88;
  TxBuffer[13] = 0xB5;

  /* Fill Payload with a pattern (0, 1, 2, 3...) */
  for(int i = 14; i < TX_PACKET_SIZE; i++)
  {
	  TxBuffer[i] = (uint8_t)(i - 14);
  }



  /* 2. Configure the HAL TX structure for STM32H5 */
  TxConfig.buffer = TxBuffer;
  TxConfig.len    = TX_PACKET_SIZE;
  TxConfig.next   = NULL; // Single buffer packet

  memset(&TxPacketConfig, 0, sizeof(ETH_TxPacketConfig));
  TxPacketConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxPacketConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT; // Hardware appends CRC
  TxPacketConfig.TxBuffer   = &TxConfig;
  TxPacketConfig.Length     = TX_PACKET_SIZE;

  // 3. Transmit the frame
  if (HAL_ETH_Transmit(&heth, &TxPacketConfig, HAL_MAX_DELAY) == HAL_OK) {
      // Transmit triggered successfully!
  } else {
	  while(1)
	  {
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(100);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(100);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(100);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(2000);
	  }
  }

//   4. Wait briefly and check the RX side
  HAL_Delay(10);
  void *rx_payload = NULL;


  if (HAL_ETH_ReadData(&heth, &rx_payload) == HAL_OK) {

	  uint8_t *rx_ptr = (uint8_t *)rx_payload;

	  uint8_t new_rx_buffer[TX_PACKET_SIZE];

	  for (int i=0; i < TX_PACKET_SIZE; i++)
	  {
		  new_rx_buffer[i] = rx_ptr[i];
	  }

	  __NOP();



  } else {
	  while(1)
	  {
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(200);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(200);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(200);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(200);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(200);
		  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
		  HAL_Delay(2000);
	  }
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  HAL_GPIO_TogglePin(HEART_GPIO_Port, HEART_Pin);
	  HAL_Delay(2000);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_CSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.CSIState = RCC_CSI_ON;
  RCC_OscInitStruct.CSICalibrationValue = RCC_CSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_CSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 32;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the programming delay
  */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_0);
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfigTypeDef));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(HEART_GPIO_Port, HEART_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : HEART_Pin */
  GPIO_InitStruct.Pin = HEART_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HEART_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// Track allocation indexes manually for our static buffer array
static uint32_t rx_alloc_idx = 0;

/**
  * @brief  HAL ETH Rx Allocate Callback. Passes memory addresses to the
  *         Ethernet descriptors when the peripheral initializes and starts.
  */
void HAL_ETH_RxAllocateCallback(uint8_t **buff)
{
    // Assign the next available buffer row from our global Rx_Buff pool
    *buff = &Rx_Buff[rx_alloc_idx][0];

    // Increment index and loop around the ring size boundary
    rx_alloc_idx++;
    if(rx_alloc_idx >= ETH_RX_DESC_CNT)
    {
        rx_alloc_idx = 0;
    }
}

/**
  * @brief  HAL ETH Rx Link Callback. Triggers during HAL_ETH_ReadData to
  *         re-assemble packets.
  */
void HAL_ETH_RxLinkCallback(void **pStart, void **pEnd, uint8_t *buff, uint16_t Length)
{
    *pStart = buff; // Assign start pointer directly to the current buffer address
}
/* USER CODE END 4 */


 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};
  MPU_Attributes_InitTypeDef MPU_AttributesInit = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region 0 and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x08FFF000;
  MPU_InitStruct.LimitAddress = 0x08FFFFFF;
  MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER0;
  MPU_InitStruct.AccessPermission = MPU_REGION_ALL_RO;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Attribute 0 and the memory to be protected
  */
  MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER0;
  MPU_AttributesInit.Attributes = INNER_OUTER(MPU_NOT_CACHEABLE);

  HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
