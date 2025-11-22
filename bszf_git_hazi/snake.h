#ifndef SNAKE_H
#define SNAKE_H

#include "segmentlcd.h"
#include "segmentlcd_individual.h"


#define SNAKE_MAX_LENGTH 50 //A kígyó max hossza, amit elérhet

//irányok amikbe mozoghat
typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
}Dir_e;

typedef struct {
  Dir_e dir;
  SegmentLCD_LowerCharSegments_TypeDef body[7];
  uint8_t length;
}Snake_s;

extern Snake_s snake;

//függvények
void initSnake(void);
void generateFood(void);
void drawFoodAndSnake(void);

//segédfüggvények

#endif
