/****************************************************************************************************
*                                                                                     ▄▄▄,/,
*   ROS_uart.c                                                                      ▄▀  ,/▄ 
*                                                                                  ▐▌ ,/' ▐▌
*   Implements RoveOS UART and USART functions.                                    /▀/'  ▄▀ 
*                                                                                  └' ▀▀▀   
****************************************************************************************************/

/****************************************************************************************************
*   Includes
****************************************************************************************************/
/*  Public   */
#include "UTL_pub.h"
#include "ROS_uart_pub.h"
#include "ROS_uart_prv.h"
/*  Private  */

/****************************************************************************************************
*   Macros
****************************************************************************************************/

/****************************************************************************************************
*   Types
****************************************************************************************************/

/****************************************************************************************************
*   Variables
****************************************************************************************************/

/****************************************************************************************************
*   Private Functions
****************************************************************************************************/


/**
  * @brief Initialize UART.
  * @param ROS_uart the uart that you wish to define.
  * @param uint64_t the baude rate of the uart instance.
  * @param uint32_t the mode the the uart instance.
  * @retval none.
  */
void ROS_start_UART(ROS_uart uart_num, uint64_t baude, uint32_t mode)
{
	uarthandlers[uart_num].Init.BaudRate = baude;
	uarthandlers[uart_num].Init.WordLength = UART_WORDLENGTH_8B;
	uarthandlers[uart_num].Init.StopBits = UART_STOPBITS_1;
	uarthandlers[uart_num].Init.Parity = UART_PARITY_NONE;
	uarthandlers[uart_num].Init.Mode = mode;
	uarthandlers[uart_num].Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uarthandlers[uart_num].Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&uarthandlers[uart_num]);
}


/**
  * @brief Writes string data through the UART instance.
  * @param ROS_uart the uart instance to send through.
  * @param char pointer the string you wish to send.
  * @retval none.
  */
void ROS_write_UART(ROS_uart uart_num, const char* ch)
{
	HAL_UART_Transmit(&uarthandlers[uart_num], (uint8_t *)ch, strlen(ch), HAL_MAX_DELAY);
}


/**
  * @brief Initializes a basic uart setup for serial printing UART_1.
  * @retval none.
  */
void ROS_start_serial()
{
	ROS_start_UART(SERIAL_UART, 115200, UART_MODE_TX_RX);
}


/**
  * @brief prints basic serial data to a monitor.
  * @param char pointer the string you wish to send.
  * @retval none.
  */
void ROS_print(const char* ch)
{
	ROS_write_UART(SERIAL_UART, ch);
}
