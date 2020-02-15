#ifndef _AUTON_RECORDER_
#define _AUTON_RECORDER_

#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"

extern int currentSubsystem;

void initRecorder(void);
void getCheckpoint(void);
void switchSubsystem(void);
void recorder(void);

#endif /* ifndef _AUTON_RECORDER */
