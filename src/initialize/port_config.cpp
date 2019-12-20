#include "main.h"
#include "port_config.hpp"

pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Vision vision (13);
pros::Motor rightMotor (1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftMotor (10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
