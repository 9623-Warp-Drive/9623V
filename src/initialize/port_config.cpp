#include "main.h"

uint8_t auton;
pros::Controller controller (CONTROLLER_MASTER);
pros::Motor Diff (16, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor Slide (15, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::Motor Right_Motor (1, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor Left_Motor (10, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
