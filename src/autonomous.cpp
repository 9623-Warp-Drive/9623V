#include "main.h"

void autonomous() {
  /* set brake mode */
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Tower.setBrakeMode(AbstractMotor::brakeMode::hold);
  Diff.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Slide.set_brake_mode(MOTOR_BRAKE_BRAKE);

  /* set speed */
  Intake.setMaxVelocity(600);
  Tower.setMaxVelocity(25);
  Drive.setMaxVelocity(600);

  switch (auton) {
    case 1: { /* TOP RED AUTONOMOUS */
              controller.print(2,0, "Run: [TOP RED]");
              break;
            }
    case 2: { /* BOTTOM RED AUTONOMOUS */
              controller.print(2,0, "Run: [BOT RED]");
              Intake.forward(1);
              Drive.moveDistance(4.0_ft);
              // Drive.moveDistance(-3.0_ft);
              // Drive.turnAngle(45.0_deg);
              // Drive.moveDistance(-2.0_ft);
              // Drive.turnAngle(-45.0_deg);
              // Drive.moveDistance(5.0_ft);
              // Drive.moveDistance(-5.0_ft);
              break;
            }
    case 3: { /* TOP BLUE AUTONOMOUS */
              controller.print(2,0, "Run: [TOP BLUE]");
              break;
            }
    case 4: { /* BOTTOM BLUE AUTONOMOUS */
              controller.print(2,0, "Run: [BOT BLUE]");
              Intake.forward(1);
              Drive.moveDistance(4.0_ft);
              // Drive.moveDistance(-3.0_ft);
              // Drive.turnAngle(-45.0_deg);
              // Drive.moveDistance(-2.0_ft);
              // Drive.turnAngle(45.0_deg);
              // Drive.moveDistance(5.0_ft);
              // Drive.moveDistance(-5.0_ft);
              break;
            }
    case 5: { /* SKILL AUTONOMOUS */
              controller.print(2,0, "Run: [SKILLS]");
              Intake.forward(1);
              break;
            }
  }
}
