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

void spin() {
    Spinners.spin(forward);
}

void up() {
    Conveyor.spin(forward);
}

void down() {
    Conveyor.spin(reverse);
}

void stopSpinning() {
    Spinners.stop();
}

void stopBelt() {
    Conveyor.stop();
}

void Autonomous() {
    
}

void UserControl() {
    while (true) {
        // Display
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Let's go DummyBeast!");
        Brain.Screen.newLine();
        Brain.Screen.print("Drive train temp %f", Drivetrain.temperature(percent));
        Brain.Screen.newLine();
        Brain.Screen.print("Ramp temp %f", Conveyor.temperature(percent));
        Brain.Screen.newLine();
        Brain.Screen.print("Spinners temp %f", Spinners.temperature(percent));

        // Movement
        Controller1.ButtonR1.pressed(up);
        Controller1.ButtonR1.released(stopBelt);
        Controller1.ButtonR2.pressed(down);
        Controller1.ButtonR2.released(stopBelt);

        Controller1.ButtonL1.pressed(spin);
        Controller1.ButtonL1.released(stopSpinning);
        
        wait(20, msec);
    }
}

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // Customizations
    turningSensitivity = 3;
    Drivetrain.setStopping(hold); // automatically account for inertia

    Spinners.setVelocity(600, rpm);
    Spinners.setStopping(brake);

    Conveyor.setVelocity(200, rpm);

    // Listen for Field Switch
    Competition.drivercontrol(UserControl);
    Competition.autonomous(Autonomous);
}
