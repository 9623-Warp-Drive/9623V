#include "pros.h"
#include "port-config.hpp"

extern "C" {
#include "gui.h"
#include "vision.h"
}

static void
applySettings(void)
{
        drive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        tray.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
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
forwardIntake(int vel, double dist)
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
turnIntake(int vel, double deg)
{
        intake.forward(1);
        drive.setMaxVelocity(vel);
        drive.turnAngle(deg);
        intake.forward(0);
}

static void
alignStack(void)
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
alignToObject(void)
{
        while (errorDist() != 0) {
                if (errorDist() > 0)
                        drive.right(1);
                else if (errorDist() < 0)
                        drive.left(1);
                else
                        drive.stop();
        }
}

static void
topRed(void)
{
        deploy();
        forwardIntake(600, 500);
        forwardIntake(600, 1224.50);
        turn(600, -86);
        forwardIntake(600, 183.80);
        turn(600, -408);
        stack(35, 1144.3);
        forward(600, -200);
}

static void
botRed(void)
{
        drive.setMaxVelocity(60);
        deploy();
        forwardIntake(20, 1168.20);
        forwardIntake(600, -601.50);
        turn(600, 437);
        alignStack();
        stack(70, 422);
        intake.moveDistance(-350.8);
        forward(600, -200);
}

static void
topBlue(void)
{
        deploy();
        forwardIntake(600, 500);
        turn(600, -400);
        intake.moveDistance(-400);
        turn(600, 400);
        forwardIntake(600, 640.10);
        turn(600, 79);
        forwardIntake(600, 201.30);
        forward(600, -201.30);
        turn(600, 408);
        stack(35, 1144.3);
        forward(600, -200);
}

static void
botBlue(void)
{
        drive.setMaxVelocity(100);
        deploy();
        forwardIntake(100, 1168.20);
        forwardIntake(600, -601.50);
        turn(600, -437);
        alignStack();
        stack(70, 422);
        forward(600, -200);
}

void
autonomous(void)
{
        applySettings();
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
                deploy();
                break;
        default:
                deploy();
        }
}
