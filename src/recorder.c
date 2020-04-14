#include <stdio.h>
#include <math.h>

#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"

#include "recorder.h"

unsigned char currentSubsystem = 0;
unsigned char appendArr = 1;

static char *outputText;

// TODO: Implement a typedef struct instead of this hack I made
static long double rightCheckpoint[100][5];
static long double leftCheckpoint[100][5];

long double rightDiffVals[100][5];
long double leftDiffVals[100][5];

static void genSensorVals(void);
static void setCommand(void);

void
resetVals(void)
{
	appendArr = 1;
	for (int i = 0; i < 100; ++i) {
		for (int y = 0; y < 5; ++y) {
			rightCheckpoint[i][y] = 0;
			leftCheckpoint[i][y] = 0;
			rightDiffVals[i][y] = 0;
			leftDiffVals[i][y] = 0;
		}
	}
}

void
initRecorder(void)
{
	resetVals();
	for (int i = 0; i < 20; ++i) {
		motor_set_encoder_units(i, E_MOTOR_ENCODER_DEGREES);
		motor_tare_position(i);
	}
}

void
getCheckpoint(void)
{
	for (int i = appendArr; i < 100; ++i) {
		switch(currentSubsystem) {
		case 0:
			rightCheckpoint[i][0] = motor_get_position(1);
			leftCheckpoint[i][0] = motor_get_position(10);
			break;
		case 1:
			rightCheckpoint[i][1] = motor_get_position(13);
			leftCheckpoint[i][1] = motor_get_position(20);
			break;
		case 2:
			rightCheckpoint[i][2] = motor_get_position(2);
			leftCheckpoint[i][2] = motor_get_position(9);
			break;
		case 3:
			rightCheckpoint[i][3] = motor_get_position(16);
			leftCheckpoint[i][3] = motor_get_position(15);
			break;
		}
		appendArr++;
	}
}

void
genOutput(void)
{
	genSensorVals();
	setCommand();
	fflush(stderr);
	for (int i = 0; i < appendArr; ++i) {
		if (leftDiffVals[i][currentSubsystem]
		    * rightDiffVals[i][currentSubsystem] != 0) {
			fprintf(stderr, "right%s(%Lf);\t", outputText,
				rightDiffVals[i][currentSubsystem]);
			fprintf(stderr, "left%s(%Lf);\n", outputText,
				leftDiffVals[i][currentSubsystem]);
		}
	}
}

static void
genSensorVals(void)
{
	for (int i = 0; i < 99; ++i) {
		rightDiffVals[i][currentSubsystem] =
			rightCheckpoint[i+1][currentSubsystem]
			- rightCheckpoint[i][currentSubsystem];
		leftDiffVals[i][currentSubsystem] =
			leftCheckpoint[i+1][currentSubsystem]
			- leftCheckpoint[i][currentSubsystem];
	}
}

static void
setCommand(void)
{
	switch (currentSubsystem) {
	case 0: outputText = "Drive.moveDistance";
		break;
	case 1: outputText = "Lift.moveDistance";
		break;
	case 2: outputText = "Intake.moveDistance";
		break;
	case 3: outputText = "Tray.moveDistance";
		break;
	}

}

