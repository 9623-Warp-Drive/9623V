typedef struct subsystem {
	long double rightCheckpoint[100];
	long double leftCheckpoint[100];

	long double rightDiffVals[100];
	long double leftDiffVals[100];

	long double avgDiffVals[100];

	char *outputText;
} subsystem;

extern unsigned char appendArr;

extern subsystem Drive;
extern subsystem Lift;
extern subsystem Intake;
extern subsystem Tray;

void resetVals(void);
void initRecorder(void);
void genOutput(void);
void getCheckpoint(void);
