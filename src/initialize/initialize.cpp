#include "main.h"
#include "port_config.hpp"

extern "C" {
  #include "gui.h"
  void gui(void);
  void setGroot(void);
}

void initialize() {
  pros::delay(10);
  gui();
}

void disabled() {}

void competition_initialize() {}
