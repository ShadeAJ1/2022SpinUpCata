#include "main.h"

// MOTORS
extern Motor frontRight;
extern Motor centerRight;
extern Motor backRight;
extern Motor frontLeft;
extern Motor centerLeft;
extern Motor backLeft;

extern Motor cata;
extern Motor intake1;

// PNEUMATICS
extern ADIPort trigger;
extern ADIPort bumper;
extern ADIPort blocker;

// MISC
extern Imu gyro;
extern Controller controller;

// MATH
#define driveGearRatio 2
#define wheelDiameter 2.75

// PORTS
#define frontRightPort 6
#define centerRightPort 2
#define backRightPort 9
#define frontLeftPort 21
#define centerLeftPort 8
#define backLeftPort 11

#define intakePort1 7
#define cataPort 3

#define triggerPort 'E'
#define bumperPort 'A'
#define blockerPort 'B'