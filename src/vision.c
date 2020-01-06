#include "main.h"
#include "vision.h"

const char SIG_NUM[5] = { 1, 2, 3, 4, 5 };

void
initVisionSensor() {
  vision_clear_led(VISION_PORT);
  vision_set_led(VISION_PORT, COLOR_MAGENTA);
  vision_set_zero_point(VISION_PORT, E_VISION_ZERO_CENTER);
  vision_set_auto_white_balance(VISION_PORT, true);

}

inline void
setVisionSig(void) {
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

int
setStartingPos(void) {
  vision_object_s_t targetCube = vision_get_by_sig(VISION_PORT, 0, SIG_NUM[0]);
  if (targetCube.x_middle_coord == E_VISION_ZERO_CENTER) {
    return 1;
  }
  else {
    return 0;
  }
}

int
getObjectNum(void) {
  return vision_get_object_count(VISION_PORT);
}
