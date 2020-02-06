#include <cerrno>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "port-config.hpp"
#include "pros.h"

int timeCount = 0;

extern "C" {
  #include "gui.h"
  #include "vision.h"
  #include "recorder.h"
}

void
opcontrol(void) {
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(AbstractMotor::brakeMode::hold);

  while (true) {

    /* Set Subsystem Number On Controller */
    if (!(timeCount % 25)) {
      controller.print(0, 0, "Subsystem: %d", currentSubsystem);
    }
    timeCount++;

    /* Set Drive Binding */
    rightMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 0.8));
    leftMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 0.8));

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
      Lift.setMaxVelocity(50);
      Lift.forward(1);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      Lift.setMaxVelocity(50);
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
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      switchSubsystem();
    }
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      fprintf(stderr, "%d\n", currentSubsystem);
    }
    else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      getCheckpoint();
      appendArr++;
    }
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      recorder();
    }
    else {}

    /* TESTING AUTON */
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      autonomous();
    }

    pros::delay(1);
  }
}
