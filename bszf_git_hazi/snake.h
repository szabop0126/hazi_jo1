/**
 * @file snake.h
 * @brief A kígyó struktúrái és annak kezelő függvényeinek fejléce.
 */

#ifndef SNAKE_H
#define SNAKE_H

#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include <stdint.h>


#define SNAKE_MAX_LENGTH 50 ///< A kígyó max hossza. Ilyen hosszú valóban nem lehet.

/**
 * @brief A képernyőn milyen irányba halad a kígyó.
 */
typedef enum {
  UP,  /**< Fel */
  DOWN,/**< Le */
  LEFT,/**< Balra */
  RIGHT/**< Jobbra */
}Dir_e;

/**
 * @brief A struktúra, amely tárolja a kígyó minden darabkáját.
 */
typedef struct {
  uint8_t digitNum;
  SegmentLCD_LowerCharSegments_TypeDef snakeBody;
}Snake_body_s;

/**
 * @brief A kígyó struktúrája.
 * @note Tárolja a kígyó irányát, a kígyó "darabkáit", a kígyó fejének pozícióját és a hosszát.
 */
typedef struct {
  Dir_e dir;                                    //a kígyó jelenlegi iránya
  Snake_body_s snakePart[SNAKE_MAX_LENGTH];
  SegmentLCD_LowerCharSegments_TypeDef head[7]; //a kígyó feje
  SegmentLCD_LowerCharSegments_TypeDef end[7];  // a kígyó testének vége
  uint8_t length;                               //jelenleg milyen hosszú
}Snake_s;

extern Snake_s snake;


void initSnake(void);
void generateFood(void);
void drawFoodAndSnake(void);
void moveSnake(void);
void updateSnake(void);


void generateCurrentState(void);
void updateDirection(void);
bool checkFood(void);
bool checkCollision(void);

#endif
