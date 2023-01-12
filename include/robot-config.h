using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor leftSpinner;
extern motor rightSpinner;
extern motor_group Spinners;
extern motor Conveyor;
extern motor Booster;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

extern int turningSensitivity;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
