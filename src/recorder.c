#include <stdio.h>
#include <stdlib.h>

#include "pros.h"
#include "recorder.h"

#define FORWARD "Drive.moveDistance"
#define TURN "Drive.turnAngle"
#define LIFT "Lift.moveDistance"
#define INTAKE "Intake.moveDistance"
#define TRAY "Tray.moveDistance"

#define ARR_LEN(l) (sizeof((l)) / sizeof((l)[0]))

int currentSubsystem = 0;
static char *outputText;
static int appendArr = 1;
static double checkpoint[100][5];
static double diffVals[100][5];

void initRecorder(void);
void switchSubsystem(void);
void getCheckpoint(void);
void genOutput(void);
static void genSensorVals(void);

void
initRecorder(void) {
  for (int i = 0; i < 21; ++i) {
    motor_set_encoder_units(i, E_MOTOR_ENCODER_DEGREES);
    motor_tare_position(i);
  }

  for (int i = 0; i < 5; ++i) checkpoint[0][i] = 0;

  fprintf(stderr, "AUTON RECORDER\n");
  fprintf(stderr, "0 - FORWARD\n1 - TURN\n2 - LIFT\n3 - INTAKE\n4 - Tray\n\n");
}

void
switchSubsystem(void) {
  appendArr = 1;
  if (currentSubsystem < 4) {
    currentSubsystem ++;
  }
  else {
    currentSubsystem = 0;
  }
}

void
getCheckpoint(void) {
  appendArr++;
  for (int i = appendArr; i < ARR_LEN(checkpoint); ++i) {
    checkpoint[i][0] = (motor_get_position(1) + motor_get_position(10)) / 2;
    checkpoint[i][1] = (abs(motor_get_position(1)) + abs(motor_get_position(10))) / 2;
    checkpoint[i][2] = (motor_get_position(12) + motor_get_position(19)) / 2;
    checkpoint[i][3] = (motor_get_position(2) + motor_get_position(9)) / 2;
    checkpoint[i][4] = (motor_get_position(16) + motor_get_position(15)) / 2;
  }
}

void
genSensorVals(void) {
  for (int i = 0; i < ARR_LEN(diffVals); ++i) {
    diffVals[i][currentSubsystem] = checkpoint[i++][currentSubsystem] - checkpoint[--i][currentSubsystem];
  }
}

void
genOutput(void) {
  genSensorVals();
  for (int i = appendArr - 2; i < (appendArr - 1); ++i) {
    switch(currentSubsystem) {
      case 0:
        outputText = FORWARD;
        break;
      case 1:
        outputText = TURN;
        break;
      case 2:
        outputText = LIFT;
        break;
      case 3:
        outputText = INTAKE;
        break;
      case 4:
        outputText = TRAY;
        break;
    }

    if (diffVals[i][currentSubsystem] != 0) {
      fprintf(stderr, "%s(%f);\n", outputText, diffVals[i][currentSubsystem]);
      if (usd_is_installed()) {
        FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
        fprintf(SDfile, "%s(%f);\n", outputText, diffVals[i][currentSubsystem]);
        fclose(SDfile);
      }
      else {}
    }
    else {}
  }
}
