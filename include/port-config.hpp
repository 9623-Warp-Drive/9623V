#ifndef _PORT_CONFIG_
#define _PORT_CONFIG_

#include "okapi/api.hpp"
#include "pros/motors.hpp"

using namespace okapi;

static pros::Controller controller(pros::E_CONTROLLER_MASTER);
static pros::Motor rightMotor(1, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor leftMotor(10, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor rightLift(13, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor leftLift(20, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

static auto drive = ChassisControllerFactory::create (
         1, -10,
         AbstractMotor::gearset::red,
         {4.0_in, 16.0_in}
         );

static auto intake = ChassisControllerFactory::create (
         -2, 9,
         AbstractMotor::gearset::green
         );

static auto lift = ChassisControllerFactory::create (
         -13, 20,
         AbstractMotor::gearset::red
         );

static auto tray = ChassisControllerFactory::create (
                -16, 15,
                AbstractMotor::gearset::red
                );

static auto intakeAsync = AsyncControllerFactory::posIntegrated({-2,9});
static auto liftAsync = AsyncControllerFactory::posIntegrated({-12,19});
static auto trayAsync = AsyncControllerFactory::posIntegrated({-16,15});

#endif /* ifndef _PORT_CONFIG_ */
