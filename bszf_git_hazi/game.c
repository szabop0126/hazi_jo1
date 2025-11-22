#include "snake.h"
#include "usart.h"

void gameTick(void){
  updateSnake(usartValue);
  usartValue = 'x';
  drawSnake();
}

