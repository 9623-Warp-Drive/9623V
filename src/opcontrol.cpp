#include "main.h"

inline void arcade() {
  // Arcade control
  Drive.arcade(controller.get_analog(ANALOG_LEFT_Y),
      controller.get_analog(ANALOG_RIGHT_X) * 0.25);

  pros::delay(1);
}

inline void tower() {
  // Tower control
  if (controller.get_digital(DIGITAL_L1)) {
    Tower.forward(1);
  }
  else if (controller.get_digital(DIGITAL_L2)) {
    Tower.forward(-1);
  }
  else {
    Tower.stop();
  }

  pros::delay(1);
}

inline void intake() {
  // Intake Control
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

inline void slide() {
  // Tower control
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

inline void AutonTester() {
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
  // set brake mode
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Tower.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.set_brake_mode(MOTOR_BRAKE_HOLD);
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);
  Diff.set_brake_mode(MOTOR_BRAKE_BRAKE);

  // set speed
  Intake.setMaxVelocity(400);
  Tower.setMaxVelocity(25);
  Drive.setMaxVelocity(200);

  controller.clear_line(2); // clear controller screen

  while (true) {
    arcade();
    tower();
    intake();
    slide();
    AutonTester();
  }
}
