#ifndef _COLOR_SIG_
#define _COLOR_SIG_

#include "pros/vision.h"
#include "pros/colors.h"

void initVisionSensor(void);
void setVisionSig(void);
int objectNum(void);
float errorDist(void);

#endif /* ifndef COLOR_SIG */
