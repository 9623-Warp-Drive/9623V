#include "main.h"

inline void arcadeControl() {
  int power = controller.get_analog(ANALOG_LEFT_Y);
  int turn = controller.get_analog(ANALOG_RIGHT_X) / 4;
  // leftMotor.move_voltage(left);
  // rightMotor.move_voltage(right);
  Drive.arcade(power,
      turn);

  pros::delay(1);
}

inline void liftControl() {
  if (controller.get_digital(DIGITAL_L1)) {
    Slide.setMaxVelocity(0.2);
    Lift.forward(1);
    Slide.forward(1);
  }
  else if (controller.get_digital(DIGITAL_L2)) {
    Slide.setMaxVelocity(0.2);
    Lift.forward(-1);
    Slide.forward(-1);
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
    Slide.forward(1);
  }
  else if (controller.get_digital(DIGITAL_B)) {
    Slide.forward(-1);
  }
  else {
    Slide.forward(0);
  }

  pros::delay(1);
}

void opcontrol() {
  while (true) {
    Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
    Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
    Slide.setBrakeMode(AbstractMotor::brakeMode::hold);
    Drive.setBrakeMode(AbstractMotor::brakeMode::brake);

    Intake.setMaxVelocity(600);
    Slide.setMaxVelocity(10);
    Lift.setMaxVelocity(20);
    Drive.setMaxVelocity(200);

    controller.clear_line(2);


    arcadeControl();
    liftControl();
    intakeControl();
    slideControl();

    pros::delay(1);
  }
}
