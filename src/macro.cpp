#include "port-config.hpp"
#include "recorder.h"

void
stackMacro(void)
{
	tray.moveDistance(1118.00);
}

void
liftMacro(char pos)
{
	if (pos == 0) {
		tray.moveDistance(384.40);
		lift.moveDistance(238.8);
	} else if (pos == 1) {
		tray.moveDistance(384.40);
		lift.moveDistance(238.8);
		tray.moveDistance(200);
		lift.moveDistance(193.70);
	}
}
