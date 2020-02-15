#ifndef _PORT_CONFIG_
#define _PORT_CONFIG_

#include "okapi/api.hpp"
#include "pros/motors.hpp"

using namespace okapi;

static inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
static inline pros::Motor rightMotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
static inline pros::Motor leftMotor(10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
static inline pros::Motor rightLift(12, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
static inline pros::Motor leftLift(19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

static inline auto Drive = ChassisControllerFactory::create (
    1, -10,
    AbstractMotor::gearset::green,
    {4.0_in, 16.0_in}
    );

static inline auto Intake = ChassisControllerFactory::create (
    -2, 9,
    AbstractMotor::gearset::green
    );

static inline auto Lift = ChassisControllerFactory::create (
    -12, 19,
    AbstractMotor::gearset::red
    );

static inline auto Tray = ChassisControllerFactory::create (
    -16, 15,
    AbstractMotor::gearset::red
    );

static inline auto intakeAsync = AsyncControllerFactory::posIntegrated({-2,9});
static inline auto liftAsync = AsyncControllerFactory::posIntegrated({-12,19});
static inline auto slideAsync = AsyncControllerFactory::posIntegrated({-16,15});

#endif /* ifndef _PORT_CONFIG_ */
