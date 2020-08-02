#include "pros/rtos.hpp"

#include "auton.hpp"
#include "gui.h"
#include "main.hpp"
#include "mappings.hpp"
#include "port-config.hpp"
#include "recorder.h"
#include "statusline.hpp"
#include "switcher.hpp"
#include "vision.h"

void
initialize(void)
{
	apply_config();
	init_recorder();
	init_vision();
	xinit();
}

void
autonomous(void)
{
	switch (current_auton) {
	case 1:
		top_red();
		break;
	case 2:
		bot_red();
		break;
	case 3:
		top_blue();
		break;
	case 4:
		bot_blue();
		break;
	case 5:
	default:
		null_auton();
	}
}

void
opcontrol(void)
{
	for (;;) {
		apply_mapping();
		update_status();

		pros::delay(1);
	}
}
