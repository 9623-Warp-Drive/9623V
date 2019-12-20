#ifndef _BINDING_
#define _BINDING_

class binding {
  public:
    void drive(void);
    void lift(void);
    void intake(void);
    void slide(void);
};

inline void binding :: drive() {
  int8_t power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int8_t turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 4;
  rightMotor.move(power - turn);
  leftMotor.move(power + turn);

  pros::delay(1);
}

inline void binding :: lift() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    Lift.forward(1);
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    Lift.forward(-1);
  }
  else {
    Lift.stop();
  }

  pros::delay(1);
}

inline void binding :: intake() {
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

  pros::delay(1);
}

inline void binding :: slide() {
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

#endif /* ifndef _BINDING_ */
