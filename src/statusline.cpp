#include "pros/misc.hpp"

#include "port-config.hpp"
#include "recorder.h"
#include "switcher.hpp"

void
previewRecorder(void)
{
	for (int i = appendArr - 2; i < (appendArr - 1); ++i) {
		switch(currentSubsystem) {
		case 0:
			if (Drive.leftDiffVals[i]
			    * Drive.rightDiffVals[i] != 0) {
				controller.print(0, 0, "%0.5Lf",
						 Drive.leftDiffVals[i]);
				controller.print(1, 0, "%0.5Lf",
						 Drive.rightDiffVals[i]);
			}
			break;
		case 1:
			if (Lift.leftDiffVals[i]
			    * Lift.rightDiffVals[i] != 0) {
				controller.print(0, 0, "%0.5Lf",
						 Lift.leftDiffVals[i]);
				controller.print(1, 0, "%0.5Lf",
						 Lift.rightDiffVals[i]);
			}
			break;
		case 2:
			if (Intake.leftDiffVals[i]
			    * Intake.rightDiffVals[i] != 0) {
				controller.print(0, 0, "%0.5Lf",
						 Intake.leftDiffVals[i]);
				controller.print(1, 0, "%0.5Lf",
						 Intake.rightDiffVals[i]);
			}
			break;
		case 3:
			if (Tray.leftDiffVals[i]
			    * Tray.rightDiffVals[i] != 0) {
				controller.print(0, 0, "%0.5Lf",
						 Tray.leftDiffVals[i]);
				controller.print(1, 0, "%0.5Lf",
						 Tray.rightDiffVals[i]);
			}
			break;
		}
	}
}

void
printCurrentSubsystem(void)
{
	switch (currentSubsystem) {
	case 0:
		controller.print(2, 0, "%d: Drive", currentSubsystem);
		break;
	case 1:
		controller.print(2, 0, "%d: LIFT", currentSubsystem);
		break;
	case 2:
		controller.print(2, 0, "%d: INTAKE", currentSubsystem);
		break;
	case 3:
		controller.print(2, 0, "%d: TRAY", currentSubsystem);
		break;
	}
}
void
printCurrentLayout(void)
{
	if (currentLayout == 0)
		controller.print(2, 0, "%d: RECORDER", currentLayout);
	else if (currentLayout == 1)
		controller.print(2, 0, "%d: MACRO", currentLayout);
	else if (currentLayout == 2)
		controller.print(2, 0, "%d: AUTON RELATED", currentLayout);
}
void
printCurrentAuton(void)
{
	switch (currentAuton) {
	case 1:
		controller.print(2, 0, "%d: TOP RED", currentAuton);
		break;
	case 2:
		controller.print(2, 0, "%d: BOT RED", currentAuton);
		break;
	case 3:
		controller.print(2, 0, "%d: TOP BLUE", currentAuton);
		break;
	case 4:
		controller.print(2, 0, "%d: BOT BLUE", currentAuton);
		break;
	case 5:
		controller.print(2, 0, "%d: SKILL", currentAuton);
		break;
	}
}

void
updateStatus(void)
{
	if (!currentLayout) {
		controller.print(0, 0, "ROBOT: %d", pros::battery::get_capacity);
		controller.print(1, 0, "CONTROLLER: %d", controller.get_battery_level());
	}
}
