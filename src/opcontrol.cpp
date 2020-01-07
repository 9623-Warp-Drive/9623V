#include <cerrno>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "main.h"
#include "port_config.hpp"
#include "function.h"

extern "C" {
  #include "gui.h"
  #include "vision.h"
}

pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Motor rightMotor (1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftMotor (10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

void
opcontrol(void) {
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(AbstractMotor::brakeMode::hold);

  Lift.setMaxVelocity(20);
  Intake.setMaxVelocity(600);
  Slide.setMaxVelocity(20);

  controller.clear_line(2);

  while (true) {

    controller.print(2,0, "cube count:%d", objectNum());

    /* Set Drive Binding */
    int8_t power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int8_t turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 4;
    rightMotor.move(power - turn);
    leftMotor.move(power + turn);

    /* Set Intake Binding */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      Intake.setMaxVelocity(50);
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
      Lift.forward(1);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      Lift.forward(-1);
    }
    else {
      Lift.stop();
    }

    /* Set Slide Binding */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      Slide.forward(1);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      Slide.forward(-1);
    }
    else {
      Slide.forward(0);
    }

    pros::delay(1);
  }
}
