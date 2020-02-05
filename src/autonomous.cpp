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

static void alignToObject(void);

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

  switch (auton) {
    case 1: { /* TOP RED AUTONOMOUS */
              break;
            }
    case 2: { /* BOTTOM RED AUTONOMOUS */
              break;
            }
    case 3: { /* TOP BLUE AUTONOMOUS */
              break;
            }
    case 4: { /* BOTTOM BLUE AUTONOMOUS */
              break;
            }
    case 5: { /* SKILL AUTONOMOUS */
              break;
            }
  }
}
