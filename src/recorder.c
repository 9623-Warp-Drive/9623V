#include <stdio.h>
#include <stdlib.h>

#include "pros.h"
#include "recorder.h"

#define DRIVE(s) "Drive"
#define LIFT(s) "Lift"

static int checkpoint[100][2];
static int diffVals[100][2];
static int subsystem[2] = { 1, 2 };
static int currentSubsystem = 1;
static int appendArr = 0;

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
      controller_clear(E_CONTROLLER_MASTER);
      delay(10);
      controller_set_text(E_CONTROLLER_MASTER, 0, 0, "LIFT SUBSYSTEM");
      break;
    case 2:
      appendArr = 0;
      currentSubsystem = subsystem[1];
      controller_clear(E_CONTROLLER_MASTER);
      delay(10);
      controller_set_text(E_CONTROLLER_MASTER, 0, 0, "DRIVE SUBSYSTEM");
      break;
  }
}

void
getCheckpoint(void) {
  for (int i = appendArr; i < sizeof(checkpoint)/sizeof(checkpoint[0]); ++i) {
    switch(currentSubsystem) {
      case 1: /* DRIVE SUBSYSTEM */
        checkpoint[i][1] = getDriveVals();
        appendArr++;
        break;
      case 2: /* LIFT SUBSYSTEM */
        checkpoint[i][2] = getLiftVals();
        appendArr++;
        break;
    }
  }
}

void
genSensorVals(void) {
for (int i = 0; i < sizeof(diffVals)/sizeof(diffVals[0]); ++i) {
    switch(currentSubsystem) {
      case 1: /* DRIVE SUBSYTEM */
        diffVals[i][1] = checkpoint[i++][1] - checkpoint[i][1];
        break;
      case 2: /* LIFT SUBSYSTEM */
        diffVals[i][2] = checkpoint[i++][2] - checkpoint[i][2];
        break;
    }
  }
}

void
recorder(void) {
  genSensorVals();
  for (int i = 0; i < sizeof(diffVals)/sizeof(diffVals[0]); ++i) {
    switch(currentSubsystem) {
      case 1: /* DRIVE SUBSYSTEM */
        if (diffVals[i][1] != 0) {
          fprintf(stderr, "%s(%d);\n", DRIVE(s), diffVals[i][1]);

          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%d);\n", DRIVE(s), diffVals[i][1]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
      case 2: /* LIFT SUBSYSTEM */
        if (diffVals[i][2] != 0) {
          fprintf(stderr, "%s(%d);\n", LIFT(s), diffVals[i][2]);

          if (usd_is_installed()) {
            FILE *SDfile = fopen("/usd/auton-snippets.txt", "w");
            fprintf(SDfile, "%s(%d);\n", LIFT(s), diffVals[i][2]);
            fclose(SDfile);
          }
          else {}
        }
        else {}
        break;
    }
  }
}
