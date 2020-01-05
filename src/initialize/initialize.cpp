#include "main.h"
#include "port_config.hpp"

extern "C" {
  #include "gui.h"
  #include "vision.h"
}

void
initialize(void) {
  initVisionSensor();
  setVisionSig();
  pros::delay(10);
  gui();
}

void
disabled(void) {}

void
competition_initialize(void) {}
