#include <cerrno>
#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "pros.h"
#include "port-config.hpp"

extern "C" {
  #include "gui.h"
  #include "vision.h"
}

void
alignToObject(void) {
  while (errorDist() != 0) {
    if (errorDist() > 0) {
      Drive.right(1);
    }
    else if (errorDist() < 0) {
      Drive.left(1);
    }
    else {
      Drive.stop();
    }
  }
}

void
autonomous(void) {
  Drive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

  Intake.setMaxVelocity(600);
  Slide.setMaxVelocity(200);

  switch (auton) {
    case 1: { /* TOP RED AUTONOMOUS */
              break;
            }
    case 2: { /* BOTTOM RED AUTONOMOUS */
              Drive.setMaxVelocity(120);
              Lift.setMaxVelocity(600);
              Lift.moveDistance(80);
              Lift.moveDistance(-80);
              Intake.forward(1);
              Drive.moveDistance(2.8_ft);
              Intake.forward(0);
              Drive.setMaxVelocity(600);
              Drive.turnAngle(142.0_deg);
              Drive.moveDistance(23.0_in);
              Slide.moveDistance(325);
              Drive.moveDistance(-2.0_ft);
              break;
            }
    case 3: { /* TOP BLUE AUTONOMOUS */
              break;
            }
    case 4: { /* BOTTOM BLUE AUTONOMOUS */
              Drive.setMaxVelocity(120);
              Lift.setMaxVelocity(600);
              Lift.moveDistance(80);
              Lift.moveDistance(-80);
              Intake.forward(1);
              Drive.moveDistance(3.0_ft);
              Intake.forward(0);
              Drive.setMaxVelocity(600);
              Drive.turnAngle(-142.0_deg);
              Drive.moveDistance(23.0_in);
              Slide.moveDistance(325);
              Drive.moveDistance(-2.0_ft);

              break;
            }
    case 5: { /* SKILL AUTONOMOUS */
              break;
            }
  }
}
