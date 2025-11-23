/**
 * @file points.c
 * @brief Kezeli a pontokat és a játék végén a pontok villogtatását.
 */
#include "points.h"
#include "snake.h"
#include "segmentlcd_individual.h"
#include "segmentlcd.h"
#include "em_msc.h"

/**
 * @brief Ez fogja villogtatás alapját adni.
 */
void gameOverBlink(void){
  static bool state = false;
  state = !state;
  gameOverLED(state);
}

/**
 * @brief A villogtatás megvalósítása.
 * @param state Milyen állapotban vannak épp a pontok.
 */
void gameOverLED(int state){
  for(int i = 0; i < 5; i++){
      SegmentLCD_Symbol(gameOverLEDs[i], state);
  }
}

/**
 * @brief Kijelzi, hogy jelenleg milyen hosszú a kígyó.
 */
void showPoints(void){
  SegmentLCD_Number(snake.length);
}
