#include <stdio.h>
#include <stdlib.h>

#include "pros.h"
#include "recorder.h"

int currentSubsystem = 0;
int appendArr = 1;
static char *outputText;
double diffVals[100][5];
static double checkpoint[100][5];

void initRecorder(void);
void resetVals(void);
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
resetVals(void) {
  for (int i = 0; i < 100; ++i) {
    for (int y = 0; y < 5; ++y) {
      diffVals[i][y] = 0;
      checkpoint[i][y] = 0;
    }
  }
}

void
switchSubsystem(void) {
  appendArr = 1;
  resetVals();
  if (currentSubsystem < 4)
    currentSubsystem ++;
  else
    currentSubsystem = 0;
}

void
getCheckpoint(void) {
  for (int i = appendArr; i < 100; ++i) switch(currentSubsystem) {
    case 0: checkpoint[i][0] = (motor_get_position(1) + motor_get_position(10)) / 2;
    case 1: checkpoint[i][1] = (abs(motor_get_position(1)) + abs(motor_get_position(10))) / 2;
    case 2: checkpoint[i][2] = (motor_get_position(12) + motor_get_position(19)) / 2;
    case 3: checkpoint[i][3] = (motor_get_position(2) + motor_get_position(9)) / 2;
    case 4: checkpoint[i][4] = (motor_get_position(16) + motor_get_position(15)) / 2;
  }
  appendArr++;
}

void
genSensorVals(void) {
  for (int i = 0; i < 99; ++i) diffVals[i][currentSubsystem] = checkpoint[++i][currentSubsystem] - checkpoint[--i][currentSubsystem];
}

void
genOutput(void) {
  genSensorVals();
  switch(currentSubsystem) {
    case 0: outputText = "Drive.moveDistance";
            break;
    case 1: outputText = "Drive.turnAngle";
            break;
    case 2: outputText = "Lift.moveDistance";
            break;
    case 3: outputText = "Intake.moveDistance";
            break;
    case 4: outputText = "Tray.moveDistance";
            break;
  }
  FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
  for (int i = appendArr - 2; i < (appendArr - 1); ++i) {
    if (diffVals[i][currentSubsystem] != 0) {
      fprintf(stderr, "%s(%f);\n", outputText, diffVals[i][currentSubsystem]);
      if (usd_is_installed())
        fprintf(SDfile, "%s(%f);\n", outputText, diffVals[i][currentSubsystem]);
    }
  }
  fclose(SDfile);
}
