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
    if (errorDist() > 0)
      Drive.right(1);
    else if (errorDist() < 0)
      Drive.left(1);
    else
      Drive.stop();
  }
}

void
autonomous(void) {
  Drive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Tray.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

  switch (auton) {
    case 1: /* TOP RED AUTONOMOUS */
      Drive.setMaxVelocity(400);
      Intake.forward(1);
      Drive.moveDistance(6.6_ft);
      Intake.forward(0);
      Drive.setMaxVelocity(600);
      Drive.moveDistance(-3.6_ft);
      Drive.turnAngle(196_deg);

      trayAsync.setMaxVelocity(70);
      Drive.moveDistanceAsync(2.0_ft);
      trayAsync.setTarget(1120.00);
      Drive.waitUntilSettled();
      trayAsync.waitUntilSettled();

      Intake.moveDistance(-100);
      Drive.moveDistance(-1.9_ft);
      break;
    case 2: /* BOTTOM RED AUTONOMOUS */
      break;
    case 3: /* TOP BLUE AUTONOMOUS */
      break;
    case 4: /* BOTTOM BLUE AUTONOMOUS */
      break;
    case 5: /* SKILL AUTONOMOUS */
      break;
  }
}
