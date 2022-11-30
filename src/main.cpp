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

void spin() {
    Spinners.spin(forward);
    Conveyor.spin(forward);
}

void stop() {
    Spinners.stop();
    Conveyor.stop();
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

    while (true) {
        Controller1.ButtonR1.pressed(spin);
        Controller1.ButtonR1.released(stop);
        
        wait(20, msec);
    }
}
