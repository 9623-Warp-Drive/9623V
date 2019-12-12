#include "main.h"
#include "port_config.hpp"

extern "C" {
  #include "gui.h"
}

uint8_t auton = 0;

void autonomous() {
  Drive.setBrakeMode(AbstractMotor::brakeMode::hold);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(AbstractMotor::brakeMode::hold);

  Drive.setMaxVelocity(85);
  Lift.setMaxVelocity(75);
  Intake.setMaxVelocity(600);
  Slide.setMaxVelocity(12);

  switch (auton) {
    case 1: { /* TOP RED AUTONOMOUS */
              controller.print(2,0, "Run: [TOP RED]");
              break;
            }
    case 2: { /* BOTTOM RED AUTONOMOUS */
              controller.print(2,0, "Run: [BOT RED]");
              Lift.moveDistance(100);
              Lift.moveDistance(-100);
              Intake.forward(1);
              Drive.moveDistance(4_ft);
              Intake.forward(0);
              Drive.moveDistance(-2_ft);
              Drive.turnAngle(160_deg);
              Drive.moveDistance(16_in);
              Slide.moveDistance(105);
              Drive.moveDistance(-2_ft);
              break;
            }
    case 3: { /* TOP BLUE AUTONOMOUS */
              controller.print(2,0, "Run: [TOP BLUE]");
              break;
            }
    case 4: { /* BOTTOM BLUE AUTONOMOUS */
              controller.print(2,0, "Run: [BOT BLUE]");
              Lift.moveDistance(100);
              Lift.moveDistance(-100);
              Intake.forward(1);
              Drive.moveDistance(4_ft);
              Intake.forward(0);
              Drive.moveDistance(-2_ft);
              Drive.turnAngle(-160_deg);
              Drive.moveDistance(16_in);
              Slide.moveDistance(105);
              Drive.moveDistance(-2_ft);
              break;
            }
    case 5: { /* SKILL AUTONOMOUS */
              controller.print(2,0, "Run: [SKILLS]");
              break;
            }
  }
}
