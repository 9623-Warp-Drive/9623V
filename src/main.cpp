#include "pros/rtos.hpp"

#include "auton.hpp"
#include "main.hpp"
#include "mappings.hpp"
#include "gui.h"
#include "recorder.h"
#include "statusline.hpp"
#include "switcher.hpp"
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
	switch (currentAuton) {
	case 1:
		topRed();
		break;
	case 2:
		botRed();
		break;
	case 3:
		topBlue();
		break;
	case 4:
		botBlue();
		break;
	case 5:
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
