#include "main.h"
#include "pros/misc.h"

void controlTrigger() {
  bool holding = false;

  if (controller.get_digital_new_press(DIGITAL_X)) {
    trigger.set_value(!trigger.get_value());
  }
  if (controller.get_digital_new_press(DIGITAL_A)) {
    blocker.set_value(!blocker.get_value());
  }

  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
    chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  }
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
    chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  }
}