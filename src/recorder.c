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
int appendArr = 1;
static int subsystem[5] = { 0, 1, 2, 3, 4 };
static double diffVals[100][5];
static double checkpoint[100][5];

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

  for (int i = 0; i <= 4; ++i) {
    checkpoint[0][i] = 0;
  }

  fprintf(stderr, "AUTON RECORDER\n");
  fprintf(stderr, "0 - FORWARD\n1 - TURN\n2 - LIFT\n3 - INTAKE\n4 - Tray\n\n");
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
      currentSubsystem = subsystem[4];
      break;
    case 4:
      currentSubsystem = subsystem[0];
      break;
  }
}

void
getCheckpoint(void) {
  for (int i = appendArr; i < ARR_LEN(checkpoint); ++i) {
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
}

void
genSensorVals(void) {
  for (int i = 0; i < ARR_LEN(diffVals); ++i) {
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
      case 4:
        diffVals[i][4] = checkpoint[++i][4] - checkpoint[--i][4];
        break;
    }
  }
}

void
recorder(void) {
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
      case 4:
        if (diffVals[i][4] != 0) {
          fprintf(stderr, "%s(%f);\n", TRAY, diffVals[i][4]);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", TRAY, diffVals[i][4]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
    }
  }
}
