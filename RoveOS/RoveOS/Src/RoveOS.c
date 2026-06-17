/*
 * RoveOS.c
 *
 *  Created on: Jun 9, 2026
 *      Author: yewke
 */

#include "RoveOS.h"

/**
  * @brief Initialize a TIM timer.
  * @param uint64_t value representing the prescaler which divides the APB frequency
  * 	to define your timer frequency.
  * @param uint64_t value representing the period/ARR value which divides the frequency
  * 	but also defines the duty cycle range.
  * @param TIM_TypeDef pointer containing the timer that you wish to initialize e.g. TIM2.
  * @param TIM_HandleTypeDef pointer containing the TIM handler that you will utilize later
  * 	to leverage the timer.
  * @retval None
  */
void initTIM(uint64_t prescaler, uint64_t period, TIM_TypeDef* tim, TIM_HandleTypeDef* htim)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	htim->Instance = tim;
	htim->Init.Prescaler = prescaler;
	htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	htim->Init.Period = period;
	htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(htim);
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(htim, &sClockSourceConfig);
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig);

	__HAL_RCC_TIM2_CLK_ENABLE();
}



/**
  * @brief Initialize pwm to a specific pin.
  * @param TIM_TypeDef pointer which is used to determine the matching APB timer.
  * @retval uint64_t containing the freqency of the APB timer for a tim timer.
  */
uint64_t getAPBTimerSpeed(TIM_TypeDef* tim)
{
	uint64_t timer = 0;

	if (tim == TIM1 || tim == TIM8
#ifdef TIM15
			|| tim == TIM15
#ifdef TIM16
			|| tim == TIM16
#ifdef TIM17
			|| tim == TIM17
#endif
#endif
#endif
			)
	{
		timer = HAL_RCC_GetPCLK2Freq() * (RCC->CFGR & RCC_CFGR_PPRE2 != 0 ? 2 : 1);
	}
	else
	{
		timer = HAL_RCC_GetPCLK1Freq() * (RCC->CFGR & RCC_CFGR_PPRE1 != 0 ? 2 : 1);
	}

	return timer;
}


/**
  * @brief Initialize pwm to a specific pin.
  * @param Pin enum of the pin that you wish to initialize, not all pins will be functional;
  * @param uint64_t the range of the PWM duty cycle.
  * @param uint64_t the target frequency of the PWM cycle.
  * @param TIM_HandleTypeDef pointer that you will use to set compare duty cycle.
  * @param uint16_t pointer to an object that stores the generated timchannel
  * @retval None
  */
void initPWMPin(Pin pin, uint64_t range, uint64_t freq, TIM_HandleTypeDef* htim, uint16_t* returnChannel)
{
	uint8_t tc = 0;
	bool validChannel = false;

	//iterates through usable tim channels in the case that one is in use
	while (pindefs[pin].timChannels[tc].channel != NONE_TIM_CHANNEL_STRUCT.channel && !validChannel)
	{
		initTIM((getAPBTimerSpeed(pindefs[pin].timChannels[tc].tim) / (range * freq)) - 1, range - 1,
					pindefs[pin].timChannels[tc].tim, htim);

		if (!((*htim).Instance->CCER & (1 << pindefs[pin].timChannels[tc].channel)))
			validChannel = true;
		else
			tc+=1;
	}

	if (!validChannel)
		return;

	*returnChannel = pindefs[pin].timChannels[tc].channel;

	TIM_OC_InitTypeDef sConfigOC = {0};

	//initialize the TIM clock to pwm mode
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, *returnChannel);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	//initialize the GPIO pin to Alternate Function
	GPIO_InitStruct.Pin = pindefs[pin].GPIOPin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = pindefs[pin].timChannels[tc].AFPort;
	HAL_GPIO_Init(pindefs[pin].GPIOPort, &GPIO_InitStruct);

	HAL_TIM_PWM_Init(htim);
	//Start pwm on set timer
	HAL_TIM_PWM_Start(htim, *returnChannel);

}
