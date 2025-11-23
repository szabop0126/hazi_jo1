#include "snake.h"
#include "segmentlcd_individual.h"
#include "segmentlcd.h"

Snake_s snake;
SegmentLCD_LowerCharSegments_TypeDef foodPos[7] = {0};
SegmentLCD_LowerCharSegments_TypeDef currentState[7] = {0};
uint8_t foodDigit;
uint8_t foodSegment;
Dir_e prevDir;

void initSnake(void){

  //kígyó kezdőhelyzete
  snake.body[0].g = 1;
  snake.body[0].m = 1;

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

      if(foodPos[randDigit].a != snake.body[randDigit].a ||
          foodPos[randDigit].b != snake.body[randDigit].b ||
          foodPos[randDigit].c != snake.body[randDigit].c ||
          foodPos[randDigit].d != snake.body[randDigit].d ||
          foodPos[randDigit].e != snake.body[randDigit].e ||
          foodPos[randDigit].f != snake.body[randDigit].f ||
          foodPos[randDigit].g != snake.body[randDigit].g){
          validFood = true;
          foodDigit = randDigit;
          foodSegment = randSeg;
      }
  }
}

void drawFoodAndSnake(void){
  generateCurrentState();
  SegmentLCD_LowerSegments(currentState);
}

void moveSnake(void){
  switch(snake.dir){
    case RIGHT: moveSnakeRight();
      break;
  }
}


//segédfüggvények
void moveSnakeRight(void){
  uint8_t i;
  uint8_t j;

  //megkeressük, hogy jelenleg hol van a kígyó feje
  for(i = 0; i < 7; i++){
      if(0 != snake.head[i].raw)
          break;
  }

  //megkeressük, hogy hol van jelenleg a kígyó vége
  for(j = 0; i < 7; i++){
        if(0 != snake.head[j].raw)
            break;
    }


  if(prevDir == snake.dir){
      //kígyó fejének áthelyezése
      if(6 >= i+1){
          snake.head[i+1].raw = snake.head[i].raw;
          snake.head[i].raw = 0;
      } else if(6 < i+1){
          snake.head[0].raw = snake.head[i].raw;
          snake.head[i].raw = 0;
      }

  } else if (prevDir != snake.dir){
      //ha a kígyó eredetileg felfele tartott
      if(UP == prevDir){
          if(1 == snake.head[i].e){
              snake.head[i].raw = 0;
              snake.head[i].g = 1;
              snake.head[i].m = 1;
          } else if (1 == snake.head[i].f){
              snake.head[i].raw = 0;
              snake.head[i].a = 1;
          } else if(1 == snake.head[i].c){
              snake.head[i].raw = 0;
              snake.head[0].g = 1;
              snake.head[0].f = 1;
          } else if(1 == snake.head[i].b){
              snake.head[i].raw = 0;
              snake.head[0].a = 1;
          }
      }

      //ha kígyó ereditleg lefele tartott
      if(DOWN == snake.dir){
          if(1 == snake.head[i].e){
              if(0 == i){
                  snake.head[0].raw = 0;
                  snake.head[6].d = 1;
              } else {
                  snake.head[i].raw = 0;
                  snake.head[i-1].d = 1;
              }
          } else if(1 == snake.head[i].f){
              if(0 == i){
                  snake.head[0].raw = 0;
                  snake.head[6].g = 1;
                  snake.head[6].m = 1;
              } else {
                  snake.head[i].raw = 0;
                  snake.head[i-1].g = 1;
                  snake.head[i-1].m = 1;
              }
          } else if (1 == snake.head[i].b){
              snake.head[i].raw = 0;
              snake.head[i].g = 1;
              snake.head[i].m = 1;
          } else if(1 == snake.head[i].c){
              snake.head[i].raw = 0;
              snake.head[i].d = 1;
          }
      }

      //ha erediteleg balra tartott
      if(LEFT == snake.dir){
          if(1 == snake.head[i].d){
              snake.head[i].raw = 0;
              snake.head[i].e = 1;
          } else if(1 == snake.head[i].g){
              snake.head[i].raw = 0;
              snake.head[i].f = 1;
          } else if(1 == snake.head[i].a){
              snake.head[i].raw = 0;
              snake.head[i].e = 1;
          }
      }
  }

  //összerakjuk az "új testet"
  snake.body[i].raw = snake.body[i].raw || snake.head[i].raw

  //vizsgáljuk, hogy ételt ért-e a feje
  if(!checkFood()){
      snake.body[j].raw = snake.body[j].raw && ~(snake.head[j].raw);
      snake.
  }


}

void generateCurrentState(void){
  //a kígyó testének átmásolás
  for(uint8_t i = 0; i < 7; i++){
      currentState[i] = snake.body[i];
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




