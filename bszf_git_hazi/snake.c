#include "snake.h"
#include "segmentlcd_individual.h"
#include "segmentlcd.h"

Snake_s snake;

void initSnake(void){
  //beállítjuk a kígyó kezdőpontját
  snake.actBod[0].g = 1;
  snake.actBod[0].m = 1;

  //a kígyó alapiránya
  snake.dir = RIGHT;
}

void drawSnake(void){
  SegmentLCD_LowerSegments(snake.actBod);
}

//a kígyó irányának frissítése
void updateSnake(char x){
  if('b' == x){
        switch (snake.dir){
          case UP: snake.dir = LEFT;
            break;
          case DOWN: snake.dir = RIGHT;
             break;
          case LEFT: snake.dir = DOWN;
             break;
          case RIGHT: snake.dir = UP;
             break;
        }
    }

    if('j' == x){
        switch (snake.dir){
          case UP: snake.dir = RIGHT;
            break;
          case DOWN: snake.dir = LEFT;
            break;
          case LEFT: snake.dir = UP;
            break;
          case RIGHT: snake.dir = DOWN;
        }
    }
}

void moveSnake(){

}
