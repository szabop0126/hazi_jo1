/**
 * @file playfield.c
 * @brief A pálya alapbeállítása.
 */
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "segmentlcdconfig.h"

SegmentLCD_LowerCharSegments_TypeDef playfield[7] = {0}; ///< Üres LCD kijelző.

/**
 * @brief Inicializál, majd törli az LCD kijelző tartalmát.
 */
void initPlayfield(void){
  SegmentLCD_Init(false);
  SegmentLCD_AllOff();
}
