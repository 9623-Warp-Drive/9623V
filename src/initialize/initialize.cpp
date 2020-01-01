#include "main.h"
#include "port_config.hpp"

extern "C" {
  #include "gui.h"
}

void
initialize(void) {
  pros::c::vision_clear_led(13);
  pros::delay(10);
  gui();
}

void
disabled(void) {}

void
competition_initialize(void) {}
