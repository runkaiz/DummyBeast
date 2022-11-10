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

void spins(bool out);

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // Customizations
    turningSensitivity = 1;
    Drivetrain.setStopping(hold); // automatically account for inertia

    Spinners.setVelocity(600, rpm)
    Conveyor.setVelocity(200, rpm);

    // Variables
    bool dir = false;

    while (true) {
        if (Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing()) {
            if (Controller1.ButtonR1.pressing()) {
                dir = true;
            } else {
                dir = false;
            }

            spins(dir);
        }
        
        wait(20, msec);
    }
}

void spins(bool out)
{
    if (out) {
        Spinners.spin(forward);
        Conveyor.spin(forward);
    } else {
        Spinners.spin(reverse);
        Conveyor.spin(reverse);
    }
}
