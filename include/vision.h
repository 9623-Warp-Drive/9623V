#ifndef _COLOR_SIG_
#define _COLOR_SIG_

#define VISION_PORT 13

#define BLUE_SIG_NUM 1
#define ORANGE_SIG_NUM 2
#define PURPLE_SIG_NUM 3
#define BLUE_ZONE_SIG_NUM 4
#define RED_ZONE_SIG_NUM 5

void initVisionSensor(void);
void setVisionSig(void);
int setStartingPos(void);
int getObjectNum(void);

#endif /* ifndef COLOR_SIG */
