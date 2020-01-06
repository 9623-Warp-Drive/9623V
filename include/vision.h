#ifndef _COLOR_SIG_
#define _COLOR_SIG_

#define VISION_PORT 13

extern const char SIG_NUM[5];

void initVisionSensor(void);
void setVisionSig(void);
int setStartingPos(void);
int getObjectNum(void);

#endif /* ifndef COLOR_SIG */
