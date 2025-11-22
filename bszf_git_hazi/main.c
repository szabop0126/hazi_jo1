/***************************************************************************//**
 * @file main.c
 * @brief main() function.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "em_device.h"
#include "em_gpio.h"
#include "stdio.h"
#include "usart.h"


int main(void)
{
  usartInit();
  while(1){
      if(usartValue == 'b'){
            USART_Tx(UART0,'<');
            usartValue = 'x';
      } else if (usartValue == 'j'){
            USART_Tx(UART0,'>');
            usartValue = 'x';
      }
  }
}
