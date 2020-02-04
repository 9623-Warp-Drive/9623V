#include <stdio.h>
#include <stdlib.h>

#include "pros.h"
#include "recorder.h"

#define FORWARD(s) "driveForward"
#define LIFT(s) "lift"
#define TURN(s) "driveTurn"

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
  motor_set_encoder_units(1, E_MOTOR_ENCODER_DEGREES);
  motor_set_encoder_units(2, E_MOTOR_ENCODER_DEGREES);
  motor_set_encoder_units(9, E_MOTOR_ENCODER_DEGREES);
  motor_set_encoder_units(10, E_MOTOR_ENCODER_DEGREES);
  motor_set_encoder_units(12, E_MOTOR_ENCODER_DEGREES);
  motor_set_encoder_units(15, E_MOTOR_ENCODER_DEGREES);
  motor_set_encoder_units(16, E_MOTOR_ENCODER_DEGREES);
  motor_set_encoder_units(19, E_MOTOR_ENCODER_DEGREES);

  motor_tare_position(1);
  motor_tare_position(2);
  motor_tare_position(9);
  motor_tare_position(10);
  motor_tare_position(12);
  motor_tare_position(15);
  motor_tare_position(16);
  motor_tare_position(19);

  checkpoint[0][0] = 0;
  checkpoint[0][1] = 0;
  checkpoint[0][2] = 0;
  checkpoint[0][3] = 0;

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
  for (int i = appendArr; i < sizeof(checkpoint)/sizeof(checkpoint[0]); ++i) {
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
  for (int i = 0; i < sizeof(diffVals)/sizeof(diffVals[0]); ++i) {
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
  genSensorVals();
  for (int i = appendArr - 2; i < (appendArr - 1); ++i) {
    switch(currentSubsystem) {
      case 0:
        if (diffVals[i][0] != 0) {
          fprintf(stderr, "%s(%f);\n", FORWARD(s), diffVals[i][0]);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", FORWARD(s), diffVals[i][0]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
      case 1:
        if (diffVals[i][1] != 0) {
          fprintf(stderr, "%s(%f);\n", TURN(s), diffVals[i][1]);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", TURN(s), diffVals[i][1]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
      case 2:
        if (diffVals[i][2] != 0) {
          fprintf(stderr, "%s(%f);\n", LIFT(s), diffVals[i][2]);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", LIFT(s), diffVals[i][2]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
      case 3:
        if (diffVals[i][3] != 0) {
          fprintf(stderr, "%s(%f);\n", LIFT(s), diffVals[i][3]);
          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", LIFT(s), diffVals[i][3]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;

    }
  }
}
