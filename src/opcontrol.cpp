#include "port-config.hpp"
#include "pros.h"

extern "C" {
#include "gui.h"
#include "vision.h"
#include "recorder.h"
}

static unsigned char layout = 0; // 0 - Recorder | 1 - Auton Related | 2 - Macro

static void
applyConfig(void)
{
        controller.clear();
        Drive.setBrakeMode(AbstractMotor::brakeMode::hold);
        Lift.setBrakeMode(AbstractMotor::brakeMode::hold);
        Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
        Tray.setBrakeMode(AbstractMotor::brakeMode::hold);
}

static void
arcadeMapping(void)
{
        static float forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        static float turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        rightMotor.move(forward + turn);
        leftMotor.move(forward - turn);
}

static void
intakeMapping(pros::controller_digital_e_t inward, pros::controller_digital_e_t outward)
{
        Intake.setMaxVelocity(600);
        if (controller.get_digital(inward))
                Intake.forward(1);
        else if (controller.get_digital(outward))
                Intake.forward(-1);
        else
                Intake.stop();
}

static void
liftMapping(pros::controller_digital_e_t up, pros::controller_digital_e_t down)
{
        Lift.setMaxVelocity(30);
        if (controller.get_digital(up))
                Lift.forward(1);
        else if (controller.get_digital(down))
                Lift.forward(-1);
        else
                Lift.stop();
}

static void
trayMapping(pros::controller_digital_e_t forward, pros::controller_digital_e_t backward)
{
        Tray.setMaxVelocity(70);
        if (controller.get_digital(forward))
                Tray.forward(1);
        else if (controller.get_digital(backward))
                Tray.forward(-1);
        else
                Tray.forward(0);
}

static void
stackMacro(void)
{
        Tray.moveDistance(1118.00);
}

static void
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

static void
switchLayout(void)
{
        if (layout < 2)
                layout++;
        else
                layout = 0;
}

static void
printCurrentLayout(void)
{
        if (layout == 0)
                controller.print(2, 0, "%d: RECORDER", layout);
        else if (layout == 1)
                controller.print(2, 0, "%d: MACRO", layout);
        else if (layout == 2)
                controller.print(2, 0, "%d: AUTON RELATED", layout);
}

static void
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

static void
switchSubsystem(void)
{
        resetVals();
        if (currentSubsystem < 4)
                currentSubsystem ++;
        else
                currentSubsystem = 0;
}

static void
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

static void
previewRecorder(void)
{
        for (int i = appendArr - 2; i < (appendArr - 1); ++i) {
                if (leftDiffVals[i][currentSubsystem]
                    * rightDiffVals[i][currentSubsystem] != 0) {
                        controller.print(0, 0, "%0.5Lf", leftDiffVals[i][currentSubsystem]);
                        controller.print(1, 0, "%0.5Lf", rightDiffVals[i][currentSubsystem]);
                }
        }
}

static void
recorderMapping(void)
{
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
            && controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                switchSubsystem();
                printCurrentSubsystem();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
                   && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                getCheckpoint();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
                   && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                resetVals();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
                   && controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                previewRecorder();
        }
}

static void
switchAuton(void)
{
        if (auton < 5)
                auton++;
        else
                auton = 1;
}

static void
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

static void
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

static void
macroMapping(void)
{
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
            controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
                stackMacro();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                 controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
                Lift.stop();
                Tray.forward(1);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
                Lift.stop();
                Tray.forward(-1);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                liftMacro(0);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
                   controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                liftMacro(1);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
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
        applyConfig();
        while (true) {
                arcadeMapping();

                intakeMapping(pros::E_CONTROLLER_DIGITAL_R2,
                              pros::E_CONTROLLER_DIGITAL_R1);

                liftMapping(pros::E_CONTROLLER_DIGITAL_L1,
                            pros::E_CONTROLLER_DIGITAL_L2);

                trayMapping(pros::E_CONTROLLER_DIGITAL_X,
                            pros::E_CONTROLLER_DIGITAL_B);

                layoutSwitcherMapping();
                if (layout == 0)
                        recorderMapping();
                else if (layout == 1)
                        autonRelatedMapping();
                else if (layout == 2)
                        macroMapping();

                pros::delay(1);
        }
}
