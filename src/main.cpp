#include "function.hpp"
#include "gui.h"
#include "pros.h"
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
	while (true) {
		mappings();
	}
}
