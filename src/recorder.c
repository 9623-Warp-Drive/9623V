#include <stdio.h>
#include <math.h>

#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"

#include "pros.h"
#include "recorder.h"

unsigned char currentSubsystem = 0; // 0 - FORWARD | 1 - TURN | 2 - LIFT | 3 - INTAKE | 4 - TRAY
unsigned char appendArr = 1;
double diffVals[100][5];
static char *outputText;
static double checkpoint[100][5];

static void genSensorVals(void);
static void setCommand(void);

void
resetVals(void)
{
        appendArr = 1;
        for (int i = 0; i < 100; ++i) {
                for (int y = 0; y < 5; ++y) {
                        diffVals[i][y] = 0;
                        checkpoint[i][y] = 0;
                }
        }
}

void
initRecorder(void)
{
        resetVals();
        for (int i = 0; i < 20; ++i) {
                motor_set_encoder_units(i, E_MOTOR_ENCODER_DEGREES);
                motor_tare_position(i);
        }
}

void
getCheckpoint(void)
{
        for (int i = appendArr; i < 100; ++i) switch(currentSubsystem) {
        case 0:
                checkpoint[i][0] = (motor_get_position(1) + motor_get_position(10)) / 2;
                break;
        case 1:
                checkpoint[i][1] = (fabs(motor_get_position(1)) + fabs(motor_get_position(10))) / 2;
                break;
        case 2:
                checkpoint[i][2] = (motor_get_position(13) + motor_get_position(20)) / 2;
                break;
        case 3:
                checkpoint[i][3] = (motor_get_position(2) + motor_get_position(9)) / 2;
                break;
        case 4:
                checkpoint[i][4] = (motor_get_position(16) + motor_get_position(15)) / 2;
                break;
        }
        appendArr++;
}

void
genSensorVals(void)
{
        for (int i = 0; i < 99; ++i)
                diffVals[i][currentSubsystem] = checkpoint[++i][currentSubsystem] - checkpoint[--i][currentSubsystem];
}

void
setCommand(void)
{
        switch (currentSubsystem) {
                /* Set text to desired command */
        case 0: outputText = "Drive.moveDistance";
                break;
        case 1: outputText = "Drive.turnAngle";
                break;
        case 2: outputText = "Lift.moveDistance";
                break;
        case 3: outputText = "Intake.moveDistance";
                break;
        case 4: outputText = "Tray.moveDistance";
                break;
        }

}

void
genOutput(void)
{
        genSensorVals();
        setCommand();
        fflush(stderr);
        for (int i = 0; i < appendArr; ++i) {
                if (diffVals[i][currentSubsystem] != 0)
                        fprintf(stderr, "%s(%f);\n", outputText, diffVals[i][currentSubsystem]);
        }
}
