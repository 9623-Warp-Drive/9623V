#include "main.h"
#include "port_config.hpp"
#include "binding.hpp"

extern "C" {
  #include "gui.h"
}

void opcontrol() {
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(AbstractMotor::brakeMode::hold);

  Drive.setMaxVelocity(100);
  Lift.setMaxVelocity(20);
  Intake.setMaxVelocity(600);

  controller.clear_line(2);

  binding b;

  while (true) {
    b.drive();
    b.lift();
    b.intake();
    b.slide();

    pros::delay(1);
  }
}
