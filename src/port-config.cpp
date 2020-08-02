#include "port-config.hpp"

void
apply_config(void)
{
	controller.clear();
	drive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	tray.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}
