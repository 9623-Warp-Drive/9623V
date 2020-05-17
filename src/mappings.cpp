#include "pros/misc.hpp"

#include "macro.hpp"
#include "main.hpp"
#include "mappings.hpp"
#include "port-config.hpp"
#include "recorder.h"
#include "rerun.hpp"
#include "statusline.hpp"
#include "switcher.hpp"

static void arcadeMapping(void);
static void intakeMapping(pros::controller_digital_e_t inward,
			  pros::controller_digital_e_t outward);
static void liftMapping(pros::controller_digital_e_t up,
			pros::controller_digital_e_t down);
static void trayMapping(pros::controller_digital_e_t forward,
			pros::controller_digital_e_t backward);

static void layoutMapping(void);
static void recorderMapping(void);
static void autonMapping(void);
static void macroMapping(void);

void
mappings(void)
{
	arcadeMapping();
	intakeMapping(pros::E_CONTROLLER_DIGITAL_R2,
		      pros::E_CONTROLLER_DIGITAL_R1);
	liftMapping(pros::E_CONTROLLER_DIGITAL_L1,
		    pros::E_CONTROLLER_DIGITAL_L2);
	trayMapping(pros::E_CONTROLLER_DIGITAL_X,
		    pros::E_CONTROLLER_DIGITAL_B);

	layoutMapping();
	if (currentLayout == 0)
		recorderMapping();
	else if (currentLayout == 1)
		autonMapping();
	else if (currentLayout == 2)
		macroMapping();
}

static void
arcadeMapping(void)
{
	drive.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
		     controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
}

static void
intakeMapping(pros::controller_digital_e_t inward, pros::controller_digital_e_t outward)
{
	intake.setMaxVelocity(600);
	if (controller.get_digital(inward))
		intake.forward(1);
	else if (controller.get_digital(outward))
		intake.forward(-1);
	else
		intake.stop();
}

static void
liftMapping(pros::controller_digital_e_t up, pros::controller_digital_e_t down)
{
	lift.setMaxVelocity(30);
	if (controller.get_digital(up))
		lift.forward(1);
	else if (controller.get_digital(down))
		lift.forward(-1);
	else
		lift.stop();
}

static void
trayMapping(pros::controller_digital_e_t forward, pros::controller_digital_e_t backward)
{
	tray.setMaxVelocity(70);
	if (controller.get_digital(forward))
		tray.forward(1);
	else if (controller.get_digital(backward))
		tray.forward(-1);
	else
		tray.forward(0);
}

static void
layoutMapping(void)
{
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		switchMode(currentLayout, 2);
	else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)
		 && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		printCurrentLayout();
	else
		controller.clear_line(2);
}

static void
recorderMapping(void)
{
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
	    && controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		switchMode(currentSubsystem, 3);
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
	} else {
		controller.clear();
	}
}

static void
autonMapping(void)
{
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
	    && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		switchMode(currentAuton, 5);
		printCurrentAuton();
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
		   && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		autonomous();
	} else {
		controller.clear_line(2);
	}

	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
	    && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
		run();
	else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
		 && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
		reverse();
}

static void
macroMapping(void)
{
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
	    && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
		stackMacro();
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
		   && controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		lift.stop();
		tray.forward(1);
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
		   && controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		lift.stop();
		tray.forward(-1);
	}

	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
	    && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		liftMacro(0);
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
		   && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		liftMacro(1);
	}

	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
	    && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
		intake.setMaxVelocity(200);
		intake.forward(-1);
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
		   && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
		intake.setMaxVelocity(200);
		intake.forward(1);
	}
}
