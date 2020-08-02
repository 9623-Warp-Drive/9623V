#include "port-config.hpp"
#include "rerun.hpp"
#include "recorder.h"
#include "switcher.hpp"

static void
get_avg_values(void)
{
	for (int i = 0; i < 100; ++i) {
		switch(current_subsystem) {
		case 0:
			Drive.avgDiffVals[i] = (Drive.rightDiffVals[i]
						   + Drive.leftDiffVals[i]) / 2;
			break;
		case 1:
			Lift.avgDiffVals[i] = (Lift.rightDiffVals[i]
						   + Lift.leftDiffVals[i]) / 2;
			break;
		case 2:
			Intake.avgDiffVals[i] = (Intake.rightDiffVals[i]
						   + Intake.leftDiffVals[i]) / 2;
			break;
		case 3:
			Tray.avgDiffVals[i] = (Tray.rightDiffVals[i]
						   + Tray.leftDiffVals[i]) / 2;
			break;
		}
	}
}

void
run(void)
{
	get_avg_values();
	switch (current_subsystem) {
	case 0: drive.moveDistance(Drive.avgDiffVals[append_array-1]);
		break;
	case 1: lift.moveDistance(Lift.avgDiffVals[append_array-1]);
		break;
	case 2: intake.moveDistance(Intake.avgDiffVals[append_array-1]);
		break;
	case 3: tray.moveDistance(Tray.avgDiffVals[append_array-1]);
		break;
	}
}

void
reverse(void)
{
	get_avg_values();
	switch (current_subsystem) {
	case 0: drive.moveDistance(-Drive.avgDiffVals[append_array-1]);
		break;
	case 1: lift.moveDistance(-Lift.avgDiffVals[append_array-1]);
		break;
	case 2: intake.moveDistance(-Intake.avgDiffVals[append_array-1]);
		break;
	case 3: tray.moveDistance(-Tray.avgDiffVals[append_array-1]);
		break;
	}
}
