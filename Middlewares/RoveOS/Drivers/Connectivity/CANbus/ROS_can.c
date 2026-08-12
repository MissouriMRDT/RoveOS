/****************************************************************************************************
*                                                                                     ▄▄▄,/,
*   ROS_can.c                                                                       ▄▀  ,/▄ 
*                                                                                  ▐▌ ,/' ▐▌
*   Implements RoveOS CANbus functions.                                            /▀/'  ▄▀ 
*                                                                                  └' ▀▀▀   
****************************************************************************************************/

/****************************************************************************************************
*   Includes
****************************************************************************************************/
/*  Public   */
#include "ROS_can_prv.h"
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

void ROS_start_CAN(ROS_can can_num)
{
	__HAL_RCC_CAN1_CLK_ENABLE();
	__HAL_RCC_CAN2_CLK_ENABLE();

	canhandlers[can_num].Init.Prescaler = 2;
	canhandlers[can_num].Init.Mode = CAN_MODE_NORMAL;
	canhandlers[can_num].Init.SyncJumpWidth = CAN_SJW_1TQ;
	canhandlers[can_num].Init.TimeSeg1 = CAN_BS1_12TQ;
	canhandlers[can_num].Init.TimeSeg2 = CAN_BS2_3TQ;
	canhandlers[can_num].Init.TimeTriggeredMode = DISABLE;
	canhandlers[can_num].Init.AutoBusOff = DISABLE;
	canhandlers[can_num].Init.AutoWakeUp = DISABLE;
	canhandlers[can_num].Init.AutoRetransmission = DISABLE;
	canhandlers[can_num].Init.ReceiveFifoLocked = DISABLE;
	canhandlers[can_num].Init.TransmitFifoPriority = DISABLE;

	if (can_num == 0)
	{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		__HAL_RCC_GPIOG_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
		HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	}
	if (can_num == 1)
	{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		__HAL_RCC_CAN2_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}

	HAL_CAN_Init(&canhandlers[can_num]);

	CAN_FilterTypeDef filter;

	filter.FilterBank = can_num;
	filter.FilterMode = CAN_FILTERMODE_IDMASK;
	filter.FilterScale = CAN_FILTERSCALE_32BIT;
	filter.FilterIdHigh = 0x0000;
	filter.FilterIdLow = 0x0000;
	filter.FilterMaskIdHigh = 0x0000;
	filter.FilterMaskIdLow = 0x0000;
	filter.FilterFIFOAssignment = can_num;
	filter.FilterActivation = ENABLE;
	filter.SlaveStartFilterBank = can_num == 0 ? 0 : 14;

	HAL_CAN_ConfigFilter(&canhandlers[can_num], &filter);

	if (HAL_CAN_Start(&canhandlers[can_num]) == HAL_OK)
		HAL_GPIO_WritePin(GPIOB, 0x0080, 1);
	else
		HAL_GPIO_WritePin(GPIOB, 0x0001, 1);
}

void ROS_write_CAN(ROS_can can_num, uint16_t stdid, uint8_t* data, uint8_t data_length)
{
	CAN_TxHeaderTypeDef header;
	uint32_t mailbox;

	header.StdId = stdid;
	header.IDE = CAN_ID_STD;
	header.RTR = CAN_RTR_DATA;
	header.DLC = data_length;

	HAL_CAN_AddTxMessage(&canhandlers[can_num], &header, data, &mailbox);

}

void ROS_setup_recieve_CAN(ROS_can can_num, void (*callback) (uint16_t, uint8_t*, uint8_t))
{
	HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 2, 2);
	HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);

	HAL_CAN_ActivateNotification(&canhandlers[can_num], candefs[can_num].IRQ);

	cancallbacks[can_num] = callback;
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef header;
	uint8_t data[8];

	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &header, data) == HAL_OK)
	{
		if (hcan->Instance == CAN1)
				cancallbacks[0](header.StdId, data, header.DLC);
	}
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef header;
	uint8_t data[8];

	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &header, data) == HAL_OK)
	{
		if (hcan->Instance == CAN2)
				cancallbacks[1](header.StdId, data, header.DLC);
	}
}


void CAN1_RX0_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&canhandlers[0]);
}

void CAN2_RX1_IRQHandler(void)
{
	HAL_GPIO_WritePin(GPIOB, 0x0001, 1);
    HAL_CAN_IRQHandler(&canhandlers[1]);
}
