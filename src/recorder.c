#include <stdio.h>
#include <stdlib.h>

#include "pros.h"
#include "recorder.h"

#define FORWARD "Drive.moveDistance"
#define TURN "Drive.turnAngle"
#define LIFT "Lift.moveDistance"
#define INTAKE "Intake.moveDistance"
#define TRAY "Tray.moveDistance"

int currentSubsystem = 0;
static char *outputText;
static int appendArr = 1;
static double checkpoint[100][5];
static double diffVals[100][5];

void initRecorder(void);
void switchSubsystem(void);
void getCheckpoint(void);
void genOutput(void);
void genSensorVals(void);

void
initRecorder(void) {
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
  for (int i = appendArr; i < 100; ++i) {
    switch(currentSubsystem) {
      case 0:
        checkpoint[i][0] = (motor_get_position(1) + motor_get_position(10)) / 2;
        break;
      case 1:
        checkpoint[i][1] = (abs(motor_get_position(1)) + abs(motor_get_position(10))) / 2;
        break;
      case 2:
        checkpoint[i][2] = (motor_get_position(12) + motor_get_position(19)) / 2;
        break;
      case 3:
        checkpoint[i][3] = (motor_get_position(2) + motor_get_position(9)) / 2;
        break;
      case 4:
        checkpoint[i][4] = (motor_get_position(16) + motor_get_position(15)) / 2;
        break;
    }
  }
  appendArr++;
}

void
genSensorVals(void) {
  for (int i = 0; i < 99; ++i) {
    diffVals[i][currentSubsystem] = checkpoint[++i][currentSubsystem] - checkpoint[--i][currentSubsystem];
  }
}

void
genOutput(void) {
  genSensorVals();
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
  for (int i = appendArr - 2; i < (appendArr - 1); ++i) {
    if (diffVals[i][currentSubsystem] != 0) {
      fprintf(stderr, "%s(%f);\n", outputText, diffVals[i][currentSubsystem]);
      if (usd_is_installed()) {
        FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
        fprintf(SDfile, "%s(%f);\n", outputText, diffVals[i][currentSubsystem]);
        fclose(SDfile);
      }
    }
  }
}
