#include "main.h"
#include "autons.hpp"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    {-21, -8, -11}

    // Right Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    ,
    {6, 2, 9}

    // IMU Port
    ,
    16

    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    //    (or tracking wheel diameter)
    ,

    2.75

    // Cartridge RPM
    //   (or tick per rotation if using tracking wheels)
    ,
    200

    // External Gear Ratio (MUST BE DECIMAL)
    //    (or gear ratio of tracking wheel)
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO would
    // be 2.333. eg. if your drive is 36:60 where the 60t is powered, your RATIO
    // would be 0.6.
    ,
    2

    // Uncomment if using tracking wheels
    /*
    // Left Tracking Wheel Ports (negative port will reverse it!)
    // ,{1, 2} // 3 wire encoder
    // ,8 // Rotation sensor

    // Right Tracking Wheel Ports (negative port will reverse it!)
    // ,{-3, -4} // 3 wire encoder
    // ,-9 // Rotation sensor
    */

    // Uncomment if tracking wheels are plugged into a 3 wire expander
    // 3 Wire Port Expander Smart Port
    // ,1
);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D

  pros::delay(
      500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(
      true); // Enables modifying the controller curve with buttons on the
             // joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(
      0, 0); // Defaults for curve. If using tank, only the first parameter is
             // used. (Comment this line out if you have an SD card!)
  default_constants(); // Set the drive to your own constants from autons.cpp!

  chassis.imu.reset();
  pros::delay(
      2000); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the
  // left/right curve buttons here! chassis.set_left_curve_buttons
  // (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If
  // using tank, only the left side is used.
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,
  // pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
      Auton("LEFT Roller + Shoot Auton", leftAuto),
      Auton("LEFT Roller ONLY Auton", leftRollerAuto),

      Auton("RIGHT Roller + Shoot Auton", rightAuto),
      Auton("RIGHT Roller ONLY Auton", rightRollerAuto),
      Auton("Skills", twoRollerExpansion),

      // Example Autons
      Auton("Example Drive\n\nDrive forward and come back.", drive_example),
      Auton("Example Turn\n\nTurn 3 times.", turn_example),
      Auton("Drive and Turn\n\nDrive forward, turn, come back. ",
            drive_and_turn),
      Auton("Drive and Turn\n\nSlow down during drive.",
            wait_until_change_speed),
      Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
      Auton("Combine all 3 movements", combining_movements),
      Auton("Interference\n\nAfter driving forward, robot performs differently "
            "if interfered or not.",
            interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

  cata.set_brake_mode(MOTOR_BRAKE_COAST);
  intake1.set_brake_mode(MOTOR_BRAKE_COAST);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets();               // Resets PID targets to 0
  chassis.reset_gyro();                      // Reset gyro position to 0
  chassis.reset_drive_sensor();              // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps
                                             // autonomous consistency.

  // twoRollerExpansion();

  ez::as::auton_selector
      .call_selected_auton(); // Calls selected auton from autonomous
  //     selector.
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {

    chassis.tank();

    // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    controlIntake();
    controlCata();
    controlTrigger();

    // if (controller.get_digital_new_press(DIGITAL_L1)) {
    //   if (!downMode) {
    //     while (!bumper.get_value()) {
    //       setCata(127);
    //     }
    //     setCata(0);
    //     downMode = true;
    //   }
    //   if (downMode) {
    //     setCata(127);
    //     pros::delay(200);
    //     setCata(0);
    //     downMode = false;
    //     pros::delay(200);

    //     while (!bumper.get_value()) {
    //       setCata(127);
    //     }
    //     setCata(0);

    //     downMode = true;
    //   }
    // } else {
    //   setCata(0);
    // }

    // std::cout << " New Gyro Heading: ";
    // std::cout << (chassis.imu.get_heading());

    if (master.get_digital_new_press(DIGITAL_B)) {
      autonomous();

      // moveFeet(1,80);
      //  resetDriveEncoders();
      //  std :: cout(avgDrivePosition()); // cout it
      //  setDrive(80,80); // how long does it tke to move one foot forward
      //  pros :: delay(1000);
      //  setDrive(0,0);
      //  std :: cout (avgDrivePosition());
      //  pros :: delay(5000);
      //  resetDriveEncoders();
      //  std :: cout (avgDrivePosition());
      //  setDrive(80,80); // how long does it tke to move one foot forward
      //  pros :: delay(750);
      //  setDrive(0,0);
      //  std :: cout (avgDrivePosition());
      //  pros :: delay(5000);
      //  resetDriveEncoders();
      //  std :: cout (avgDrivePosition());
      //  setDrive(80,80); // how long does it tke to move one foot forward
      //  pros :: delay(500);
      //  setDrive(0,0);
      //  std :: cout (avgDrivePosition());
      //  pros :: delay(10000);
      //  // turn testing aim for a full 90 degree turn left

      // for(i = 500; i < 1000; i += 250)
      // {
      //   setDrive(-60,60);
      //   pros :: delay(i);
      //   setDrive(0,0);
      //   pros :: delay(5000)
      // }
    }

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!
                                       // Keep this ez::util::DELAY_TIME
  }
}
