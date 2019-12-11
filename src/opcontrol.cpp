#include "main.h"
#include "port_config.hpp"
#include "binding.hpp"
using namespace pros;

extern "C" {
  void autonomous(void);
}

void opcontrol() {
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(AbstractMotor::brakeMode::hold);
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);

  Intake.setMaxVelocity(600);
  Slide.setMaxVelocity(10);
  Lift.setMaxVelocity(20);
  Drive.setMaxVelocity(200);

  binding b;

  while (true) {
    b.drive();
    b.lift();
    b.intake();
    b.slide();

    delay(1);
  }
}
