#include "port-config.hpp"
#include "vision.h"

static void deploy(void);
static void forward(int vel, double dist);
static void forward_intake(int vel, double dist);
static void turn(int vel, double deg);
static void align_stack(void);
static void stack(int vel, double dist);
static void align_to_object(void);

void
top_red(void)
{
	deploy();
	forward_intake(600, 500);
	forward_intake(600, 1224.50);
	turn(600, -86);
	forward_intake(600, 183.80);
	turn(600, -408);
	stack(35, 1144.3);
	forward(600, -200);
}

void
bot_red(void)
{
	drive.setMaxVelocity(60);
	deploy();
	forward_intake(20, 1168.20);
	forward_intake(600, -601.50);
	turn(600, 437);
	align_stack();
	stack(70, 422);
	intake.moveDistance(-350.8);
	forward(600, -200);
}

void
top_blue(void)
{
	deploy();
	forward_intake(600, 500);
	turn(600, -400);
	intake.moveDistance(-400);
	turn(600, 400);
	forward_intake(600, 640.10);
	turn(600, 79);
	forward_intake(600, 201.30);
	forward(600, -201.30);
	turn(600, 408);
	stack(35, 1144.3);
	forward(600, -200);
}

void
bot_blue(void)
{
	drive.setMaxVelocity(100);
	deploy();
	forward_intake(100, 1168.20);
	forward_intake(600, -601.50);
	turn(600, -437);
	align_stack();
	stack(70, 422);
	forward(600, -200);
}

void
null_auton(void)
{
	deploy();
	align_to_object();
}

static void
deploy(void)
{
	trayAsync.tarePosition();
	trayAsync.setTarget(573.60);
	lift.moveDistance(90.3);
	trayAsync.waitUntilSettled();
	lift.waitUntilSettled();

	trayAsync.setTarget(0);
	lift.moveDistance(-90.3);
	trayAsync.waitUntilSettled();
}

static void
forward(int vel, double dist)
{
	drive.setMaxVelocity(vel);
	drive.moveDistance(dist);
}

static void
forward_intake(int vel, double dist)
{
	intake.forward(1);
	drive.setMaxVelocity(vel);
	drive.moveDistance(dist);
	intake.forward(0);
}

static void
turn(int vel, double deg)
{
	drive.setMaxVelocity(vel);
	drive.turnAngle(deg);
}

static void
align_stack(void)
{
	intakeAsync.tarePosition();
	intakeAsync.setTarget(-177.40);
	intakeAsync.waitUntilSettled();
}

static void
stack(int vel, double dist)
{
	trayAsync.setMaxVelocity(vel);
	drive.setMaxVelocity(600);

	drive.moveDistanceAsync(dist);
	trayAsync.setTarget(1120.00);
	drive.waitUntilSettled();
	trayAsync.waitUntilSettled();
}

static void
align_to_object(void)
{
	while (get_displacement() != 0) {
		if (get_displacement() > 0)
			drive.right(1);
		else if (get_displacement() < 0)
			drive.left(1);
		else
			drive.stop();
	}
}
