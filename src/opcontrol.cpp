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

static void tiltMacro(void);
static void switchAuton(void);

void
switchAuton(void) {
  if (auton < 6) {
    auton++;
  }
  else {
    auton = 0;
  }
}

void
tiltMacro(void) {
  Tray.setMaxVelocity(70);
  Tray.moveDistance(1118.00);
}

void
opcontrol(void) {
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Tray.setBrakeMode(AbstractMotor::brakeMode::hold);

  while (true) {
    /* Set Drive Binding */
    if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      rightMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
      leftMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    }
    else {
      rightMotor.move((controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 0.5) + (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 0.5));
      leftMotor.move((controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 0.5) - (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 0.5));
    }

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

    /* Set Tray Binding */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      Tray.setMaxVelocity(70);
      Tray.forward(1);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      Tray.setMaxVelocity(70);
      Tray.forward(-1);
    }
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      tiltMacro();
    }
    else {
      Tray.forward(0);
    }

    /* Print Variable On Controller */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      controller.print(2, 0, "Subsystem: %d", currentSubsystem);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      controller.print(2, 0, "Auton: %d", auton);
    }
    else {
      controller.clear_line(2);
    }

    /* Auton Recorder */
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      switchSubsystem();
    }
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      getCheckpoint();
    }
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      genOutput();
    }


    /* Autonomous Testing Related */
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      switchAuton();
    }
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      autonomous();
    }

    pros::delay(1);
  }
}
