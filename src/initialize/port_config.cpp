#include "main.h"

pros::Controller controller (CONTROLLER_MASTER);
pros::Motor rightMotor (1, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor leftMotor (10, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
