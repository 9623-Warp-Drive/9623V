#include "switcher.hpp"

/*
 * 0 = Macro Recorder
 * 1 = Autonomous Related
 * 2 = Macro
 */
int current_layout = 0;

/*
 * 0 = Drive
 * 1 = Lift
 * 2 = Intake
 * 3 = Tray
 */
int current_subsystem = 0;

/*
 * 1 = Top Red
 * 2 = Bot Red
 * 3 = Top Blue
 * 4 = Bot Blue
 */
int current_auton = 0;

void
switch_mode(int *mode, int mode_count)
{
	if (*mode < mode_count)
		(*mode)++;
	else
		*mode = 1;
}
