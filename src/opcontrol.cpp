#include "main.h"

inline void arcadeControl() {
  // Drive.arcade(controller.get_analog(ANALOG_LEFT_Y),
  //     controller.get_analog(ANALOG_RIGHT_X) * 0.01);
  rightMotor.move_voltage(controller.get_analog(ANALOG_LEFT_Y - controller.get_analog(ANALOG_RIGHT_X);
  leftMotor.move_voltage(controller.get_analog(ANALOG_LEFT_Y + controller.get_analog(ANALOG_RIGHT_X);

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
    // Slide.move_velocity(10);
    Slide.forward(1);
  }
  else if (controller.get_digital(DIGITAL_B)) {
    // Slide.move_velocity(-10);
    Slide.forward(-1);
  }
  else {
    // Slide.move_velocity(0);
    Slide.forward(0);
  }

  pros::delay(1);
}

void opcontrol() {
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  Slide.setBrakeMode(AbstractMotor::brakeMode::hold);
  Drive.setBrakeMode(AbstractMotor::brakeMode::brake);

  Intake.setMaxVelocity(600);
  Slide.setMaxVelocity(10);
  Lift.setMaxVelocity(25);
  Drive.setMaxVelocity(2);

  controller.clear_line(2);

  while (true) {
    arcadeControl();
    liftControl();
    intakeControl();
    slideControl();

    pros::delay(1);
  }
}
