///**
//  ******************************************************************************
//  * @file    LwIP/LwIP_UDPP_Echo_Client/LWIP/App/udp_echoclient.c
//  * @author  MCD Application Team
//  * @brief   tcp echoclient application using LwIP RAW API
//  ******************************************************************************
//  * @attention
//  *
//  * Copyright (c) 2024 STMicroelectronics.
//  * All rights reserved.
//  *
//  * This software is licensed under terms that can be found in the LICENSE file
//  * in the root directory of this software component.
//  * If no LICENSE file comes with this software, it is provided AS-IS.
//  *
//  ******************************************************************************
//  */
//
///* Includes ------------------------------------------------------------------*/
//#include "main.h"
//#include "lwip/pbuf.h"
//#include "lwip/udp.h"
//#include "lwip/tcp.h"
//#include <stdio.h>
//#include <string.h>
//#include "udp_echoclient.h"
//
//struct udp_pcb *upcb;
//UDP_Packet_t tx_packet;
//UDP_Packet_t rx_packet;
//
//
///* Private typedef -----------------------------------------------------------*/
///* Private define ------------------------------------------------------------*/
///* Private macro -------------------------------------------------------------*/
///* Private variables ---------------------------------------------------------*/
///* Private function prototypes -----------------------------------------------*/
//void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
//
//void Custom_UDP_Init(void) {
//   ip_addr_t DestIPaddr;
//
//   /* Create a new UDP control block */
//   upcb = udp_new();
//
//   if (upcb != NULL) {
//      /* Bind STM32 to its local port */
//      udp_bind(upcb, IP_ADDR_ANY, UDP_CLIENT_PORT);
//
//      /* Set the Laptop's destination IP */
//      IP4_ADDR(&DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3);
//
//      /* Connect to the remote laptop port */
//      udp_connect(upcb, &DestIPaddr, UDP_SERVER_PORT);
//
//      /* Register the Receive Callback function */
//      udp_recv(upcb, udp_receive_callback, NULL);
//   }
//}
//
//void Custom_UDP_Send(void) {
//   struct pbuf *p;
//
//   // Prepare structural data
//   static uint32_t id_counter = 0;
//   tx_packet.message_id = id_counter++;
//   tx_packet.sensor_value = 23.5f; // Simulation data
//   strncpy(tx_packet.status_flag, "OK", sizeof(tx_packet.status_flag));
//
//   /* Allocate standard packet buffer */
//   p = pbuf_alloc(PBUF_TRANSPORT, sizeof(UDP_Packet_t), PBUF_RAM);
//
//   if (p != NULL) {
//      /* Copy struct data into pbuf payload */
//      pbuf_take(p, &tx_packet, sizeof(UDP_Packet_t));
//
//      /* Send the packet */
//      udp_send(upcb, p);
//
//      /* Free the allocated payload buffer memory */
//      pbuf_free(p);
//   }
//}
//
//u8_t data[100];
//__IO uint32_t message_count = 0;
//struct udp_pcb *upcb;
//
//
///* Private functions ---------------------------------------------------------*/
//
///**
//  * @brief  Connect to UDP echo server
//  * @param  None
//  * @retval None
//  */
//void udp_echoclient_connect(void)
//{
//  ip_addr_t DestIPaddr;
//  err_t err;
//
//  /* Create a new UDP control block  */
//  upcb = udp_new();
//
//  if (upcb!=NULL)
//  {
//    /*assign destination IP address */
//    IP4_ADDR( &DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3 );
//
//    /* configure destination IP address and port */
//    err= udp_connect(upcb, &DestIPaddr, UDP_SERVER_PORT);
//
//    if (err == ERR_OK)
//    {
//      /* Set a receive callback for the upcb */
//      udp_recv(upcb, udp_receive_callback, NULL);
//    }
//  }
//}
//
///**
//  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
//  * @param arg user supplied argument (udp_pcb.recv_arg)
//  * @param pcb the udp_pcb which received data
//  * @param p the packet buffer that was received
//  * @param addr the remote IP address from which the packet was received
//  * @param port the remote port from which the packet was received
//  * @retval None
//  */
//void udp_echoclient_send(void)
//{
//  struct pbuf *p;
//
//  BSP_LED_Off(LED_GREEN);
//
//  sprintf((char*)data, "Sending UDP Client Message %d", (int)message_count);
//
//  /* allocate pbuf from pool*/
//  p = pbuf_alloc(PBUF_TRANSPORT,strlen((char*)data), PBUF_RAM);
//
//  if (p != NULL)
//  {
//    /* copy data to pbuf */
//    pbuf_take(p, (char*)data, strlen((char*)data));
//
//    /* send udp data */
//    udp_send(upcb, p);
//
//    /* free pbuf */
//    pbuf_free(p);
//  }
//}
//
///**
//  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
//  * @param arg user supplied argument (udp_pcb.recv_arg)
//  * @param pcb the udp_pcb which received data
//  * @param p the packet buffer that was received
//  * @param addr the remote IP address from which the packet was received
//  * @param port the remote port from which the packet was received
//  * @retval None
//  */
//void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
//{
////  /* notify the user*/
////  printf("Received %lu message(s) from UDP server\r\n",(uint32_t)message_count);
////  BSP_LED_On(LED_GREEN);
////
////  /*increment message count */
////  message_count++;
////
////  /* Free receive pbuf */
////  pbuf_free(p);
//	if (p->len == sizeof(UDP_Packet_t)) {
//	      /* Copy incoming payload into memory mapped struct */
//	      pbuf_copy_partial(p, &rx_packet, sizeof(UDP_Packet_t), 0);
//
//	      /* PARSING STEP */
//	      uint32_t received_id = rx_packet.message_id;
//	      float received_val = rx_packet.sensor_value;
//
//	      // Perform an action based on parsed values
//	      if (strcmp(rx_packet.status_flag, "LED") == 0) {
//	          // Toggle a NUCLEO onboard LED to verify success
//	          HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
//	      }
//	   }
//	pbuf_free(p);
//}
//
//
/* Deprecated - Custom UDP implementation has been moved directly to main.c */
