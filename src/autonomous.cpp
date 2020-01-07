#include <cerrno>
#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "function.h"
#include "main.h"
#include "port_config.hpp"
#include "okapi/api.hpp"

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

  Drive.setMaxVelocity(85);
  Lift.setMaxVelocity(75);
  Intake.setMaxVelocity(600);
  Slide.setMaxVelocity(12);

  switch (auton) {
    case 1: { /* TOP RED AUTONOMOUS */
              break;
            }
    case 2: { /* BOTTOM RED AUTONOMOUS */
              Intake.forward(1);
              Drive.moveDistanceAsync(4_ft);
              Lift.moveDistance(100);
              Drive.waitUntilSettled();
              Intake.forward(0);
              Drive.moveDistance(-2_ft);
              Drive.turnAngle(160_deg);
              Drive.moveDistance(16_in);
              Slide.moveDistance(105);
              Drive.moveDistance(-2_ft);
              break;
            }
    case 3: { /* TOP BLUE AUTONOMOUS */
              break;
            }
    case 4: { /* BOTTOM BLUE AUTONOMOUS */
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
              break;
            }
  }
}
