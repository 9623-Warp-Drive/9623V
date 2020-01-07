#include "main.h"
#include "vision.h"

void
initVisionSensor() {
  vision_clear_led(VISION_PORT);
  vision_set_led(VISION_PORT, COLOR_MAGENTA);
  vision_set_exposure(VISION_PORT, 50);
  vision_set_zero_point(VISION_PORT, E_VISION_ZERO_CENTER);
  vision_set_auto_white_balance(VISION_PORT, true);
}

void
setVisionSig(void) {
  vision_signature_s_t GREEN_SIG = GREEN_UTIL_SIG;
  vision_signature_s_t ORANGE_SIG = ORANGE_UTIL_SIG;
  vision_signature_s_t PURPLE_SIG = PURPLE_UTIL_SIG;
  vision_signature_s_t BLUE_ZONE_SIG = BLUE_ZONE_UTIL_SIG;
  vision_signature_s_t RED_ZONE_SIG = RED_ZONE_UTIL_SIG;

  vision_set_signature(VISION_PORT, GREEN_SIG_NUM, &GREEN_SIG);
  vision_set_signature(VISION_PORT, ORANGE_SIG_NUM, &ORANGE_SIG);
  vision_set_signature(VISION_PORT, PURPLE_SIG_NUM, &PURPLE_SIG);
  vision_set_signature(VISION_PORT, BLUE_ZONE_SIG_NUM, &BLUE_ZONE_SIG);
  vision_set_signature(VISION_PORT, RED_ZONE_SIG_NUM, &RED_ZONE_SIG);
}

int
setStartingPos(void) {
  vision_object_s_t targetCube = vision_get_by_size(VISION_PORT, 0);
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

float
getErrorDist(void) {
  vision_object_s_t targetCube = vision_get_by_size(VISION_PORT, 0);
  return targetCube.x_middle_coord - E_VISION_ZERO_CENTER;
}
