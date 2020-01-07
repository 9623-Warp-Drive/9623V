#ifndef _PORT_CONFIG_
#define _PORT_CONFIG_

#include "okapi/api.hpp"

extern pros::Controller controller;

using namespace okapi;

static inline auto Drive = ChassisControllerFactory::create (
    1, -10,
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for distance
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for angle
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for turning
    AbstractMotor::gearset::green,
    {4.0_in, 16.0_in}
    );

static inline auto Intake = ChassisControllerFactory::create (
    -2, 9,
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for distance
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for angle
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for turning
    AbstractMotor::gearset::red
    );

static inline auto Lift = ChassisControllerFactory::create (
    -12, 19,
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for distance
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for angle
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for turning
    AbstractMotor::gearset::red
    );

static inline auto Slide = ChassisControllerFactory::create (
    -16, 15,
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for distance
    IterativePosPIDController::Gains{0, 0, 0}, // PID values for angle
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, // PID values for turning
    AbstractMotor::gearset::red
    );

#endif /* ifndef _PORT_CONFIG_ */
