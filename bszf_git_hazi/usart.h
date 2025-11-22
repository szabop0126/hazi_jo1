#ifndef USART_H
#define USART_H

extern volatile char usartValue;

void usartInit(void);
void UART0_RX_IRQHandler(void);
void GetChar(void);

#endif
