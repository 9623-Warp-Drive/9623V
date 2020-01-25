#ifndef _AUTON_RECORDER_
#define _AUTON_RECORDER_

#include "pros/misc.h"

void getCheckpoint(void);
void switchSubsystem(void);
void recorder(void);

extern int getDriveVals(void);
extern int getLiftVals(void);

#endif /* ifndef _AUTON_RECORDER */
