/**
 * @file main.c
 * @brief Inicializálja a hardver perifériáit, a kígyót és folyamatosan futtatja a gameTick()-t.
 *
 */

#include "em_device.h"
#include "em_gpio.h"
#include "stdio.h"
#include "usart.h"
#include "snake.h"
#include "game.h"

//főprogram
int main(void)
{
  usartInit();
  initPlayfield();
  initSnake();
  while(1){
      gameTick();

  }
}
