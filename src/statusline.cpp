#include "port-config.hpp"
#include "recorder.h"
#include "switcher.hpp"

static void preview(long double left, long double right);

static void
preview(long double left, long double right)
{
	if (left * right != 0) {
		controller.print(0, 0, "%0.5Lf", left);
		controller.print(1, 0, "%0.5Lf", right);
	}
}

void
preview_recorded_values(void)
{
	for (int i = append_array - 2; i < (append_array - 1); ++i) {
		switch(current_subsystem) {
		case 0:
			preview(Drive.leftDiffVals[i], Drive.rightDiffVals[i]);
			break;
		case 1:
			preview(Lift.leftDiffVals[i], Lift.rightDiffVals[i]);
			break;
		case 2:
			preview(Intake.leftDiffVals[i], Intake.rightDiffVals[i]);
			break;
		case 3:
			preview(Tray.leftDiffVals[i], Tray.rightDiffVals[i]);
			break;
		}
	}
}

void
print_current_subsystem(void)
{
	switch (current_subsystem) {
	case 0:
		controller.print(2, 0, "%d: DRIVE", current_subsystem);
		break;
	case 1:
		controller.print(2, 0, "%d: LIFT", current_subsystem);
		break;
	case 2:
		controller.print(2, 0, "%d: INTAKE", current_subsystem);
		break;
	case 3:
		controller.print(2, 0, "%d: TRAY", current_subsystem);
		break;
	}
}
void
print_current_layout(void)
{
	if (current_layout == 0)
		controller.print(2, 0, "%d: RECORDER", current_layout);
	else if (current_layout == 1)
		controller.print(2, 0, "%d: MACRO", current_layout);
	else if (current_layout == 2)
		controller.print(2, 0, "%d: AUTON RELATED", current_layout);
}
void
print_current_auton(void)
{
	switch (current_auton) {
	case 1:
		controller.print(2, 0, "%d: TOP RED", current_auton);
		break;
	case 2:
		controller.print(2, 0, "%d: BOT RED", current_auton);
		break;
	case 3:
		controller.print(2, 0, "%d: TOP BLUE", current_auton);
		break;
	case 4:
		controller.print(2, 0, "%d: BOT BLUE", current_auton);
		break;
	case 5:
		controller.print(2, 0, "%d: SKILL", current_auton);
		break;
	}
}

void
update_status(void)
{
	if (!current_layout) {
		controller.print(0, 0, "ROBOT: %d", pros::battery::get_capacity);
		controller.print(1, 0, "CONTROLLER: %d", controller.get_battery_level());
	}
}
