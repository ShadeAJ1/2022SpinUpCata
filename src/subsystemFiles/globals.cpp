#include "main.h"

Motor frontLeft(frontLeftPort, E_MOTOR_GEARSET_18, true);
Motor centerLeft(centerLeftPort, E_MOTOR_GEARSET_18, true);
Motor backLeft(backLeftPort, E_MOTOR_GEARSET_18, true);

Motor frontRight(frontRightPort, E_MOTOR_GEARSET_18, false);
Motor centerRight(centerRightPort, E_MOTOR_GEARSET_18, false);
Motor backRight(backRightPort, E_MOTOR_GEARSET_18, false);

Motor cata(cataPort, E_MOTOR_GEARSET_36, false);
Motor intake1(intakePort1, E_MOTOR_GEARSET_06);

ADIPort trigger1(triggerPort1, ADI_DIGITAL_OUT);
ADIPort trigger2(triggerPort2, ADI_DIGITAL_OUT);
ADIPort bumper(bumperPort, ADI_DIGITAL_IN);

// Imu gyro(gyroPort);

Controller controller(E_CONTROLLER_MASTER);
