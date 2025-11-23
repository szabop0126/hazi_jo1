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
  SegmentLCD_LowerCharSegments_TypeDef temp;


  //kígyó fejének megkeresése
  uint8_t i;
  for(i = 0; i < 7; i++){
      if(0 != snake.head[i].raw)
        temp.raw = snake.head[i].raw;
        break;
  }

  snake.head[i].raw = 0;


  if(prevDir == snake.dir){
      switch (snake.dir){
        case UP:
              if (1 == temp.e){
                  snake.head[i].f = 1;
              } else if (1 == temp.f){
                  snake.head[i].e = 1;
              } else if (1 == temp.c){
                  snake.head[i].b = 1;
              } else if (1 == temp.b){
                  snake.head[i].c = 1;
              }
          break;
        case DOWN:
              if (1 == temp.e){
                  snake.head[i].f = 1;
              } else if (1 == temp.f){
                  snake.head[i].e = 1;
              } else if (1 == temp.c){
                  snake.head[i].b = 1;
              } else if (1 == temp.b){
                  snake.head[i].c = 1;
              }
          break;
        case LEFT:
              if (1 == temp.a){
                  if (0 == i){
                      snake.head[6].a = 1;
                  } else {
                      snake.head[i - 1].a = 1;
                  }
              } else if (1 == temp.g){
                  if (0 == i){
                      snake.head[6].g = 1;
                      snake.head[6].m = 1;
                  } else {
                      snake.head[i - 1].g = 1;
                      snake.head[i - 1].m = 1;
                  }
              } else if (1 == temp.d){
                  if (0 == i){
                      snake.head[6].d = 1;
                  } else {
                      snake.head[i - 1].d = 1;
                  }
              }
          break;
        case RIGHT:
              if (1 == temp.a){
                  if (6 == i){
                      snake.head[0].a = 1;
                  } else {
                      snake.head[i + 1].a = 1;
                  }
              } else if (1 == temp.g){
                  if (6 == i){
                      snake.head[0].g = 1;
                      snake.head[0].m = 1;
                  } else {
                      snake.head[i+1].g = 1;
                      snake.head[i+1].m = 1;
                  }
              } else if(1 == temp.d){
                    if(6 == i){
                        snake.head[0].d = 1;
                    } else {
                        snake.head[i + 1].d = 1;
                    }
              }
          break;

      }
  } else if(prevDir != snake.dir){
      switch (prevDir){
        case UP:
          if(LEFT == snake.dir){
              if(1 == temp.e){
                  if(0 == i){
                      snake.head[6].g = 1;
                      snake.head[6].m = 1;
                  } else {
                      snake.head[i - 1].g = 1;
                      snake.head[i - 1].m = 1;
                  }
              } else if(1 == temp.f){
                  if(0 == i){
                      snake.head[6].a = 1;
                  } else {
                      snake.head[i - 1].a = 1;
                  }
              } else if(1 == temp.c){
                  snake.head[i].g = 1;
                  snake.head[i].m = 1;
              } else if(1 == temp.b){
                  snake.head[i].a = 1;
              }
          } else if(RIGHT == snake.dir){
              if(1 == temp.e){
                  snake.head[i].g = 1;
                  snake.head[i].m = 1;
              } else if(1 == temp.f){
                  snake.head[i].a = 1;
              } else if(1 == temp.c){
                  snake.head[0].g = 1;
                  snake.head[0].m = 1;
              } else if(1 == temp.b){
                  snake.head[0].a = 1;
              }
          }
          break;
        case DOWN:
          if(LEFT == snake.dir){
              if(1 == temp.e){
                  if(0 == i){
                      snake.head[6].d = 1;
                  } else {
                      snake.head[i - 1].d = 1;
                  }
              } else if(1 == temp.f){
                  if(0 == i){
                      snake.head[6].g = 1;
                      snake.head[6].m = 1;
                  } else {
                      snake.head[i - 1].g = 1;
                      snake.head[i - 1].m = 1;
                  }
              } else if(1 == temp.c){
                  snake.head[i].d = 1;
              } else if(1 == temp.b){
                  snake.head[i].g = 1;
                  snake.head[i].m = 1;
              }
          } else if(RIGHT == snake.dir){
              if(1 == temp.e){
                  snake.head[i].d = 1;
              } else if(1 == temp.f){
                  snake.head[i].g = 1;
                  snake.head[i].m = 1;
              } else if(1 == temp.c){
                  snake.head[0].d = 1;
              } else if(1 == temp.b){
                  snake.head[0].g = 1;
                  snake.head[0].m = 1;
              }
          }
          break;
        case LEFT:
          if(UP == snake.dir){
              if(1 == temp.a){
                  snake.head[i].e = 1;
              } else if(1 ==)
          } else if(DOWN == snake.dir){

          }
          break;

      }

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




