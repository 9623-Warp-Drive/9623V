#include <cerrno>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "port-config.hpp"
#include "pros.h"

extern "C" {
  #include "gui.h"
  #include "vision.h"
  #include "recorder.h"
}

pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Motor rightMotor (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftMotor (10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightLift (12, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftLift (19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

extern "C" int
getDriveVals(void) {
  return (abs(rightMotor.get_position()) + abs(leftMotor.get_position()) / 2);
}

extern "C" int
getLiftVals(void) {
  return (abs(rightLift.get_position()) + abs(leftLift.get_position())) / 2;
}

void
opcontrol(void) {
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(AbstractMotor::brakeMode::hold);

  while (true) {
    /* Set Drive Binding */
    int8_t power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int8_t turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 2;
    rightMotor.move_voltage(power + turn);
    leftMotor.move_voltage(power - turn);

    /* Set Intake Binding */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      Intake.setMaxVelocity(200);
      Intake.forward(-1);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      Intake.setMaxVelocity(600);
      Intake.forward(1);
    }
    else {
      Intake.stop();
    }

    /* Set Lift Binding */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      Lift.setMaxVelocity(20);
      Lift.forward(1);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      Lift.setMaxVelocity(20);
      Lift.forward(-1);
    }
    else {
      Lift.stop();
    }

    /* Set Slide Binding */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {

      Slide.setMaxVelocity(30);
      Slide.forward(1);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      Slide.setMaxVelocity(30);
      Slide.forward(-1);
    }
    else {
      Slide.forward(0);
    }

    /* Auton Recorder */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      switchSubsystem();
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      getCheckpoint();
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {

      rightMotor.tare_position();
      leftMotor.tare_position();
      rightLift.tare_position();
      leftLift.tare_position();

      Drive.resetSensors();
      Intake.resetSensors();
      Lift.resetSensors();
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
      recorder();
    }
    else {}

    pros::delay(1);
  }
}
