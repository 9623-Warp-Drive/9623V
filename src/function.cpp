#include "pros.h"
#include "function.hpp"
#include "port-config.hpp"
#include "rerun.hpp"

#include "vision.h"
#include "recorder.h"
#include "gui.h"

static unsigned char layout = 0; // 0 - Recorder | 1 - Auton Related | 2 - Macro

static void deploy(void);
static void forward(int vel, double dist);
static void forwardIntake(int vel, double dist);
static void turn(int vel, double deg);
static void alignStack(void);
static void stack(int vel, double dist);
static void alignToObject(void);

static void arcadeMapping(void);
static void intakeMapping(pros::controller_digital_e_t inward,
			  pros::controller_digital_e_t outward);
static void liftMapping(pros::controller_digital_e_t up,
			pros::controller_digital_e_t down);
static void trayMapping(pros::controller_digital_e_t forward,
			pros::controller_digital_e_t backward);

static void switchLayout(void);
static void printCurrentLayout(void);
static void layoutSwitcherMapping(void);

static void switchSubsystem(void);
static void printCurrentSubsystem(void);
static void previewRecorder(void);
static void recorderMapping(void);

static void switchAuton(void);
static void printCurrentAuton(void);
static void autonRelatedMapping(void);

static void stackMacro(void);
static void liftMacro(char pos);
static void macroMapping(void);

static void updateStatus(void);

void
applyConfig(void)
{
	controller.clear();
	drive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	tray.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}

void
topRed(void)
{
	deploy();
	forwardIntake(600, 500);
	forwardIntake(600, 1224.50);
	turn(600, -86);
	forwardIntake(600, 183.80);
	turn(600, -408);
	stack(35, 1144.3);
	forward(600, -200);
}

void
botRed(void)
{
	drive.setMaxVelocity(60);
	deploy();
	forwardIntake(20, 1168.20);
	forwardIntake(600, -601.50);
	turn(600, 437);
	alignStack();
	stack(70, 422);
	intake.moveDistance(-350.8);
	forward(600, -200);
}

void
topBlue(void)
{
	deploy();
	forwardIntake(600, 500);
	turn(600, -400);
	intake.moveDistance(-400);
	turn(600, 400);
	forwardIntake(600, 640.10);
	turn(600, 79);
	forwardIntake(600, 201.30);
	forward(600, -201.30);
	turn(600, 408);
	stack(35, 1144.3);
	forward(600, -200);
}

void
botBlue(void)
{
	drive.setMaxVelocity(100);
	deploy();
	forwardIntake(100, 1168.20);
	forwardIntake(600, -601.50);
	turn(600, -437);
	alignStack();
	stack(70, 422);
	forward(600, -200);
}

void
nullAuton(void)
{
	deploy();
	alignToObject();
}

static void
deploy(void)
{
	trayAsync.tarePosition();
	trayAsync.setTarget(573.60);
	lift.moveDistance(90.3);
	trayAsync.waitUntilSettled();
	lift.waitUntilSettled();

	trayAsync.setTarget(0);
	lift.moveDistance(-90.3);
	trayAsync.waitUntilSettled();
}

static void
forward(int vel, double dist)
{
	drive.setMaxVelocity(vel);
	drive.moveDistance(dist);
}

static void
forwardIntake(int vel, double dist)
{
	intake.forward(1);
	drive.setMaxVelocity(vel);
	drive.moveDistance(dist);
	intake.forward(0);
}

static void
turn(int vel, double deg)
{
	drive.setMaxVelocity(vel);
	drive.turnAngle(deg);
}

static void
alignStack(void)
{
	intakeAsync.tarePosition();
	intakeAsync.setTarget(-177.40);
	intakeAsync.waitUntilSettled();
}

static void
stack(int vel, double dist)
{
	trayAsync.setMaxVelocity(vel);
	drive.setMaxVelocity(600);

	drive.moveDistanceAsync(dist);
	trayAsync.setTarget(1120.00);
	drive.waitUntilSettled();
	trayAsync.waitUntilSettled();
}

static void
alignToObject(void)
{
	while (errorDist() != 0) {
		if (errorDist() > 0)
			drive.right(1);
		else if (errorDist() < 0)
			drive.left(1);
		else
			drive.stop();
	}
}

void
mappings(void)
{
	updateStatus();

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
	else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)
		 && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
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
	} else {
		controller.clear();
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
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)
	    && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		switchAuton();
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
stackMacro(void)
{
	tray.moveDistance(1118.00);
}

static void
liftMacro(char pos)
{
	if (pos == 0) { // Medium Tower
		tray.moveDistance(384.40);
		lift.moveDistance(238.8);
	} else if (pos == 1) { // Hight Tower
		tray.moveDistance(384.40);
		lift.moveDistance(238.8);
		tray.moveDistance(200);
		lift.moveDistance(193.70);
	}
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

static void
updateStatus(void)
{
	if (!layout) {
		controller.print(0, 0, "ROBOT: %d", pros::battery::get_capacity);
		controller.print(1, 0, "CONTROLLER: %d", controller.get_battery_level());
	}
}

