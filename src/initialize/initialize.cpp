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
disabled(void) {
  while(setStartingPos()) {
    controller.print(2,0, "ready to play!");
  }
}

void
competition_initialize(void) {}
