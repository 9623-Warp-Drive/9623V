#ifndef PORT_CONFIG
#define PORT_CONFIG
extern pros::Controller controller;
extern pros::Motor Diff;
extern pros::Motor rightMotor;
extern pros::Motor leftMotor;
#endif /* ifndef PORT_CONFIG */

#ifndef MotorPID
#define MotorPID
using namespace okapi;
inline auto Drive = ChassisControllerFactory::create (
    -1, 10,
    AbstractMotor::gearset::green,
    {4.0_in, 16.0_in}
    );

inline auto Intake = ChassisControllerFactory::create (
    -2, 9,
    AbstractMotor::gearset::green
    );

inline auto Lift = ChassisControllerFactory::create (
    -12, 19,
    AbstractMotor::gearset::red
    );

inline auto Slide = ChassisControllerFactory::create (
    -16, 15,
    AbstractMotor::gearset::red
    );
#endif /* ifndef ChassisPID */
