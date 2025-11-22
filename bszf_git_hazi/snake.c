#include "snake.h"
#include "segmentlcd_individual.h"
#include "segmentlcd.h"

Snake_s snake;
SegmentLCD_LowerCharSegments_TypeDef foodPos[7] = {0};

void initSnake(void){

  //kígyó kezdőhelyzete
  snake.body[0].g = 1;
  snake.body[0].m = 1;

  //hossz beállítása
  snake.length = 1;
}

void generateFood(void){
  bool validFood = false;

  while(!validFood){
      for(uint8_t i; i < 7; i++){
          foodPos[i].raw = 0;
      }

      int randDigit = rand() % 7;
      int randSeg=-1;

      if(0 <= randDigit && 5 >= randDigit){
          randSeg = rand() % 5;
      } else if(6 == randDigit){
          randSeg = rand() % 7;
      }

      switch(randSeg){
        case 0: foodPos[randDigit].e = 1;
          break;
        case 1: foodPos[randDigit].f = 1;
          break;
        case 2: foodPos[randDigit].g = 1;
                foodPos[randDigit].m = 1;
          break;
        case 3: foodPos[randDigit].a = 1;
          break;
        case 4: foodPos[randDigit].d = 1;
          break;
        case 5: foodPos[randDigit].a = 1;
          break;
        case 6: foodPos[randDigit].b = 1;
          break;
      }

      if(foodPos[randDigit] != snake.body[randDigit]){
          validFood = true;
      }
  }
}





/*
Snake_s snake;
SegmentLCD_LowerCharSegments_TypeDef prevPos[7];




void initSnake(void){
  //beállítjuk a kígyó kezdőpontját
  snake.head[0].g = 1;
  snake.head[0].m = 1;

  //a kígyó alapiránya
  snake.dir = RIGHT;
}

void drawSnake(void){
  SegmentLCD_LowerSegments(snake.head);
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

}*/
