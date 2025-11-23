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
  Dir_e dir;                                    //a kígyó jelenlegi iránya
  SegmentLCD_LowerCharSegments_TypeDef body[7]; //a kígyó egész teste
  SegmentLCD_LowerCharSegments_TypeDef head[7]; //a kígyó feje
  SegmentLCD_LowerCharSegments_TypeDef end[7];  // a kígyó testének vége
  uint8_t length;                               //jelenleg milyen hosszú
}Snake_s;

extern Snake_s snake;

//függvények
void initSnake(void);
void generateFood(void);
void drawFoodAndSnake(void);

//segédfüggvények
void generateCurrentState(void);

#endif
