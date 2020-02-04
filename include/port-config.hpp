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
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for distance
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for angle
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for turning
    AbstractMotor::gearset::green,
    {4.0_in, 16.0_in}
    );

static inline auto Intake = ChassisControllerFactory::create (
    -2, 9,
    // IterativePosPIDController::Gains{0.000, 0.0, 0.0000}, // PID values for distance
    // IterativePosPIDController::Gains{0.000, 0.0, 0.0000}, // PID values for angle
    // IterativePosPIDController::Gains{0.000, 0.0, 0.0000}, // PID values for turning
    AbstractMotor::gearset::green
    );

static inline auto Lift = ChassisControllerFactory::create (
    -12, 19,
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for distance
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for angle
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for turning
    AbstractMotor::gearset::red
    );

static inline auto Slide = ChassisControllerFactory::create (
    -16, 15,
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for distance
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for angle
    // IterativePosPIDController::Gains{0.002, 0.0, 0.0002}, // PID values for turning
    AbstractMotor::gearset::red
    );

static inline auto intakeAsync = AsyncControllerFactory::posIntegrated({-2,9});
static inline auto liftAsync = AsyncControllerFactory::posIntegrated({-12,19});
static inline auto slideAsync = AsyncControllerFactory::posIntegrated({-16,15});

// static inline auto intakeAsync = AsyncControllerFactory::posPID (
//     {-2,9},
//     0.002, 0.0, 0.0002
//     );
//
// static inline auto liftAsync = AsyncControllerFactory::posPID (
//     {-12,19},
//     0.002, 0.0, 0.0002
//     );
//
// static inline auto slideAsync = AsyncControllerFactory::posPID (
//     {-16,15},
//     0.002,0.0, 0.0002
//     );
#endif /* ifndef _PORT_CONFIG_ */
