#ifndef PORT_CONFIG
#define PORT_CONFIG
extern pros::Controller controller;
extern pros::Motor Diff;
extern pros::Motor Slide;
extern pros::Motor Right_Motor;
extern pros::Motor Left_Motor;
#endif /* ifndef PORT_CONFIG */

#ifndef MotorPID
#define MotorPID
using namespace okapi;
inline auto Drive = ChassisControllerFactory::create (
    -1, 10,
    // IterativePosPIDController::Gains{0,0,0}, // pid values for distance
    // IterativePosPIDController::Gains{0,0,0}, // pid values for angle
    // IterativePosPIDController::Gains{0,0,0}, // pid values for turning
    AbstractMotor::gearset::green,
    {4.0_in, 16.0_in}
    );

inline auto Intake = ChassisControllerFactory::create (
    -2, 9,
    // IterativePosPIDController::Gains{0,0,0}, // pid values for distance
    // IterativePosPIDController::Gains{0,0,0}, // pid values for angle
    AbstractMotor::gearset::green
    );

inline auto Lift = ChassisControllerFactory::create (
    -12, 19,
    // IterativePosPIDController::Gains{0,0,0}, // pid values for distance
    // IterativePosPIDController::Gains{0,0,0}, // pid values for angle
    AbstractMotor::gearset::green
    );
#endif /* ifndef ChassisPID */
