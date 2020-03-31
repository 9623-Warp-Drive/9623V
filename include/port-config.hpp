#ifndef _PORT_CONFIG_
#define _PORT_CONFIG_

#include "okapi/api.hpp"
#include "pros/motors.hpp"

using namespace okapi;

const static unsigned char rightMotorPort = 1;
const static unsigned char leftMotorPort = 10;

const static unsigned char rightIntakePort = 2;
const static unsigned char leftIntakePort = 9;

const static unsigned char rightLiftPort = 13;
const static unsigned char leftLiftPort = 20;

const static unsigned char rightTrayPort = 16;
const static unsigned char leftTrayPort = 15;

static pros::Controller controller(pros::E_CONTROLLER_MASTER);
static pros::Motor rightMotor(rightMotorPort,
                              pros::E_MOTOR_GEARSET_36, false,
                              pros::E_MOTOR_ENCODER_DEGREES
                              );

static pros::Motor leftMotor(leftMotorPort,
                             pros::E_MOTOR_GEARSET_36, true,
                             pros::E_MOTOR_ENCODER_DEGREES
                             );

static auto
drive = ChassisControllerFactory::create (
        rightMotorPort, -leftMotorPort,
        AbstractMotor::gearset::red,
        {4.0_in, 16.0_in}
);

static auto
intake = ChassisControllerFactory::create (
        -rightIntakePort, leftIntakePort,
        AbstractMotor::gearset::green
);

static auto
lift = ChassisControllerFactory::create (
        -rightLiftPort, leftLiftPort,
        AbstractMotor::gearset::red
);

static auto
tray = ChassisControllerFactory::create (
        -rightTrayPort, leftTrayPort,
        AbstractMotor::gearset::red
);

static auto intakeAsync = AsyncControllerFactory::posIntegrated(
        {-rightIntakePort, leftIntakePort}
);

static auto liftAsync = AsyncControllerFactory::posIntegrated(
        {-rightLiftPort, leftLiftPort}
);

static auto trayAsync = AsyncControllerFactory::posIntegrated(
        {-rightTrayPort, leftTrayPort}
);

#endif /* ifndef _PORT_CONFIG_ */
