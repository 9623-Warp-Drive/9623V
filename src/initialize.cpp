#include "pros.h"

extern "C" {
  #include "gui.h"
  #include "vision.h"
}

void
initialize(void) {
  initVisionSensor();
  setVisionSig();
  gui();
}

void
disabled(void) {}

void
competition_initialize(void) {}
