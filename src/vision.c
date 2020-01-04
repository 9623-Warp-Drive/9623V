#include "main.h"
#include "vision.h"

void
setVisionSig(void) {
  vision_signature_s_t BLUE_SIG = BLUE_UTIL_SIG;
  vision_signature_s_t ORANGE_SIG = ORANGE_UTIL_SIG;
  vision_signature_s_t PURPLE_SIG = PURPLE_UTIL_SIG;
  vision_signature_s_t BLUE_ZONE_SIG = BLUE_ZONE_UTIL_SIG;
  vision_signature_s_t RED_ZONE_SIG = RED_ZONE_UTIL_SIG;

  vision_set_signature(VISION_PORT, SIG_1, &BLUE_SIG);
  vision_set_signature(VISION_PORT, SIG_2, &ORANGE_SIG);
  vision_set_signature(VISION_PORT, SIG_3, &PURPLE_SIG);
  vision_set_signature(VISION_PORT, SIG_3, &BLUE_ZONE_SIG);
  vision_set_signature(VISION_PORT, SIG_3, &RED_ZONE_SIG);
}
