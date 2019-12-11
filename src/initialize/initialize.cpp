#include "main.h"
#include "port_config.hpp"
using namespace pros::c;

extern "C" {
  #include "gui.h"
  void gui(void);
}

void initialize() {
  vision_clear_led(13);
  pros::delay(10);
  gui();
}

void disabled() {}

void competition_initialize() {}
