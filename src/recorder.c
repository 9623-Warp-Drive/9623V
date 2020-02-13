#include <stdio.h>
#include <stdlib.h>

#include "pros.h"
#include "recorder.h"

#define FORWARD "Drive.moveDistance"
#define TURN "Drive.turnAngle"
#define LIFT "Lift.moveDistance"
#define INTAKE "Intake.moveDistance"

#define arrLen(l) (sizeof((l)) / sizeof((l)[0]))

int subsystem[4] = { 0, 1, 2, 3 };
int currentSubsystem = 0;
int appendArr = 1;
double diffVals[100][4];
double checkpoint[100][4];

void genSensorVals(void);
void switchSubsystem(void);
void getCheckpoint(void);
void recorder(void);

void
initRecorder(void) {
  for (int i = 0; i <= 20; ++i) {
    motor_set_encoder_units(i, E_MOTOR_ENCODER_DEGREES);
    motor_tare_position(i);
  }

  for (int i = 0; i <= 3; ++i) {
    checkpoint[0][i] = 0;
  }

  fprintf(stderr, "AUTON RECORDER\n");
  fprintf(stderr, "0 - FORWARD\n1 - TURN\n2 - LIFT\n3 - INTAKE\n\n");
}

void
switchSubsystem(void) {
  appendArr = 1;
  switch(currentSubsystem) {
    case 0:
      currentSubsystem = subsystem[1];
      break;
    case 1:
      currentSubsystem = subsystem[2];
      break;
    case 2:
      currentSubsystem = subsystem[3];
      break;
    case 3:
      currentSubsystem = subsystem[0];
      break;
  }
}

void
getCheckpoint(void) {
  for (int i = appendArr; i < arrLen(checkpoint); ++i) {
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

    }
  }
}

void
genSensorVals(void) {
  for (int i = 0; i < arrLen(diffVals); ++i) {
    switch(currentSubsystem) {
      case 0:
        diffVals[i][0] = checkpoint[++i][0] - checkpoint[--i][0];
        break;
      case 1:
        diffVals[i][1] = checkpoint[++i][1] - checkpoint[--i][1];
        break;
      case 2:
        diffVals[i][2] = checkpoint[++i][2] - checkpoint[--i][2];
        break;
      case 3:
        diffVals[i][3] = checkpoint[++i][3] - checkpoint[--i][3];
        break;
    }
  }
}

void
recorder(void) {
#if currentSubsystem == 1
  #define outStr "Drive.turnAngle"
#endif

  genSensorVals();
  for (int i = appendArr - 2; i < (appendArr - 1); ++i) {
    switch(currentSubsystem) {
      case 0:
        if (diffVals[i][0] != 0) {
          fprintf(stderr, "%s(%f);\n", FORWARD, diffVals[i][0]);
          controller_clear(E_CONTROLLER_MASTER);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", FORWARD, diffVals[i][0]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
      case 1:
        if (diffVals[i][1] != 0) {
          fprintf(stderr, "%s(%f);\n", TURN, diffVals[i][1]);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", TURN, diffVals[i][1]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
      case 2:
        if (diffVals[i][2] != 0) {
          fprintf(stderr, "%s(%f);\n", LIFT, diffVals[i][2]);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", LIFT, diffVals[i][2]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
      case 3:
        if (diffVals[i][3] != 0) {
          fprintf(stderr, "%s(%f);\n", INTAKE, diffVals[i][3]);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", INTAKE, diffVals[i][3]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
    }
  }
}
