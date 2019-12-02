#include "main.h"

void autonomous() {
  // set brake mode
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Tower.setBrakeMode(AbstractMotor::brakeMode::hold);
  Diff.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Slide.set_brake_mode(MOTOR_BRAKE_BRAKE);

  // set speed
  Intake.setMaxVelocity(600);
  Tower.setMaxVelocity(25);
  Drive.setMaxVelocity(600);

  // Autonomous phase
  switch (auton) {
    case 1: {
              controller.print(2,0, "Run: [TOP RED]");
              break;
            }
    case 2: {
              controller.print(2,0, "Run: [BOT RED]");
              break;
            }
    case 3: {
              controller.print(2,0, "Run: [TOP BLUE]");
              break;
            }
    case 4: {
              controller.print(2,0, "Run: [BOT BLUE]");
              break;
            }
    case 5: {
              controller.print(2,0, "Run: [Skills]");
              break;
            }
  }
}
