#include "main.h"
#include "port_config.hpp"
using namespace pros;
using namespace pros::c;

extern "C" {
  #include "gui.h"
}

void initialize() {
  vision_clear_led(13);
  delay(10);
  gui();
}

void disabled() {}

void competition_initialize() {}
