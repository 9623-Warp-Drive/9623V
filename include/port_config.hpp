#ifndef _PORT_CONFIG_
#define _PORT_CONFIG_

extern pros::Controller controller;
extern pros::Vision vision;
extern pros::Motor rightMotor;
extern pros::Motor leftMotor;

using namespace okapi;
static inline auto Drive = ChassisControllerFactory::create (
    1, -10,
    AbstractMotor::gearset::red,
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

static inline auto Slide = ChassisControllerFactory::create (
    -16, 15,
    AbstractMotor::gearset::red
    );

#endif /* ifndef _PORT_CONFIG_ */
