/**
 * @file points.h
 * @brief A pontszámláló segédtömbje és kezelő függvényei.
 */
#ifndef POINTS_H
#define POINTS_H

#include "segmentlcdconfig.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

/**
 * @brief Tárolja, hogy milyen LCD szimbolúmokat kell majd villogtatni.
 */
static const lcdSymbol gameOverLEDs[] = {
    LCD_SYMBOL_DP2,
    LCD_SYMBOL_DP3,
    LCD_SYMBOL_DP4,
    LCD_SYMBOL_DP5,
    LCD_SYMBOL_DP6
};

/**
 * @brief A tömb hosszát meghatározza. így később lehet változatni, hogy pont villogjon.
 */
static const int gameOverLEDCount = sizeof(gameOverLEDs)/sizeof(gameOverLEDs[0]);

void gameOverLED(int state);

void gameOverBlink(void);

void showPoints(void);

#endif
