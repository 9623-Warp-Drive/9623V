#include <stdio.h>
#include <stdlib.h>

#include "pros.h"
#include "recorder.h"

#define DRIVE(s) "drive"
#define LIFT(s) "lift"

int subsystem[3] = { 0, 1, 2 };
int currentSubsystem = 1;
int appendArr = 0;
int i;
double diffVals[50][2];
double checkpoint[50][2];

void genSensorVals(void);
void switchSubsystem(void);
void getCheckpoint(void);
void recorder(void);

void
switchSubsystem(void) {
  switch(currentSubsystem) {
    case 1:
      appendArr = 0;
      currentSubsystem = subsystem[2];
      break;
    case 2:
      appendArr = 0;
      currentSubsystem = subsystem[1];
      break;
  }
}

void
getCheckpoint(void) {
  for (i = appendArr; i < sizeof(checkpoint)/sizeof(checkpoint[0]); ++i) {
    switch(currentSubsystem) {
      case 1:
        checkpoint[i][1] = (motor_get_position(1) + motor_get_position(10)) / 2;
        break;
      case 2:
        checkpoint[i][1] = (motor_get_position(12) + motor_get_position(19)) / 2;
        break;
    }
  }
}

void
genSensorVals(void) {
  for (i = 0; i < sizeof(diffVals)/sizeof(diffVals[0]); ++i) {
    switch(currentSubsystem) {
      case 1: /* DRIVE SUBSYTEM */
        diffVals[i][1] = checkpoint[++i][1] - checkpoint[--i][1];
        break;
      case 2: /* LIFT SUBSYSTEM */
        diffVals[i][2] = checkpoint[++i][2] - checkpoint[--i][2];
        break;
    }
  }
}

void
recorder(void) {
  genSensorVals();
  fprintf(stderr, "\n");
  fprintf(stderr, "AUTON-SNIPPET:\n");
  for (i = 0; i < (appendArr - 1); ++i) {
    switch(currentSubsystem) {
      case 1: /* DRIVE SUBSYSTEM */
        if (diffVals[i][1] > 0) {
          fprintf(stderr, "%s(%f);\n", DRIVE(s), diffVals[i][1]);

          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%f);\n", DRIVE(s), diffVals[i][1]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
      case 2: /* LIFT SUBSYSTEM */
        if (diffVals[i][2] > 0) {
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
    }
  }
}
