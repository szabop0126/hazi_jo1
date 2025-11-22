#include "snake.h"
#include "usart.h"

void gameTick(void){
  if(newDir){
      newDir = false;
      updateSnake(usartValue);
      usartValue = 'x';
  }
  drawSnake();


}

