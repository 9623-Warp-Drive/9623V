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
  if (controller.get_digital(DIGITAL_UP)) {
    Slide.move_velocity(10);
  }
  else if (controller.get_digital(DIGITAL_DOWN)) {
    Slide.move_velocity(-10);
  }
  else {
    Slide.move_velocity(0);
  }

  pros::delay(1);
}

inline void autonTester() {
  if (controller.get_digital(DIGITAL_Y)) {
    Drive.turnAngle(90);
  }
  else if (controller.get_digital(DIGITAL_X)) {
    Drive.turnAngle(-90);
  }
  else if (controller.get_digital(DIGITAL_A)) {
    Drive.moveDistance(4.0_ft);
  }
  else if (controller.get_digital(DIGITAL_B)) {
    Drive.moveDistance(-4.0_ft);
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
  Lift.setMaxVelocity(25);
  Drive.setMaxVelocity(200);

  controller.clear_line(2);

  while (true) {
    arcadeControl();
    liftControl();
    intakeControl();
    slideControl();
    AutonTester();

    pros::delay(1);
  }
}
