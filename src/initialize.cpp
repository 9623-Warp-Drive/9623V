#include "main.h"

// setup port
pros::Controller controller (CONTROLLER_MASTER);
pros::Motor Diff (16, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor Slide (15, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::Motor Right_Motor (1, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor Left_Motor (10, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

void initialize() {
  pros::delay(10);
  gui();
}

void disabled() {}

void competition_initialize() {}
