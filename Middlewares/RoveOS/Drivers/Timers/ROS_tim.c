/****************************************************************************************************
*                                                                                     ▄▄▄,/,
*   ROS_tim.c                                                                       ▄▀  ,/▄ 
*                                                                                  ▐▌ ,/' ▐▌
*   Implements RoveOS timer functions.                                             /▀/'  ▄▀ 
*                                                                                  └' ▀▀▀   
****************************************************************************************************/

/****************************************************************************************************
*   Includes
****************************************************************************************************/
/*  Public   */
#include "ROS_tim_pub.h"
/*  Private  */
#include "ROS_tim_prv.h"
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
  * @brief Start specific TIM RCC clock.
  * @param TimDef pointer to the timer you wish to initialize.
  * @retval none.
  */
void startTIMRCC(const ROS_tim_def* tim)
{
#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H5xxxx) || (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
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
	else if (tim->htim->Instance == TIM8)
		__HAL_RCC_TIM8_CLK_ENABLE();
	else if (tim->htim->Instance == TIM12)
		__HAL_RCC_TIM12_CLK_ENABLE();
	else if (tim->htim->Instance == TIM13)
		__HAL_RCC_TIM13_CLK_ENABLE();
	else if (tim->htim->Instance == TIM14)
		__HAL_RCC_TIM14_CLK_ENABLE();
	else if (tim->htim->Instance == TIM15)
		__HAL_RCC_TIM15_CLK_ENABLE();
	else if (tim->htim->Instance == TIM16)
		__HAL_RCC_TIM16_CLK_ENABLE();
	else if (tim->htim->Instance == TIM17)
		__HAL_RCC_TIM17_CLK_ENABLE();
#elif (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_F4xxxx)
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
#endif
}

/**
  * @brief Initialize a TIM timer.
  * @param uint64_t value representing the prescaler which divides the APB frequency
  * 	to define your timer frequency.
  * @param uint64_t value representing the period/ARR value which divides the frequency
  * 	but also defines the duty cycle range.
  * @param TimDef pointer of the timer you want to initialize.
  * @retval None
  */
void initTIM(uint64_t prescaler, uint64_t period, const ROS_tim_def* tim)
{
	startTIMRCC(tim);

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	tim->htim->Init.Prescaler = prescaler;
	tim->htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	tim->htim->Init.Period = period;
	tim->htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	tim->htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(tim->htim);
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(tim->htim, &sClockSourceConfig);
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(tim->htim, &sMasterConfig);
}



/**
  * @brief Initialize pwm to a specific pin.
  * @param TIM_TypeDef pointer which is used to determine the matching APB timer.
  * @retval uint64_t containing the freqency of the APB timer for a tim timer.
  */
