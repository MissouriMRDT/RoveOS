#ifndef ROS_TIM_PUB_H
#define ROS_TIM_PUB_H

/****************************************************************************************************
*                                                                                     ▄▄▄,/,
*   ROS_tim_pub.h                                                                   ▄▀  ,/▄ 
*                                                                                  ▐▌ ,/' ▐▌
*   Defines RoveOS timer public functions.                                         /▀/'  ▄▀ 
*                                                                                  └' ▀▀▀   
****************************************************************************************************/

/****************************************************************************************************
*   Includes
****************************************************************************************************/
/*  Public   */
/*  Private  */
#include "UTL_pub.h"
#include "ROS_core_pub.h"
#include "GPIO/ROS_gpio_pub.h"
#include "ROS_platform_pub.h"

/****************************************************************************************************
*   Macros
****************************************************************************************************/

/****************************************************************************************************
*   Types
****************************************************************************************************/
//Usages: N/A N/A N/A N/A N/A N/A N/A Interrupt
typedef struct
{
	TIM_HandleTypeDef* htim;
	IRQn_Type IRQ;
	uint8_t usages;
} ROS_tim_def;

typedef struct {
	uint16_t channel;
	uint16_t AFPort;
	const ROS_tim_def* tim;
} ROS_tim_channel;

typedef struct {
	ROS_tim_channel timChannels[3];
} ROS_tim_pin;

typedef struct
{
	void (*func)(void);
	TIM_HandleTypeDef* htim;
} ROS_IRQ_callback;

typedef struct {
	const ROS_tim_channel* channel;
	ROS_pin pin;
	uint64_t range;
} ROS_defined_pwm;

/****************************************************************************************************
*   Variables
****************************************************************************************************/

/****************************************************************************************************
*   Private Functions
****************************************************************************************************/

void ROS_set_PWM_duty(ROS_pin pin, float duty);
void ROS_start_PWM(ROS_pin pin, uint64_t range, uint64_t freq);
void ROS_start_interupt(void (*callback)(void), uint64_t period);

#endif /* ROS_TIM_PUB_H */
