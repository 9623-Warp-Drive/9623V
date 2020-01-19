#include <cerrno>
#include <cstdint>
#include <cstdlib>

#include "pros.h"
#include "pros/rtos.hpp"

extern "C" {
  #include "gui.h"
  #include "vision.h"
}

void
initialize(void) {
  initVisionSensor();
  setVisionSig();
  pros::delay(100);
  gui();
}

void
disabled(void) {}

void
competition_initialize(void) {}