uint64_t getAPBTimerSpeed(TIM_TypeDef* tim)
{
	uint64_t timer = 0;

#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H5xxxx) || (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
	if (tim == TIM1 || tim == TIM8 || tim == TIM15 || tim == TIM16 || tim == TIM17)
	{
		timer = HAL_RCC_GetPCLK2Freq() * (((RCC->CFGR2 & RCC_CFGR2_PPRE1) != 0U )? 2 : 1);
	}
	else
	{
		timer = HAL_RCC_GetPCLK1Freq() * (((RCC->CFGR1 & RCC_CFGR1_PPRE1) != 0U) ? 2 : 1);
	}
#elif (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_F4xxxx)
	if (tim == TIM1 || tim == TIM9 || tim == TIM10 || tim == TIM11)
	{
		timer = HAL_RCC_GetPCLK2Freq() * (((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_HCLK_DIV1)? 2 : 1);
	}
	else
	{
		timer = HAL_RCC_GetPCLK1Freq() * (((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_HCLK_DIV1) ? 2 : 1);
	}
#endif

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
void initPWMPin(ROS_pin pin, uint64_t range, uint64_t freq, const ROS_tim_channel** channel)
{
	uint8_t tc = 0;
	bool validChannel = false;

	//iterates through usable tim channels in the case that one is in use
	while (pindefs[pin].timChannels[tc].channel != NONE_TIM_CHANNEL_STRUCT.channel && !validChannel)
	{
		if (pindefs[pin].timChannels[tc].tim->htim->State == HAL_TIM_STATE_RESET)
			validChannel = true;
		else
			tc+=1;
	}

	if (!validChannel)
		return;


	initTIM((getAPBTimerSpeed(pindefs[pin].timChannels[tc].tim->htim->Instance) / (range * freq)) - 1, range - 1,
		pindefs[pin].timChannels[tc].tim);

	*channel = &(pindefs[pin].timChannels[tc]);

	HAL_TIM_PWM_Init((*channel)->tim->htim);

	TIM_OC_InitTypeDef sConfigOC = {0};

	//initialize the TIM clock to pwm mode
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_ConfigChannel((*channel)->tim->htim, &sConfigOC, (*channel)->channel);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	//initialize the GPIO pin to Alternate Function
	GPIO_InitStruct.Pin = gpio_pin_defs[pin].GPIOPin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = pindefs[pin].timChannels[tc].AFPort;
	HAL_GPIO_Init(gpio_pin_defs[pin].GPIOPort, &GPIO_InitStruct);

	//Start pwm on set timer
	HAL_TIM_PWM_Start((*channel)->tim->htim, (*channel)->channel);

}


/**
  * @brief returns one of the integer factors of any givin integer.
  * @param uint64_t the integer to find the factor of.
  * @retval uint16_t one integer factor of the provided product.
  */
uint16_t findFactors(uint64_t product)
{
	uint16_t p1 = (uint16_t)sqrt(product);

	while (p1 * (product / p1) != product) p1--;

	return p1;
}


/**
  * @brief Sets up a given pin for PWM usage.
  * @param ROS_pin the pin that should output the pwm signal.
  * @param uint64_t the range of the pwm signal which determines possible
  * 	duty-cycle compare values.
  * @retval none.
  */
void ROS_start_PWM(ROS_pin pin, uint64_t range, uint64_t freq)
{
	initPWMPin(pin, range, freq, &(defined_pwms[num_pwms].channel));
	defined_pwms[num_pwms].range = range;
	defined_pwms[num_pwms].pin = pin;
	num_pwms++;
}


/**
  * @brief returns the pwm system assigned to a given pin.
  * @param ROS_pin containing the pin you wish to retrieve the pwm of.
  * @retval ROS_defined_pwm pointer of the defined pwm..
  */
ROS_defined_pwm* pwmFromPin(ROS_pin pin)
{
	for(uint8_t i = 0; i < sizeof(defined_pwms) / sizeof(ROS_defined_pwm); i++)
	{
		if (defined_pwms[i].pin == pin)
			return &defined_pwms[i];
	}

	return &NONE_PWM;
}


/**
  * @brief sets the duty cycle of the PWM.
  * @param ROS_pin the pin that you wish to set the duty cycle of.
  * @param float the duty cycle you wish to assign to the pin.
  * @retval none.
 */
void ROS_set_PWM_duty(ROS_pin pin, float duty)
{
	ROS_defined_pwm* dp = pwmFromPin(pin);
	__HAL_TIM_SET_COMPARE((*dp).channel->tim->htim, (*dp).channel->channel, (uint64_t)((*dp).range * (duty/100.)));
}


/**
  * @brief returns the next availible TIM with certain requirements.
  * @param uint8_t bitmask of the requirements the TIM must have.
  * @retval int16_t returns the availible tim or -1 if failed.
  */
int16_t getAvailibleTIM(uint8_t reqs)
{

	for(uint8_t i = 0; i < sizeof(timdefs) / sizeof(ROS_tim_def); i++)
	{
		if ((timdefs[i].usages & reqs) == reqs && timHandlers[i].State == HAL_TIM_STATE_RESET)
		{
			return i;
		}
	}

	return -1;
}


/**
  * @brief Initializes a timer interrupt.
  * @param function pointer callback to the function you wish to be called
  * 	on the interrupt reset.
  * @retval none.
  */
void initTIMInterrupt(void (*callback)(void), uint64_t period)
{
	uint8_t tim = getAvailibleTIM(0b00000001);
	const ROS_tim_def* timd = &timdefs[tim];

	uint16_t psc = findFactors((uint64_t)(getAPBTimerSpeed(timd->htim->Instance) / (1000000. / period)));

	initTIM(psc - 1, (uint64_t)(getAPBTimerSpeed(timd->htim->Instance) / (1000000. / period)) / psc - 1,
			timd);

	HAL_NVIC_SetPriority(timdefs[tim].IRQ, 2, 2);
	HAL_NVIC_EnableIRQ(timdefs[tim].IRQ);
  	HAL_TIM_Base_Start_IT(timd->htim);

  	IRQ_callbacks[num_callbacks].func = callback;
  	IRQ_callbacks[num_callbacks].htim = timd->htim;
  	num_callbacks++;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	for (uint8_t i = 0; i < num_callbacks; i++)
	{
		if (htim == IRQ_callbacks[i].htim)
		{
			IRQ_callbacks[i].func();
		}
	}
}


/**
  * @brief Initializes a timer interrupt.
  * @param function pointer callback to the function you wish to be called
  * 	on the interrupt reset.
  * @retval none.
  */
void ROS_start_interrupt(void (*callback)(void), uint64_t period)
{
	initTIMInterrupt(callback, period);
}


//these could probably be moved to another file, these are just used to handle the interrupt setup.
#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H5xxxx) || (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
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
#elif (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_F4xxxx)
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
#endif
