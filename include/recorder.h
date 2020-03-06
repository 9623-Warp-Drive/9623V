#ifndef _AUTON_RECORDER_
#define _AUTON_RECORDER_

#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"

extern int currentSubsystem;
extern int appendArr;
extern double diffVals[100][5];

void initRecorder(void);
void genOutput(void);
void getCheckpoint(void);
void switchSubsystem(void);

#endif /* ifndef _AUTON_RECORDER */
