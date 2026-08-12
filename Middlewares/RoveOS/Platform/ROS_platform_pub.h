#ifndef ROS_PLATFORM_PUB_H
#define ROS_PLATFORM_PUB_H

/****************************************************************************************************
*                                                                                     ▄▄▄,/,
*   ROS_platform_pub.h                                                              ▄▀  ,/▄
*                                                                                  ▐▌ ,/' ▐▌
*   Includes platform-specific private headers.                                    /▀/'  ▄▀
*                                                                                  └' ▀▀▀
****************************************************************************************************/

/****************************************************************************************************
*   Includes
****************************************************************************************************/
/*  Public   */
/*  Private  */
#include "ROS_config.h"

#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H5xxxx)
#include "Nucleo_H5\ROS_plat_nucleo_h5_prv.h"
#elif (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
#include "RoveNode_H5\ROS_plat_rovenode_h5_prv.h"
#elif (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_F4xxxx)
#include "Nucleo_F4\ROS_plat_nucleo_f4_prv.h"
#endif

#endif /* ROS_PLATFORM_PUB_H */