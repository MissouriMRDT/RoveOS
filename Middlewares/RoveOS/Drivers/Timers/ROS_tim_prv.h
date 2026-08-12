#ifndef ROS_TIM_PRV_H
#define ROS_TIM_PRV_H

/****************************************************************************************************
*                                                                                     ▄▄▄,/,
*   ROS_tim_prv.h                                                                   ▄▀  ,/▄ 
*                                                                                  ▐▌ ,/' ▐▌
*   Defines RoveOS timer private functions.                                        /▀/'  ▄▀ 
*                                                                                  └' ▀▀▀   
****************************************************************************************************/

/****************************************************************************************************
*   Includes
****************************************************************************************************/
/*  Public   */
#include "ROS_tim_pub.h"
/*  Private  */

/****************************************************************************************************
*   Macros
****************************************************************************************************/
#define NONE_TIM_CHANNEL 0xFFFF
#define NONE_AF_PORT 0xFFFF
#define NONE_TIM {NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}
#define NONE_IRQ 82

/****************************************************************************************************
*   Types
****************************************************************************************************/

/****************************************************************************************************
*   Variables
****************************************************************************************************/
static ROS_IRQ_callback IRQ_callbacks[5] = {0};
static int num_callbacks = 0;

static ROS_defined_pwm defined_pwms[5] = {0};
static int num_pwms = 0;

static const ROS_tim_channel NONE_TIM_CHANNEL_STRUCT = {NONE_TIM_CHANNEL, NONE_AF_PORT, NULL};
static const ROS_defined_pwm NONE_PWM = {&NONE_TIM_CHANNEL_STRUCT, -1, 0};

static TIM_HandleTypeDef timHandlers[20] = {
#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_F4xxxx)
	{.Instance = TIM1}, {.Instance = TIM2}, {.Instance = TIM3},
	{.Instance = TIM4}, {.Instance = TIM5}, {.Instance = TIM6}, {.Instance = TIM7},
	{.Instance = TIM8}, {.Instance = TIM9}, {.Instance = TIM10}, {.Instance = TIM11},
	{.Instance = TIM12}, {.Instance = TIM13}, {.Instance = TIM14}
#elif (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H5xxxx) || (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
	{.Instance = TIM1}, {.Instance = TIM2}, {.Instance = TIM3},
	{.Instance = TIM4}, {.Instance = TIM5}, {.Instance = TIM6}, {.Instance = TIM7},
	{.Instance = TIM8}, {.Instance = TIM12}, {.Instance = TIM13}, {.Instance = TIM14},
	{.Instance = TIM15}, {.Instance = TIM16}, {.Instance = TIM17}
#endif
};

static const ROS_tim_def timdefs[] =
{
#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H5xxxx) || (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
	{&timHandlers[0], NONE_IRQ, 0b00000000}, {&timHandlers[1], TIM2_IRQn, 0b00000001}, {&timHandlers[2], TIM3_IRQn, 0b00000001},
	{&timHandlers[3], TIM4_IRQn, 0b00000001}, {&timHandlers[4], TIM5_IRQn, 0b00000001}, {&timHandlers[5], NONE_IRQ, 0b00000000},
	{&timHandlers[6], NONE_IRQ, 0b00000000}, {&timHandlers[7], TIM12_IRQn, 0b00000001}, {&timHandlers[8], NONE_IRQ, 0b00000000},
	{&timHandlers[9], NONE_IRQ, 0b00000000}, {&timHandlers[10], TIM15_IRQn, 0b00000001}, {&timHandlers[11], TIM16_IRQn, 0b00000001},
	{&timHandlers[12], TIM16_IRQn, 0b00000001}, {&timHandlers[13], TIM17_IRQn, 0b00000001},
#elif (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_F4xxxx)
	{&timHandlers[0], NONE_IRQ, 0b00000000}, {&timHandlers[1], TIM2_IRQn, 0b00000001}, {&timHandlers[2], TIM3_IRQn, 0b00000001},
	{&timHandlers[3], TIM4_IRQn, 0b00000001}, {&timHandlers[4], TIM5_IRQn, 0b00000001}, {&timHandlers[5], NONE_IRQ, 0b00000000},
	{&timHandlers[6], NONE_IRQ, 0b00000000}, {&timHandlers[7], NONE_IRQ, 0b00000000}, {&timHandlers[8], NONE_IRQ, 0b00000000},
	{&timHandlers[9], NONE_IRQ, 0b00000000}, {&timHandlers[10], NONE_IRQ, 0b00000000}, {&timHandlers[11], NONE_IRQ, 0b00000000},
	{&timHandlers[12], NONE_IRQ, 0b00000000}, {&timHandlers[13], NONE_IRQ, 0b00000000},
#endif
};

