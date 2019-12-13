#ifndef _BINDING_
#define _BINDING_
using namespace pros;
class binding {
  public:
    void drive(void);
    void lift(void);
    void intake(void);
    void slide(void);
};
inline void binding :: drive() {
  int power = controller.get_analog(ANALOG_LEFT_Y);
  int turn = controller.get_analog(ANALOG_RIGHT_X) / 4;
  Drive.arcade(power,
      turn);

  delay(1);
}

inline void binding :: lift() {
  if (controller.get_digital(DIGITAL_L1)) {
    Lift.forward(1);
  }
  else if (controller.get_digital(DIGITAL_L2)) {
    Lift.forward(-1);
  }
  else {
    Lift.stop();
  }

  delay(1);
}

inline void binding :: intake() {
  if (controller.get_digital(DIGITAL_R1)) {
    Intake.setMaxVelocity(600);
    Intake.forward(-1);
  }
  else if (controller.get_digital(DIGITAL_R2)) {
    Intake.setMaxVelocity(100);
    Intake.forward(1);
  }
  else {
    Intake.stop();
  }

  delay(1);
}

inline void binding :: slide() {
  if (controller.get_digital(DIGITAL_X)) {
    Slide.forward(1);
  }
  else if (controller.get_digital(DIGITAL_B)) {
    Slide.forward(-1);
  }
  else {
    Slide.forward(0);
  }

  delay(1);
}
#endif /* ifndef _BINDING_ */
