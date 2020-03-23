#ifndef _AUTON_RECORDER_
#define _AUTON_RECORDER_

extern unsigned char currentSubsystem;
extern unsigned char appendArr;
extern double diffVals[100][5];

void resetVals(void);
void initRecorder(void);
void genOutput(void);
void getCheckpoint(void);

#endif /* ifndef _AUTON_RECORDER */
