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

static void deploy(void);
static void forward(int vel, double dist);
static void forwardIntake(int vel, double dist);
static void turn(int vel, double deg);
static void turnIntake(int vel, double deg);
static void alignStack(void);
static void stack(int vel, double dist);
static void alignToObject(void);

void
deploy(void) {
  trayAsync.tarePosition();
  trayAsync.setTarget(573.60);
  Lift.moveDistance(90.3);
  trayAsync.waitUntilSettled();
  Lift.waitUntilSettled();

  trayAsync.setTarget(0);
  Lift.moveDistance(-90.3);
  trayAsync.waitUntilSettled();
}

void
forward(int vel, double dist) {
  Drive.setMaxVelocity(vel);
  Drive.moveDistance(dist);
}

void
forwardIntake(int vel, double dist) {
  Intake.forward(1);
  Drive.setMaxVelocity(vel);
  Drive.moveDistance(dist);
  Intake.forward(0);
}

void
turn(int vel, double deg) {
  Drive.setMaxVelocity(vel);
  Drive.turnAngle(deg);
}

void
turnIntake(int vel, double deg) {
  Intake.forward(1);
  Drive.setMaxVelocity(vel);
  Drive.turnAngle(deg);
  Intake.forward(0);
}

void
alignStack(void) {
  intakeAsync.setTarget(-197.40);
  intakeAsync.waitUntilSettled();
}

void
stack(int vel, double dist) {
  trayAsync.setMaxVelocity(vel);
  Drive.setMaxVelocity(600);

  Drive.moveDistanceAsync(dist);
  trayAsync.setTarget(1120.00);
  Drive.waitUntilSettled();
  trayAsync.waitUntilSettled();
}

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
      deploy();
      forwardIntake(600, 1224.50);
      turn(600, -86);
      forwardIntake(600, 183.80);
      turn(600, -424);
      alignStack();
      stack(35, 1144.3);
      forward(600, -200);
      auton = 0;
      break;
    case 2: /* BOTTOM RED AUTONOMOUS */
      deploy();
      forwardIntake(200, 1168.20);
      forwardIntake(600, -601.50);
      turn(600, 437);
      alignStack();
      stack(70, 422);
      forward(600, -200);
      auton = 0;
      break;
    case 3: /* TOP BLUE AUTONOMOUS */
      deploy();
      forwardIntake(600, 1140.10);
      turn(600, 79);
      forwardIntake(600, 201.30);
      forward(600, -201.30);
      turn(600, 370);
      alignStack();
      stack(35, 1144.3);
      forward(600, -200);
      auton = 0;
      break;
    case 4: /* BOTTOM BLUE AUTONOMOUS */
      deploy();
      forwardIntake(300, 1168.20);
      forwardIntake(600, -601.50);
      turn(600, -437);
      alignStack();
      stack(70, 422);
      forward(600, -200);
      auton = 0;
      break;
    case 5: /* SKILL AUTONOMOUS */
      deploy();
      auton = 0;
      break;
    default:
      deploy();
  }
}
