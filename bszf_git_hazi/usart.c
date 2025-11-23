#include "em_usart.h"
#include <stdbool.h>
#include "em_cmu.h"
#include "em_gpio.h"
#include "stdio.h"
#include "snake.h"

volatile char usartValue = 'x';
volatile bool progressed = true;

void usartInit(void){
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
  GPIO_PinModeSet(gpioPortF,7,gpioModePushPull,1);
  CMU_ClockEnable(cmuClock_GPIO,true);
  CMU_ClockEnable(cmuClock_UART0,true);


  USART_InitAsync_TypeDef UART0_Init = USART_INITASYNC_DEFAULT;
  USART_InitAsync(UART0, &UART0_Init);
  GPIO_PinModeSet(gpioPortE,0,gpioModePushPull,1);
  GPIO_PinModeSet(gpioPortE,1,gpioModeInput,0);
  UART0->ROUTE |= UART_ROUTE_LOCATION_LOC1;
  UART0->ROUTE |= UART_ROUTE_TXPEN | UART_ROUTE_RXPEN;

  USART_IntClear(UART0,_USART_IFC_MASK);
  USART_IntEnable(UART0,USART_IEN_RXDATAV);
  NVIC_ClearPendingIRQ(UART0_RX_IRQn);
  NVIC_EnableIRQ(UART0_RX_IRQn);
}

void GetChar(void){
  usartValue = USART_RxDataGet(UART0);
}

void UART0_RX_IRQHandler(void){
  if(progressed){
      updateDirection();
      progressed = false;
  }
  USART_IntClear(UART0,_USART_IFC_MASK);
}






