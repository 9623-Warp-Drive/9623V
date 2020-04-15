#include <stdio.h>
#include <math.h>

#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"

#include "recorder.h"

unsigned char currentSubsystem = 0;
unsigned char appendArr = 1;

static void genSensorVals(void);
static void setCommand(void);

subsystem Drive;
subsystem Lift;
subsystem Intake;
subsystem Tray;

void
resetVals(void)
{
	for (int i = 0; i < 100; ++i) {
		switch(currentSubsystem) {
		case 0:
			Drive.rightCheckpoint[i] = 0;
			Drive.leftCheckpoint[i] = 0;
			Drive.rightDiffVals[i] = 0;
			Drive.leftDiffVals[i] = 0;
			break;
		case 1:
			Lift.rightCheckpoint[i] = 0;
			Lift.leftCheckpoint[i] = 0;
			Lift.rightDiffVals[i] = 0;
			Lift.leftDiffVals[i] = 0;
			break;
		case 2:
			Intake.rightCheckpoint[i] = 0;
			Intake.leftCheckpoint[i] = 0;
			Intake.rightDiffVals[i] = 0;
			Intake.leftDiffVals[i] = 0;
			break;
		case 3:
			Tray.rightCheckpoint[i] = 0;
			Tray.leftCheckpoint[i] = 0;
			Tray.rightDiffVals[i] = 0;
			Tray.leftDiffVals[i] = 0;
			break;
		}
	}
	appendArr = 1;
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
			Drive.rightCheckpoint[i] = motor_get_position(1);
			Drive.leftCheckpoint[i] = motor_get_position(10);
			break;
		case 1:
			Lift.rightCheckpoint[i] = motor_get_position(13);
			Lift.leftCheckpoint[i] = motor_get_position(20);
			break;
		case 2:
			Intake.rightCheckpoint[i] = motor_get_position(2);
			Intake.leftCheckpoint[i] = motor_get_position(9);
			break;
		case 3:
			Tray.rightCheckpoint[i] = motor_get_position(16);
			Tray.leftCheckpoint[i] = motor_get_position(15);
			break;
		}
	}
	appendArr++;
}

void
genOutput(void)
{
	genSensorVals();
	setCommand();
	fflush(stderr);
	for (int i = 0; i < appendArr; ++i) {
		switch(currentSubsystem) {
		case 0:
			if (Drive.leftDiffVals[i]
			    * Drive.rightDiffVals[i] != 0) {
				fprintf(stderr, "right%s(%Lf);\t", Drive.outputText,
					Drive.rightDiffVals[i]);
				fprintf(stderr, "left%s(%Lf);\n", Drive.outputText,
					Drive.leftDiffVals[i]);
			}
			break;
		case 1:
			if (Lift.leftDiffVals[i]
			    * Lift.rightDiffVals[i] != 0) {
				fprintf(stderr, "right%s(%Lf);\t", Lift.outputText,
					Lift.rightDiffVals[i]);
				fprintf(stderr, "left%s(%Lf);\n", Lift.outputText,
					Lift.leftDiffVals[i]);
			}
			break;
		case 2:
			if (Intake.leftDiffVals[i]
			    * Intake.rightDiffVals[i] != 0) {
				fprintf(stderr, "right%s(%Lf);\t", Intake.outputText,
					Intake.rightDiffVals[i]);
				fprintf(stderr, "left%s(%Lf);\n", Intake.outputText,
					Intake.leftDiffVals[i]);
			}
			break;
		case 3:
			if (Tray.leftDiffVals[i]
			    * Tray.rightDiffVals[i] != 0) {
				fprintf(stderr, "right%s(%Lf);\t", Tray.outputText,
					Tray.rightDiffVals[i]);
				fprintf(stderr, "left%s(%Lf);\n", Tray.outputText,
					Tray.leftDiffVals[i]);
			}
			break;
		}
	}
}

static void
genSensorVals(void)
{
	for (int i = 0; i < 99; ++i) {
		switch(currentSubsystem) {
		case 0:
			Drive.rightDiffVals[i] =
				Drive.rightCheckpoint[i+1]
				- Drive.rightCheckpoint[i-1];
			Drive.leftDiffVals[i] =
				Drive.leftCheckpoint[i+1]
				- Drive.leftCheckpoint[i-1];
			break;
		case 1:
			Lift.rightDiffVals[i] =
				Lift.rightCheckpoint[i+1]
				- Lift.rightCheckpoint[i-1];
			Lift.leftDiffVals[i] =
				Lift.leftCheckpoint[i+1]
				- Lift.leftCheckpoint[i-1];
			break;
		case 2:
			Intake.rightDiffVals[i] =
				Intake.rightCheckpoint[i+1]
				- Intake.rightCheckpoint[i-1];
			Intake.leftDiffVals[i] =
				Intake.leftCheckpoint[i+1]
				- Intake.leftCheckpoint[i-1];
			break;
		case 3:
			Tray.rightDiffVals[i] =
				Tray.rightCheckpoint[i+1]
				- Tray.rightCheckpoint[i-1];
			Tray.leftDiffVals[i] =
				Tray.leftCheckpoint[i+1]
				- Tray.leftCheckpoint[i-1];
			break;
		}
	}
}

static void
setCommand(void)
{
	switch (currentSubsystem) {
	case 0: Drive.outputText = "Drive.moveDistance";
		break;
	case 1: Lift.outputText = "Lift.moveDistance";
		break;
	case 2: Intake.outputText = "Intake.moveDistance";
		break;
	case 3: Tray.outputText = "Tray.moveDistance";
		break;
	}

}

