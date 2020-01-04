#include "main.h"
#include "vision.h"

void
setVisionSig(void) {
  const char SIG_NUM[5] = { 1, 2, 3, 4, 5 };

  vision_signature_s_t BLUE_SIG = vision_signature_from_utility(SIG_NUM[0], 0, 0, 0, 0, 0, 0, 0, 0);
  vision_signature_s_t ORANGE_SIG = vision_signature_from_utility(SIG_NUM[1], 0, 0, 0, 0, 0, 0, 0, 0);
  vision_signature_s_t PURPLE_SIG = vision_signature_from_utility(SIG_NUM[2], 0, 0, 0, 0, 0, 0, 0, 0);
  vision_signature_s_t BLUE_ZONE_SIG = vision_signature_from_utility(SIG_NUM[3], 0, 0, 0, 0, 0, 0, 0, 0);
  vision_signature_s_t RED_ZONE_SIG = vision_signature_from_utility(SIG_NUM[4], 0, 0, 0, 0, 0, 0, 0, 0);

  vision_set_signature(VISION_PORT, SIG_NUM[0], &BLUE_SIG);
  vision_set_signature(VISION_PORT, SIG_NUM[1], &ORANGE_SIG);
  vision_set_signature(VISION_PORT, SIG_NUM[2], &PURPLE_SIG);
  vision_set_signature(VISION_PORT, SIG_NUM[3], &BLUE_ZONE_SIG);
  vision_set_signature(VISION_PORT, SIG_NUM[4], &RED_ZONE_SIG);
}
