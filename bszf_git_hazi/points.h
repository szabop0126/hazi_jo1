#ifndef POINTS_H
#define POINTS_H

#include "segmentlcdconfig.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

static const lcdSymbol gameOverLEDs[] = {
    LCD_SYMBOL_DP2,
    LCD_SYMBOL_DP3,
    LCD_SYMBOL_DP4,
    LCD_SYMBOL_DP5,
    LCD_SYMBOL_DP6
};

static const int gameOverLEDCount = sizeof(gameOverLEDs)/sizeof(gameOverLEDs[0]);

void gameOverLED(int state);

void gameOverBlink(void);

void showPoints(void);

#endif
