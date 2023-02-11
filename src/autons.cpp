#include "main.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED =
    110; // This is 110/127 (around 87% of max speed).  We don't suggest making
         // this 127. If this is 127 and the robot tries to heading correct,
         // it's only correcting by making one side slower.  When this is 87%,
         // it's correcting by making one side faster and one side slower,
         // giving better heading correction.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

const int ROLLER_TIME = 90;

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier
// game objects, or with lifts up vs down. If the objects are light or the cog
// doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void leftAuto() {
  setDriveBrake();
  moveFeet(4.5, 127);
  pros::delay(200);
  setDrive(80, -80);
  pros::delay(160);
  setDrive(100, 100);
  pros::delay(185);
  setDrive(0, 0);
  pros::delay(350);
  setCata(127);
  pros::delay(200);
  setCata(0);
  pros::delay(200);
  while (!bumper.get_value()) {
    setCata(127);
  }
  setCata(0);
  setDrive(-80, 80);
  pros::delay(410); // 440 is 90 deg
  setDrive(0, 0);
  pros::delay(100);
  setIntake(127);
  moveFeet(-6.1, 127);
  pros::delay(200);
  setDrive(80, -80);
  pros::delay(335); // 440 is 90 deg
  setDrive(0, 0);
  setIntake(0);
  setDrive(-127 * 0.20, -127 * 0.20);
  pros::delay(1500);
  setIntake(-127);
  pros::delay(110);
  setDrive(50, 50);
  setIntake(0);
  pros::delay(200);
  setDrive(0, 0);
  setDriveCoast();
}

void leftRollerAuto() {
  setDrive(-100, -100);
  pros::delay(250);
  setIntake(-127);
  pros::delay(ROLLER_TIME);
  setDrive(50, 50);
  setIntake(0);
  pros::delay(400);
  setDrive(0, 0);
}

void rightAuto() {}

void rightRollerAuto() {
  setDrive(-100, -100);
  pros::delay(370);
  setDrive(0, 0);
  turnDegrees(90, 50, 1);
  setDrive(-100, -100);
  pros::delay(300);
  setIntake(-127);
  pros::delay(ROLLER_TIME);
  setDrive(50, 50);
  setIntake(0);
  pros::delay(200);
  setDrive(0, 0);
}

void twoRollerExpansion() {
  // setDrive(-75, -75);
  // pros::delay(300);
  // setIntake(-127);
  // pros::delay(210);
  // setIntake(0);
  // setDrive(0, 0);
  // moveFeet(2.1, 50);
  // pros::delay(500);
  // setDrive(80, -80);
  // pros::delay(440); // 440 is 90 deg
  // setDrive(0, 0);
  // pros::delay(500);
  // setDrive(-70, -70);
  // pros::delay(1250);
  // setIntake(-127);
  // pros::delay(150);
  // setIntake(0);
  // setDrive(0, 0);
  // pros::delay(500);
  // moveFeet(0.5, 50);
  // pros::delay(500);
  // setDrive(-80, 80);
  // pros::delay(440); // 440 is 90 deg
  // setDrive(0, 0);
  // moveFeet(-1.7, 50);
  // pros::delay(500);
  // setDrive(80, -80);
  // pros::delay(220); // 440 is 90 deg
  // setDrive(0, 0);
  // pros::delay(500);
  // moveFeet(0.57, 50);
  // pros::delay(500);
  trigger1.set_value(!trigger1.get_value());
  trigger2.set_value(!trigger2.get_value());
}