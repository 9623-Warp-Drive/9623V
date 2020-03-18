#include <iostream>

#include "port-config.hpp"
#include "pros.h"

extern "C" {
#include "gui.h"
#include "vision.h"
#include "recorder.h"
}

static int layout = 0; // 0 - Recorder | 1 - Auton Related | 2 - Macro
static void tiltMacro(void);
static void liftLow(void);
static void liftHigh(void);
static void switchSubsystem(void);
static void switchAuton(void);

void
tiltMacro(void)
{
        Tray.moveDistance(1118.00);
}

void
liftLow(void)
{
        Tray.moveDistance(384.40);
        Lift.moveDistance(238.8);
}

void
liftHigh(void)
{
        Tray.moveDistance(384.40);
        Lift.moveDistance(238.8);
        Tray.moveDistance(200);
        Lift.moveDistance(193.70);
}

void
switchSubsystem(void)
{
        resetVals();
        if (currentSubsystem < 4)
                currentSubsystem ++;
        else
                currentSubsystem = 0;
}

void
switchAuton(void)
{
        if (auton < 5)
                auton++;
        else
                auton = 1;
}

void
switchLayout(void)
{
        if (layout < 2)
                layout++;
        else
                layout = 0;
}

void
opcontrol(void)
{
        Drive.setBrakeMode(AbstractMotor::brakeMode::hold);
        Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
        Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
        Tray.setBrakeMode(AbstractMotor::brakeMode::hold);

        Lift.setMaxVelocity(30);
        Tray.setMaxVelocity(70);
        Intake.setMaxVelocity(600);

        while (1) {
                /* Set Drive Binding */
                static int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
                static int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
                rightMotor.move(forward + turn);
                leftMotor.move(forward - controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

                /* Set Intake Binding */
                if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
                        Intake.forward(-1);
                else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
                        Intake.forward(1);
                else
                        Intake.stop();

                /* Set Lift Binding */
                if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
                        Lift.forward(1);
                else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
                        Lift.forward(-1);
                else
                        Lift.stop();

                /* Set Tray Binding */
                if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
                        Tray.forward(1);
                else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
                        Tray.forward(-1);
                else
                        Tray.forward(0);

                if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                        switchLayout();
                } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) &&
                           controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                        if (layout == 0)
                                controller.print(2, 0, "%d: RECORDER", layout);
                        else if (layout == 1)
                                controller.print(2, 0, "%d: MACRO", layout);
                        else if (layout == 2)
                                controller.print(2, 0, "%d: AUTON RELATED", layout);
                } else
                        controller.clear_line(2);

                switch (layout) {

                case 0: // AUTONOMOUS RECORDER
                        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                            controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                                switchSubsystem();
                                switch (currentSubsystem) { // Display Current Subsystem
                                case 0:
                                        controller.print(2, 0, "%d: FORWARD", currentSubsystem);
                                        break;
                                case 1:
                                        controller.print(2, 0, "%d: TURN", currentSubsystem);
                                        break;
                                case 2:
                                        controller.print(2, 0, "%d: LIFT", currentSubsystem);
                                        break;
                                case 3:
                                        controller.print(2, 0, "%d: INTAKE", currentSubsystem);
                                        break;
                                case 4:
                                        controller.print(2, 0, "%d: TRAY", currentSubsystem);
                                        break;
                                }
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                                getCheckpoint();
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                                resetVals();
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                                for (int i = appendArr - 2; i < (appendArr - 1); ++i)
                                        if (diffVals[i][currentSubsystem] != 0)
                                                controller.print(2, 0, "%f", diffVals[i][currentSubsystem]);
                        }
                        break;

                case 1: // AUTONOMOUS RELATED
                        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                            controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                                switchAuton();
                                switch (auton) { // Display Current Auton
                                case 1:
                                        controller.print(2, 0, "%d: TOP RED", auton);
                                        break;
                                case 2:
                                        controller.print(2, 0, "%d: BOT RED", auton);
                                        break;
                                case 3:
                                        controller.print(2, 0, "%d: TOP BLUE", auton);
                                        break;
                                case 4:
                                        controller.print(2, 0, "%d: BOT BLUE", auton);
                                        break;
                                case 5:
                                        controller.print(2, 0, "%d: SKILL", auton);
                                        break;
                                }
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                                autonomous();
                        }
                        break;

                case 2: // MACRO
                        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                            controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
                                tiltMacro();
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                                liftLow();
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                                liftHigh();
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
                                Lift.stop();
                                Tray.forward(1);
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
                                Lift.stop();
                                Tray.forward(-1);
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
                                Intake.setMaxVelocity(200);
                                Intake.forward(-1);
                        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
                                Intake.setMaxVelocity(200);
                                Intake.forward(1);
                        }
                        break;
                }
                pros::delay(1);
        }
}
