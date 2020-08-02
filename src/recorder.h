typedef struct subsystem {
	long double rightCheckpoint[100];
	long double leftCheckpoint[100];

	long double rightDiffVals[100];
	long double leftDiffVals[100];

	long double avgDiffVals[100];

	char *outputText;
} subsystem;

extern int append_array;

extern subsystem Drive;
extern subsystem Lift;
extern subsystem Intake;
extern subsystem Tray;

void reset_values(void);
void init_recorder(void);
void generate_output(void);
void get_checkpoint(void);
