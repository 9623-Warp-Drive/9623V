#include "main.h"

inline void arcadeControl() {
  Drive.arcade(controller.get_analog(ANALOG_LEFT_Y),
      controller.get_analog(ANALOG_RIGHT_X) * 0.25);

  pros::delay(1);
}

inline void liftControl() {
  if (controller.get_digital(DIGITAL_L1)) {
    Lift.forward(1);
  }
  else if (controller.get_digital(DIGITAL_L2)) {
    Lift.forward(-1);
  }
  else {
    Lift.stop();
  }

  pros::delay(1);
}

inline void intakeControl() {
  if (controller.get_digital(DIGITAL_R1)) {
    Intake.forward(-1);
  }
  else if (controller.get_digital(DIGITAL_R2)) {
    Intake.forward(1);
  }
  else {
    Intake.stop();
  }

  pros::delay(1);
}

inline void slideControl() {
  if (controller.get_digital(DIGITAL_X)) {
    Slide.move_velocity(10);
  }
  else if (controller.get_digital(DIGITAL_B)) {
    Slide.move_velocity(-10);
  }
  else {
    Slide.move_velocity(0);
  }

  pros::delay(1);
}

inline void autonTester() {
  if (controller.get_digital(DIGITAL_Y)) {
    auton = 1;
    autonomous();
  }
  else if (controller.get_digital(DIGITAL_X)) {
    auton = 2;
    autonomous();

  }
  else if (controller.get_digital(DIGITAL_A)) {
    auton = 3;
    autonomous();
  }
  else if (controller.get_digital(DIGITAL_B)) {
    auton = 4;
    autonomous();
  }
  else {}
}

void opcontrol() {
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.set_brake_mode(MOTOR_BRAKE_HOLD);
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Diff.set_brake_mode(MOTOR_BRAKE_BRAKE);

  Intake.setMaxVelocity(400);
  Lift.setMaxVelocity(75);
  Drive.setMaxVelocity(100);

  controller.clear_line(2);

  while (true) {
    arcadeControl();
    liftControl();
    intakeControl();
    slideControl();

    pros::delay(1);
  }
}
