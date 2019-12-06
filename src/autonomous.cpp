#include "main.h"

void autonomous() {
  /* set brake mode */
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(AbstractMotor::brakeMode::hold);

  /* set speed */
  Intake.setMaxVelocity(600);
  Lift.setMaxVelocity(75);
  Drive.setMaxVelocity(50);
  Slide.setMaxVelocity(10);

  switch (auton) {
    case 1: { /* TOP RED AUTONOMOUS */
              controller.print(2,0, "Run: [TOP RED]");
              break;
            }
    case 2: { /* BOTTOM RED AUTONOMOUS */
              controller.print(2,0, "Run: [BOT RED]");
              Lift.moveDistance(240);
              Lift.moveDistance(-240);
              Intake.forward(1);
              Drive.moveDistance(4_ft);
              Intake.forward(0);
              Drive.moveDistance(-3_ft);
              Drive.turnAngle(124_deg);
              Drive.moveDistance(10_in);
              Slide.moveDistance(105);
              Drive.moveDistance(-1_ft);
              break;
            }
    case 3: { /* TOP BLUE AUTONOMOUS */
              controller.print(2,0, "Run: [TOP BLUE]");
              Lift.moveDistance(240);
              Lift.moveDistance(-240);
              Intake.forward(1);
              Drive.moveDistance(4_ft);
              Intake.forward(0);
              Drive.moveDistance(-3_ft);
              Drive.turnAngle(-124_deg);
              Drive.moveDistance(10_in);
              Slide.moveDistance(105);
              Drive.moveDistance(-1_ft);
              break;
            }
    case 4: { /* BOTTOM BLUE AUTONOMOUS */
              controller.print(2,0, "Run: [BOT BLUE]");
              break;
            }
    case 5: { /* SKILL AUTONOMOUS */
              controller.print(2,0, "Run: [SKILLS]");
              break;
            }
  }
}