static const ROS_tim_pin pindefs[] =
{
#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_F4xxxx)
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM2, &timdefs[1]}, {TIM_CHANNEL_1, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM2, &timdefs[1]}, {TIM_CHANNEL_2, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM2, &timdefs[1]}, {TIM_CHANNEL_3, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM2, &timdefs[1]}, {TIM_CHANNEL_4, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},

	{{{TIM_CHANNEL_3, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM3, &timdefs[2]}, {TIM_CHANNEL_1, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM3, &timdefs[2]}, {TIM_CHANNEL_2, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF2_TIM3, &timdefs[2]}, {TIM_CHANNEL_3, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF2_TIM3, &timdefs[2]}, {TIM_CHANNEL_4, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
#elif (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H5xxxx) || (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM2, &timdefs[1]}, {TIM_CHANNEL_1, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM2, &timdefs[1]}, {TIM_CHANNEL_2, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM2, &timdefs[1]}, {TIM_CHANNEL_3, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM2, &timdefs[1]}, {TIM_CHANNEL_4, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},

	{{{TIM_CHANNEL_3, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM3, &timdefs[2]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM16, &timdefs[12]}, {TIM_CHANNEL_3, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM17, &timdefs[13]}, {TIM_CHANNEL_4, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM12, &timdefs[8]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM12, &timdefs[8]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},

	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM17, &timdefs[13]}, {TIM_CHANNEL_4, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM2, &timdefs[1]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM3, &timdefs[2]}, {TIM_CHANNEL_1, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM3, &timdefs[2]}, {TIM_CHANNEL_2, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF2_TIM3, &timdefs[2]}, {TIM_CHANNEL_3, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF2_TIM3, &timdefs[2]}, {TIM_CHANNEL_4, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM15, &timdefs[11]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF2_TIM4, &timdefs[3]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF4_TIM15, &timdefs[11]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF4_TIM15, &timdefs[11]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_4, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM16, &timdefs[12]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF1_TIM17, &timdefs[13]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},

	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM12, &timdefs[8]}, {TIM_CHANNEL_1, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF1_TIM1, &timdefs[0]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF1_TIM1, &timdefs[0]}, {TIM_CHANNEL_2, GPIO_AF2_TIM12, &timdefs[8]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_1, GPIO_AF2_TIM5, &timdefs[4]}, {TIM_CHANNEL_3, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},

	{{{TIM_CHANNEL_4, GPIO_AF2_TIM5, &timdefs[4]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{{{TIM_CHANNEL_4, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{{{TIM_CHANNEL_1, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_2, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{{{TIM_CHANNEL_3, GPIO_AF3_TIM8, &timdefs[7]}, NONE_TIM_CHANNEL_STRUCT, NONE_TIM_CHANNEL_STRUCT}},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
	{NONE_TIM},
#endif
};

/****************************************************************************************************
*   Private Functions
****************************************************************************************************/
void startTIMRCC(const ROS_tim_def* tim);
void initPWMPin(ROS_pin pin, uint64_t range, uint64_t freq, const ROS_tim_channel** channel);
uint64_t getAPBTimerSpeed(TIM_TypeDef* tim);
void initTIM(uint64_t prescaler, uint64_t period, const ROS_tim_def* tim);
uint16_t findFactors(uint64_t product);
int16_t getAvailibleTIM(uint8_t reqs);
void initTIMInterrupt(void (*callback)(), uint64_t period);
void ROS_start_PWM(ROS_pin pin, uint64_t range, uint64_t freq);
ROS_defined_pwm* pwmFromPin(ROS_pin pin);
void ROS_set_PWM_duty(ROS_pin pin, float duty);

//these could probably be moved to another file, these are just used to handle the interrupt setup.
#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_F4xxxx)
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
#elif (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H5xxxx) || (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
void TIM12_IRQHandler(void);
void TIM15_IRQHandler(void);
void TIM16_IRQHandler(void);
void TIM17_IRQHandler(void);
#endif

#endif /* ROS_TIM_PRV_H */
