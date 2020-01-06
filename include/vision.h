#ifndef _COLOR_SIG_
#define _COLOR_SIG_

#define VISION_PORT 13

#define GREEN_SIG_NUM 1
#define ORANGE_SIG_NUM 2
#define PURPLE_SIG_NUM 3
#define BLUE_ZONE_SIG_NUM 4
#define RED_ZONE_SIG_NUM 5

#define GREEN_UTIL_SIG vision_signature_from_utility(GREEN_SIG_NUM, 0, 0, 0, 0, 0, 0, 0, 0)
#define ORANGE_UTIL_SIG vision_signature_from_utility(ORANGE_SIG_NUM, 0, 0, 0, 0, 0, 0, 0, 0)
#define PURPLE_UTIL_SIG vision_signature_from_utility(PURPLE_SIG_NUM, 0, 0, 0, 0, 0, 0, 0, 0)
#define BLUE_ZONE_UTIL_SIG vision_signature_from_utility(BLUE_ZONE_SIG_NUM, 0, 0, 0, 0, 0, 0, 0, 0)
#define RED_ZONE_UTIL_SIG vision_signature_from_utility(RED_ZONE_SIG_NUM, 0, 0, 0, 0, 0, 0, 0, 0)

void initVisionSensor(void);
void setVisionSig(void);
int setStartingPos(void);
int getObjectNum(void);

#endif /* ifndef COLOR_SIG */
