#include "snake.h"
#include "usart.h"
#include "sl_udelay.h"

volatile bool gameOver = false;

void gameTick(void){
  gameOver = checkCollision();

  if(false == gameOver){
      showPoints();
      updateSnake();
      drawFoodAndSnake();
      sl_udelay_wait(500000);
  } else if(true == gameOver){
      sl_udelay_wait(500000);
      gameOverBlink();
  }
}

