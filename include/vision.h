#ifndef _COLOR_SIG_
#define _COLOR_SIG_

#define VISION_PORT 13

#define SIG_1 1
#define SIG_2 2
#define SIG_3 3
#define SIG_4 4
#define SIG_5 5

#define BLUE_UTIL_SIG vision_signature_from_utility(SIG_1, 0, 0, 0, 0, 0, 0, 0, 0)
#define ORANGE_UTIL_SIG vision_signature_from_utility(SIG_2, 0, 0, 0, 0, 0, 0, 0, 0)
#define PURPLE_UTIL_SIG vision_signature_from_utility(SIG_3, 0, 0, 0, 0, 0, 0, 0, 0)
#define BLUE_ZONE_UTIL_SIG vision_signature_from_utility(SIG_4, 0, 0, 0, 0, 0, 0, 0, 0)
#define RED_ZONE_UTIL_SIG vision_signature_from_utility(SIG_5, 0, 0, 0, 0, 0, 0, 0, 0)

void setVisionSig(void);
#endif /* ifndef COLOR_SIG */
