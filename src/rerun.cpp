#include "port-config.hpp"
#include "rerun.hpp"

extern "C" {
#include "recorder.h"
}

static long double avgDiffVals[100][5];

static void
getAvg(void)
{
	for (int i = 0; i < 100; ++i) {
		for (int y = 0; i < 5; ++y) {
			avgDiffVals[i][y] = (rightDiffVals[i][y] + leftDiffVals[i][y]) / 2;
		}
	}

}

void
run(void)
{
	getAvg();
	switch (currentSubsystem) {
	case 0: drive.moveDistance(avgDiffVals[appendArr-1][0]);
		break;
	case 1: drive.turnAngle(avgDiffVals[appendArr-1][1]);
		break;
	case 2: intake.moveDistance(avgDiffVals[appendArr-1][2]);
		break;
	case 3: tray.moveDistance(avgDiffVals[appendArr-1][3]);
		break;
	}
}

void
reverse(void)
{
	getAvg();
	switch (currentSubsystem) {
	case 0: drive.moveDistance(-avgDiffVals[appendArr-1][0]);
		break;
	case 1: drive.turnAngle(-avgDiffVals[appendArr-1][1]);
		break;
	case 2: intake.moveDistance(-avgDiffVals[appendArr-1][2]);
		break;
	case 3: tray.moveDistance(-avgDiffVals[appendArr-1][3]);
		break;
	}
}
