#include "switcher.hpp"

/*
 * 0 = Macro Recorder
 * 1 = Autonomous Related
 * 2 = Macro
 */
int currentLayout = 0;

/*
 * 0 = Drive
 * 1 = Lift
 * 2 = Intake
 * 3 = Tray
 */
int currentSubsystem = 0;

/*
 * 1 = Top Red
 * 2 = Bot Red
 * 3 = Top Blue
 * 4 = Bot Blue
 */
int currentAuton = 0;

void
switchMode(int mode, int NumOfMode)
{
        if (mode < NumOfMode)
                mode++;
        else
                mode = 1;
}
