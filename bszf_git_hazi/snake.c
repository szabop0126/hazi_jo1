#include "snake.h"
#include "segmentlcd_individual.h"
#include "segmentlcd.h"
#include "usart.h"

Snake_s snake;
SegmentLCD_LowerCharSegments_TypeDef foodPos[7] = {0};
SegmentLCD_LowerCharSegments_TypeDef currentState[7] = {0};
uint8_t foodDigit;
uint8_t foodSegment;
Dir_e prevDir;

void initSnake(void){
  //alaphelyzetre állítás ha már volt egy játék
  for(uint8_t i = 0; i < SNAKE_MAX_LENGTH; i++){
      snake.snakePart[i].digitNum = 0;
      snake.snakePart[i].snakeBody.raw = 0;
  }

  for(uint8_t i = 0; i < 7; i++){
      snake.head[i].raw = 0;
      snake.end[i].raw = 0;
  }

  for(uint8_t i = 0; i < 7; i++){
      foodPos[i].raw = 0;
  }

  snake.dir = RIGHT;
  snake.length = 0;


  //kígyó kezdőhelyzete
  snake.snakePart[0].snakeBody.g = 1;
  snake.snakePart[0].snakeBody.m = 1;
  snake.snakePart[0].digitNum = 1;

  //a kígyó fejének beállítása
  snake.head[0].g = 1;
  snake.head[0].m = 1;

  //a kígyó testének vége
  snake.end[0].g = 1;
  snake.end[0].m = 1;

  //hossz beállítása
  snake.length = 1;

  //az irány beállítása
  prevDir = RIGHT;
  snake.dir = RIGHT;

  //random étel generálása
  generateFood();
  drawFoodAndSnake();
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
        case 5: foodPos[randDigit].c = 1;
          break;
        case 6: foodPos[randDigit].b = 1;
          break;
      }

      validFood = true;
      foodDigit = randDigit;
      foodSegment = randSeg;

      for(uint8_t i = 0; i < SNAKE_MAX_LENGTH; i++){
          if(randDigit == snake.snakePart[i].digitNum){
              if(foodPos[randDigit].raw == snake.snakePart[i].snakeBody.raw){
                  validFood = false;
                  foodDigit = 0;
                  foodSegment = 0;
              }
          }
      }
  }
}

void drawFoodAndSnake(void){
  generateCurrentState();
  SegmentLCD_LowerSegments(currentState);
}

void moveSnake(void){
  if(prevDir == snake.dir){
      switch(snake.dir){
        case UP:


      }
  } else if(prevDir != snake.dir){

  }
}


//segédfüggvények
void updateDirection(void){
  prevDir = snake.dir;
  switch (usartValue){
    case 'b':
      if(UP == snake.dir){
          snake.dir = LEFT;
      } else if(DOWN == snake.dir){
          snake.dir = RIGHT;
      } else if(LEFT == snake.dir){
          snake.dir = DOWN;
      } else if(RIGHT == snake.dir){
          snake.dir = UP;
      }
      break;
    case 'j':
      if(UP == snake.dir){
          snake.dir = RIGHT;
      } else if(DOWN == snake.dir){
          snake.dir = LEFT;
      } else if(LEFT == snake.dir){
          snake.dir = UP;
      } else if(RIGHT == snake.dir){
          snake.dir = DOWN;
      }
      break;
    default:
      break;
  }
}

void generateCurrentState(void){
  for(uint8_t i = 0; i < 7; i++)
    currentState[i].raw = 0;

  //a kígyó testének átmásolás
  for(uint8_t i = 0; i < SNAKE_MAX_LENGTH; i++){
      switch (snake.snakePart[i].digitNum){
        case 1: currentState[0].raw |= snake.snakePart[i].snakeBody.raw;
        break;
        case 2: currentState[1].raw |= snake.snakePart[i].snakeBody.raw;
        break;
        case 3: currentState[2].raw |= snake.snakePart[i].snakeBody.raw;
        break;
        case 4: currentState[3].raw |= snake.snakePart[i].snakeBody.raw;
        break;
        case 5: currentState[4].raw |= snake.snakePart[i].snakeBody.raw;
        break;
        case 6: currentState[5].raw |= snake.snakePart[i].snakeBody.raw;
        break;
        case 7: currentState[6].raw |= snake.snakePart[i].snakeBody.raw;
        break;
      }
  }

  //az étel bemásolás
  switch(foodSegment){
    case 0: currentState[foodDigit].e = 1;
      break;
    case 1: currentState[foodDigit].f = 1;
      break;
    case 2: currentState[foodDigit].g = 1;
            currentState[foodDigit].m = 1;
      break;
    case 3: currentState[foodDigit].a = 1;
      break;
    case 4: currentState[foodDigit].d = 1;
      break;
    case 5: currentState[foodDigit].c = 1;
      break;
    case 6: currentState[foodDigit].b = 1;
      break;
  }
}

bool checkFood(void){
  bool headOnFood = false;

  for (uint8_t i = 0; i < 7; i++){
      if(snake.head[i].raw == foodPos[i].raw){
          headOnFood = true;
      }
  }

  return headOnFood;
}

bool checkCollision(void){

}




