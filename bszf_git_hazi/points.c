#include "points.h"
#include "snake.h"
#include "segmentlcd_individual.h"
#include "segmentlcd.h"
#include "em_msc.h"

void gameOverBlink(void){
  static bool state = false;
  state = !state;
  gameOverLED(state);
}

void gameOverLED(int state){
  for(int i = 0; i < 5; i++){
      SegmentLCD_Symbol(gameOverLEDs[i], state);
  }
}

void showPoints(void){
  SegmentLCD_Number(snake.length);
}
