#ifndef PORT_CONFIG
#define PORT_CONFIG
extern pros::Controller controller;
extern pros::Vision vision;
extern pros::Motor rightMotor;
extern pros::Motor leftMotor;
#endif /* ifndef PORT_CONFIG */

#ifndef MotorPID
#define MotorPID
using namespace okapi;
static inline auto Drive = ChassisControllerFactory::create (
    -1, 10,
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

static inline auto Slide = ChassisControllerFactory::create (
    -16, 15,
    AbstractMotor::gearset::red
    );
#endif /* ifndef ChassisPID */
