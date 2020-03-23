#include "port-config.hpp"
#include "pros.h"

extern "C" {
#include "gui.h"
#include "vision.h"
#include "recorder.h"
}

static char layout = 0; // 0 - Recorder | 1 - Auton Related | 2 - Macro

static void applySettings(void);
static void arcadeMapping(void);
static void intakeMapping(pros::controller_digital_e_t inward,
                          pros::controller_digital_e_t outward);
static void liftMapping(pros::controller_digital_e_t up,
                        pros::controller_digital_e_t down);
static void trayMapping(pros::controller_digital_e_t forward,
                        pros::controller_digital_e_t backward);

static void tiltMacro(void);
static void liftMacro(char pos);

static void switchSubsystem(void);
static void switchAuton(void);
static void switchLayout(void);

static void printCurrentLayout(void);
static void printCurrentSubsystem(void);
static void printCurrentAuton(void);
static void previewRecorder(void);

static void layoutSwitcherMapping(void);
static void recorderMapping(void);
static void autonRelatedMapping(void);
static void macroMapping(void);

void
applySettings(void)
{
        Drive.setBrakeMode(AbstractMotor::brakeMode::hold);
        Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
        Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
        Tray.setBrakeMode(AbstractMotor::brakeMode::hold);

        Lift.setMaxVelocity(30);
        Tray.setMaxVelocity(70);
        Intake.setMaxVelocity(600);
}

void
arcadeMapping(void)
{
        static int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        static int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        rightMotor.move(forward + turn);
        leftMotor.move(forward - turn);
}

void
intakeMapping(pros::controller_digital_e_t inward, pros::controller_digital_e_t outward)
{
        if (controller.get_digital(inward))
                Intake.forward(1);
        else if (controller.get_digital(outward))
                Intake.forward(-1);
        else
                Intake.stop();
}

void
liftMapping(pros::controller_digital_e_t up, pros::controller_digital_e_t down)
{

        if (controller.get_digital(up))
                Lift.forward(1);
        else if (controller.get_digital(down))
                Lift.forward(-1);
        else
                Lift.stop();
}

void
trayMapping(pros::controller_digital_e_t forward, pros::controller_digital_e_t backward)
{

        if (controller.get_digital(forward))
                Tray.forward(1);
        else if (controller.get_digital(backward))
                Tray.forward(-1);
        else
                Tray.forward(0);
}

void
tiltMacro(void)
{
        Tray.moveDistance(1118.00);
}

void
liftLow(void)
{
}

void
liftHigh(void)
{
}

void
liftMacro(char pos)
{
        if (pos == 0) { // Medium Tower
                Tray.moveDistance(384.40);
                Lift.moveDistance(238.8);
        } else if (pos == 1) { // Hight Tower
                Tray.moveDistance(384.40);
                Lift.moveDistance(238.8);
                Tray.moveDistance(200);
                Lift.moveDistance(193.70);
        }
}

void
switchLayout(void) {
        if (layout < 2)
                layout++;
        else
                layout = 0;
}

void
printCurrentLayout(void) {
        if (layout == 0)
                controller.print(2, 0, "%d: RECORDER", layout);
        else if (layout == 1)
                controller.print(2, 0, "%d: MACRO", layout);
        else if (layout == 2)
                controller.print(2, 0, "%d: AUTON RELATED", layout);
}

void
layoutSwitcherMapping(void)
{

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
                switchLayout();
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) &&
                 controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
                printCurrentLayout();
        else
                controller.clear_line(2);

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
printCurrentSubsystem(void)
{
        switch (currentSubsystem) {
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
}

void
previewRecorder(void)
{
        for (int i = appendArr - 2; i < (appendArr - 1); ++i)
                if (diffVals[i][currentSubsystem] != 0)
                        controller.print(2, 0, "%f", diffVals[i][currentSubsystem]);
}

void
recorderMapping(void)
{
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
            controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                switchSubsystem();
                printCurrentSubsystem();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                getCheckpoint();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                resetVals();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                previewRecorder();
        }
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
printCurrentAuton(void)
{

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
}

void
autonRelatedMapping(void)
{

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
            controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                switchAuton();
                printCurrentAuton();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                autonomous();
        }
}

void
macroMapping(void)
{

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
            controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
                tiltMacro();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                liftMacro(0);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                liftMacro(1);
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
}

void
opcontrol(void)
{
        applySettings();
        while (1) {
                arcadeMapping();
                intakeMapping(pros::E_CONTROLLER_DIGITAL_R2,
                              pros::E_CONTROLLER_DIGITAL_R1);
                liftMapping(pros::E_CONTROLLER_DIGITAL_L1,
                            pros::E_CONTROLLER_DIGITAL_L2);
                trayMapping(pros::E_CONTROLLER_DIGITAL_X,
                            pros::E_CONTROLLER_DIGITAL_B);
                layoutSwitcherMapping();
                switch (layout) {
                case 0: // AUTONOMOUS RECORDER
                        recorderMapping();
                        break;
                case 1: // AUTONOMOUS RELATED
                        autonRelatedMapping();
                        break;
                case 2: // MACRO
                        macroMapping();
                        break;
                }
                pros::delay(1);
        }
}
