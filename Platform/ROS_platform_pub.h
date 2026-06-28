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
#include "ROS_config.h"

#if (ROS_PLATFORM == ROS_PLATFORM_NUCLEO_H563ZI)
#include "ROS_plat_nucleo_prv.h"
#elif (ROS_PLATFORM == ROS_PLATFORM_ROVENODE_H5)
#include "ROS_plat_rovenode_prv.h"
#endif

#endif /* ROS_PLATFORM_PUB_H */