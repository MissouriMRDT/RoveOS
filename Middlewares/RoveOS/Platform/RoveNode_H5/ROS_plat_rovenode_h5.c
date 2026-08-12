/****************************************************************************************************
*                                                                                     ▄▄▄,/,
*   ROS_plat_rovenode_h5.c                                                          ▄▀  ,/▄ 
*                                                                                  ▐▌ ,/' ▐▌
*   Implements platform-specific functions for the RoveNode H5.                    /▀/'  ▄▀ 
*                                                                                  └' ▀▀▀   
****************************************************************************************************/

/****************************************************************************************************
*   Includes
****************************************************************************************************/
/*  Public   */
/*  Private  */
#include "ROS_plat_rovenode_h5_prv.h"

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
 * Timers
 */

/**
  * @brief Start specific TIM RCC clock.
  * @param TimDef pointer to the timer you wish to initialize.
  * @retval none.
  */
void startTIMRCC(const ROS_tim_def* tim)
{
	if (tim->htim->Instance == TIM1)
		__HAL_RCC_TIM1_CLK_ENABLE();
	else if (tim->htim->Instance == TIM2)
		__HAL_RCC_TIM2_CLK_ENABLE();
	else if (tim->htim->Instance == TIM3)
		__HAL_RCC_TIM3_CLK_ENABLE();
	else if (tim->htim->Instance == TIM4)
		__HAL_RCC_TIM4_CLK_ENABLE();
	else if (tim->htim->Instance == TIM5)
		__HAL_RCC_TIM5_CLK_ENABLE();
	else if (tim->htim->Instance == TIM6)
		__HAL_RCC_TIM6_CLK_ENABLE();
	else if (tim->htim->Instance == TIM7)
		__HAL_RCC_TIM7_CLK_ENABLE();
	else if (tim->htim->Instance == TIM9)
		__HAL_RCC_TIM9_CLK_ENABLE();
	else if (tim->htim->Instance == TIM10)
		__HAL_RCC_TIM10_CLK_ENABLE();
	else if (tim->htim->Instance == TIM11)
		__HAL_RCC_TIM11_CLK_ENABLE();
	else if (tim->htim->Instance == TIM12)
		__HAL_RCC_TIM12_CLK_ENABLE();
	else if (tim->htim->Instance == TIM13)
		__HAL_RCC_TIM13_CLK_ENABLE();
	else if (tim->htim->Instance == TIM14)
		__HAL_RCC_TIM14_CLK_ENABLE();
}


/**
  * @brief Initialize pwm to a specific pin.
  * @param TIM_TypeDef pointer which is used to determine the matching APB timer.
  * @retval uint64_t containing the freqency of the APB timer for a tim timer.
  */
uint64_t getAPBTimerSpeed(TIM_TypeDef* tim)
{
	uint64_t timer = 0;

	if (tim == TIM1 || tim == TIM9 || tim == TIM10 || tim == TIM11)
		timer = HAL_RCC_GetPCLK2Freq() * (((RCC->CFGR & RCC_CFGR_PPRE2) != 0U )? 2 : 1);
	else
		timer = HAL_RCC_GetPCLK1Freq() * (((RCC->CFGR & RCC_CFGR_PPRE1) != 0U) ? 2 : 1);

	return timer;
}


void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandlers[1]);
}
void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandlers[2]);
}
void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandlers[3]);
}
void TIM5_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandlers[4]);
}
void TIM12_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandlers[1]);
}
void TIM15_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandlers[2]);
}
void TIM16_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandlers[3]);
}
void TIM17_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandlers[4]);
}
