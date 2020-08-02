#include "pros/misc.hpp"

#include "macro.hpp"
#include "main.hpp"
#include "mappings.hpp"
#include "port-config.hpp"
#include "recorder.h"
#include "rerun.hpp"
#include "statusline.hpp"
#include "switcher.hpp"

static void arcade_mapping(void);
static void intake_mapping(pros::controller_digital_e_t inward,
                           pros::controller_digital_e_t outward);
static void lift_mapping(pros::controller_digital_e_t up,
                         pros::controller_digital_e_t down);
static void tray_mapping(pros::controller_digital_e_t forward,
                         pros::controller_digital_e_t backward);

static void layout_mapping(void);
static void record_mapping(void);
static void auton_mapping(void);
static void macro_mapping(void);

void
apply_mapping(void)
{
	arcade_mapping();
	intake_mapping(pros::E_CONTROLLER_DIGITAL_R2,
	               pros::E_CONTROLLER_DIGITAL_R1);
	lift_mapping(pros::E_CONTROLLER_DIGITAL_L1,
	             pros::E_CONTROLLER_DIGITAL_L2);
	tray_mapping(pros::E_CONTROLLER_DIGITAL_X,
	             pros::E_CONTROLLER_DIGITAL_B);

	layout_mapping();
	if (current_layout == 0)
		record_mapping();
	else if (current_layout == 1)
		auton_mapping();
	else if (current_layout == 2)
		macro_mapping();
}

static void
arcade_mapping(void)
{
	drive.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
	             controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
}

static void
intake_mapping(pros::controller_digital_e_t inward, pros::controller_digital_e_t outward)
{
	intake.setMaxVelocity(600);
	if (controller.get_digital(inward))
		intake.forward(1);
	else if (controller.get_digital(outward))
		intake.forward(-1);
	else
		intake.stop();
}

static void
lift_mapping(pros::controller_digital_e_t up, pros::controller_digital_e_t down)
{
	lift.setMaxVelocity(30);
	if (controller.get_digital(up))
		lift.forward(1);
	else if (controller.get_digital(down))
		lift.forward(-1);
	else
		lift.stop();
}

static void
tray_mapping(pros::controller_digital_e_t forward, pros::controller_digital_e_t backward)
{
	tray.setMaxVelocity(70);
	if (controller.get_digital(forward))
		tray.forward(1);
	else if (controller.get_digital(backward))
		tray.forward(-1);
	else
		tray.forward(0);
}

static void
layout_mapping(void)
{
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		switch_mode(&current_layout, 2);
	else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) && 
	         controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		print_current_layout();
	else
		controller.clear_line(2);
}

static void
record_mapping(void)
{
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	    controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		switch_mode(&current_subsystem, 3);
		print_current_subsystem();
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	           controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		get_checkpoint();
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	           controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		reset_values();
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	           controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
		preview_recorded_values();
	} else {
		controller.clear();
	}
}

static void
auton_mapping(void)
{
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	    controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		switch_mode(&current_auton, 5);
		print_current_auton();
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	           controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		autonomous();
	} else {
		controller.clear_line(2);
	}

	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	    controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
		run();
	else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	         controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
		reverse();
}

static void
macro_mapping(void)
{
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	    controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
		stack_macro();
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	           controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		lift.stop();
		tray.forward(1);
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	           controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		lift.stop();
		tray.forward(-1);
	}

	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	    controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		lift_macro(0);
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	           controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		lift_macro(1);
	}

	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	    controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
		intake.setMaxVelocity(200);
		intake.forward(-1);
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && 
	           controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
		intake.setMaxVelocity(200);
		intake.forward(1);
	}
}
