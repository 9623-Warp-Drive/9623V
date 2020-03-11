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
static void deploy(void);

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
deploy(void) {
  trayAsync.setTarget(573.60);
  Lift.moveDistance(90.3);
  trayAsync.waitUntilSettled();
  Lift.waitUntilSettled();
  trayAsync.tarePosition();
  trayAsync.setTarget(-573.60);
  Lift.moveDistance(-90.3);
  trayAsync.waitUntilSettled();
  trayAsync.tarePosition();
}

void
autonomous(void) {
  Drive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Tray.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

  switch (auton) {
    case 1: /* TOP RED AUTONOMOUS */
      deploy();
      break;
    case 2: /* BOTTOM RED AUTONOMOUS */
      deploy();

      Drive.setMaxVelocity(300);
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
    case 3: /* TOP BLUE AUTONOMOUS */
      break;
    case 4: /* BOTTOM BLUE AUTONOMOUS */
      deploy();
      Drive.setMaxVelocity(300);
      Intake.forward(1);

      Drive.moveDistance(1038.3);
      Intake.forward(0);

      Drive.setMaxVelocity(600);
      Drive.moveDistance(-544.3);

      Drive.turnAngle(-437);

      trayAsync.setMaxVelocity(70);
      Drive.moveDistanceAsync(883.2_ft);
      trayAsync.setTarget(1120.00);
      Drive.waitUntilSettled();
      trayAsync.waitUntilSettled();
      break;
    case 5: /* SKILL AUTONOMOUS */
      deploy();
      break;
  }
}
