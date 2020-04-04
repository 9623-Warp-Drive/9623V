#include "pros.h"

extern "C" {
#include "gui.h"
#include "vision.h"
#include "recorder.h"
}

void
initialize(void)
{
	initRecorder();
	initVisionSensor();
	xinit();
}
