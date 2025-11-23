/**
 * @file game.c
 * @brief A gameTick függvény megvalósítása és a játék állapotának tárolása.
 */
#include "snake.h"
#include "usart.h"
#include "sl_udelay.h"

volatile bool gameOver = false; ///<A játék jelenleg tart vagy véget ért.

/**
 * @brief A függvény ellenőrzi, hogy ütközött-e, majd frissít eszerint a játék állapotát.
 */
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

