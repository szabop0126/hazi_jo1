#ifndef USART_H
#define USART_H

extern volatile char usartValue;
extern volatile bool newDir;

void usartInit(void);
void UART0_RX_IRQHandler(void);
void GetChar(void);

#endif
