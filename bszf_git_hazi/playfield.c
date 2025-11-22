#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "segmentlcdconfig.h"

SegmentLCD_LowerCharSegments_TypeDef playfield[7] = {0};

void initPlayfield(void){
  SegmentLCD_Init(false);
  SegmentLCD_AllOff();
}
