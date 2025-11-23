/**
 * @file usart.c
 * @brief Az USART kezelése.
 */
#include "em_usart.h"
#include <stdbool.h>
#include "em_cmu.h"
#include "em_gpio.h"
#include "stdio.h"
#include "snake.h"

volatile char usartValue = 'x';       ///< Ebben tároljuk a soros porton érkező karaktert.
volatile bool progressed = true;      ///< Ezzel tartjuk számon, hogy a mozgatás teljesen végbement és nem zavar bele az új karakter.


/**
 * @brief Inicializálja a USART-t.
 *
 * Beállítja az órajelet, a megfelelő perifériákra rákapcsolja.
 * Megfelelően beállítja az USART részeit: location,interrupt.
 *
 */
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

/**
 * @brief Kiolvassa a beérkező karaktert.
 */
void GetChar(void){
  usartValue = USART_RxDataGet(UART0);
}
/**
 * @brief A USART interrupt kezelője.
 *
 * Ha karakter érkezik, akkor azt beolvassa.
 */
void UART0_RX_IRQHandler(void){
  if(progressed){
      updateDirection();
      progressed = false;
  }
  USART_IntClear(UART0,_USART_IFC_MASK);
}






