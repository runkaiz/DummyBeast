/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       runkai                                                    */
/*    Created:      Wed Oct 12 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 3, 4
// Controller1          controller
// Spinners             motor_group   5, 6
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

bool shootingMode = false;

void spin()
{
    Spinners.spin(forward);
}

void up()
{
    Conveyor.spin(forward);

    if (shootingMode) {
        Booster.spin(forward);
    }
}

void down()
{
    Conveyor.spin(reverse);
}

void stopSpinning()
{
    Spinners.stop();
}

void stopBelt()
{
    Conveyor.stop();
    Booster.stop();
}

void toggleMode() {
    Conveyor.stop();
    Booster.stop();
    Spinners.stop();
    shootingMode = !shootingMode;

    if (shootingMode) {
        spin();
    }
}

void Autonomous()
{
}

void UserControl()
{
    bool DrivetrainLNeedsToBeStopped_Controller1 = true;
    bool DrivetrainRNeedsToBeStopped_Controller1 = true;

    while (true)
    {
        // calculate the drivetrain motor velocities from the controller joystick axies
        // left = Axis3 + Axis1
        // right = Axis3 - Axis1
        int drivetrainLeftSideSpeed = (Controller1.Axis3.position() + Controller1.Axis1.position() / (6 / turningSensitivity));
        int drivetrainRightSideSpeed = (Controller1.Axis3.position() - Controller1.Axis1.position() / (6 / turningSensitivity));

        // check if the value is inside of the deadband range
        if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5)
        {
            // check if the left motor has already been stopped
            if (DrivetrainLNeedsToBeStopped_Controller1)
            {
                // stop the left drive motor
                LeftDriveSmart.stop();
                // tell the code that the left motor has been stopped
                DrivetrainLNeedsToBeStopped_Controller1 = false;
            }
        }
        else
        {
            // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
            DrivetrainLNeedsToBeStopped_Controller1 = true;
        }
        // check if the value is inside of the deadband range
        if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5)
        {
            // check if the right motor has already been stopped
            if (DrivetrainRNeedsToBeStopped_Controller1)
            {
                // stop the right drive motor
                RightDriveSmart.stop();
                // tell the code that the right motor has been stopped
                DrivetrainRNeedsToBeStopped_Controller1 = false;
            }
        }
        else
        {
            // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
            DrivetrainRNeedsToBeStopped_Controller1 = true;
        }

        // only tell the left drive motor to spin if the values are not in the deadband range
        if (DrivetrainLNeedsToBeStopped_Controller1)
        {
            LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
            if (shootingMode) {
                LeftDriveSmart.spin(reverse);
            } else {
                LeftDriveSmart.spin(forward);
            }
        }
        // only tell the right drive motor to spin if the values are not in the deadband range
        if (DrivetrainRNeedsToBeStopped_Controller1)
        {
            RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
            if (shootingMode) {
                RightDriveSmart.spin(reverse);
            } else {
                RightDriveSmart.spin(forward);
            }
        }

        // Display
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.print("Let's go DummyBeast!");
        Brain.Screen.newLine();
        Brain.Screen.print("Drive train temp %f", Drivetrain.temperature(percent));
        Brain.Screen.newLine();
        Brain.Screen.print("Ramp temp %f", Conveyor.temperature(percent));
        Brain.Screen.newLine();
        Brain.Screen.print("Spinners temp %f", Spinners.temperature(percent));
        Brain.Screen.newLine();
        Brain.Screen.print("Booster temp %f", Booster.temperature(percent));
        Brain.Screen.newLine();
        Brain.Screen.print("Throwing Mode %s", shootingMode?"true":"false");

        Controller1.ButtonX.pressed(toggleMode);

        Controller1.ButtonR1.pressed(up);
        Controller1.ButtonR1.released(stopBelt);
        Controller1.ButtonR2.pressed(down);
        Controller1.ButtonR2.released(stopBelt);

        wait(20, msec);
    }
}

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // Customizations
    turningSensitivity = 3;
    //Drivetrain.setStopping(brake);

    leftSpinner.setVelocity(600, rpm);
    rightSpinner.setVelocity(575, rpm);
    Spinners.setStopping(coast);

    Conveyor.setVelocity(200, rpm);
    Conveyor.setStopping(brake);

    Booster.setVelocity(200, rpm);
    Booster.setStopping(brake);

    // Listen for Field Switch
    Competition.drivercontrol(UserControl);
    Competition.autonomous(Autonomous);
}
