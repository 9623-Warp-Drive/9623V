#ifndef _PORT_CONFIG_
#define _PORT_CONFIG_

#include "okapi/api.hpp"
#include "pros/motors.hpp"

using namespace okapi;

enum motor_port {
	RIGHT_DRIVE =  1,
	LEFT_DRIVE  =  10,
	RIGHT_INTAKE=  2,
	LEFT_INTAKE =  9,
	RIGHT_LIFT  =  13,
	LEFT_LIFT   =  20,
	RIGHT_TRAY  =  16,
	LEFT_TRAY   =  15
};

static pros::Controller controller(pros::E_CONTROLLER_MASTER);

static auto
drive = ChassisControllerFactory::create (
	RIGHT_DRIVE, -LEFT_DRIVE,
	AbstractMotor::gearset::red,
	{4.0_in, 16.0_in}
);

static auto
intake = ChassisControllerFactory::create (
	-RIGHT_INTAKE, LEFT_INTAKE,
	AbstractMotor::gearset::green
);

static auto
lift = ChassisControllerFactory::create (
	-RIGHT_LIFT, LEFT_LIFT,
	AbstractMotor::gearset::red
);

static auto
tray = ChassisControllerFactory::create (
	-RIGHT_TRAY, LEFT_TRAY,
	AbstractMotor::gearset::red
);

static auto intakeAsync = AsyncControllerFactory::posIntegrated(
	{-RIGHT_INTAKE, LEFT_INTAKE}
);

static auto liftAsync = AsyncControllerFactory::posIntegrated(
	{-RIGHT_LIFT, LEFT_LIFT}
);

static auto trayAsync = AsyncControllerFactory::posIntegrated(
	{-RIGHT_TRAY, LEFT_TRAY}
);

#endif /* ifndef _PORT_CONFIG_ */
