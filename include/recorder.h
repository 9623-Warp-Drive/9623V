#ifndef _AUTON_RECORDER_
#define _AUTON_RECORDER_

extern unsigned char currentSubsystem;
extern unsigned char appendArr;

extern long double rightDiffVals[100][5];
extern long double leftDiffVals[100][5];

void resetVals(void);
void initRecorder(void);
void genOutput(void);
void getCheckpoint(void);

#endif /* ifndef _AUTON_RECORDER */
