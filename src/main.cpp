#include "pros/rtos.hpp"

#include "function.hpp"
#include "gui.h"
#include "main.hpp"
#include "recorder.h"
#include "vision.h"

void
initialize(void)
{
	applyConfig();
	initRecorder();
	initVisionSensor();
	xinit();
}

void
autonomous(void)
{
	switch (auton) {
	case 1: /* TOP RED AUTONOMOUS */
		topRed();
		break;
	case 2: /* BOTTOM RED AUTONOMOUS */
		botRed();
		break;
	case 3: /* TOP BLUE AUTONOMOUS */
		topBlue();
		break;
	case 4: /* BOTTOM BLUE AUTONOMOUS */
		botBlue();
		break;
	case 5: /* SKILL AUTONOMOUS */
		break;
	default:
		nullAuton();
	}
}

void
opcontrol(void)
{
	for (;;) {
		mappings();
		updateStatus();

		pros::delay(1);
	}
}
