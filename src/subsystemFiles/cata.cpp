#include "main.h"
#include "pros/rtos.hpp"

void setCata(int power) { cata = power; }

void controlCata() {
  bool downMode = bumper.get_value();

  if (controller.get_digital_new_press(DIGITAL_L1)) {
    if (!downMode) {
      while (!bumper.get_value()) {
        setCata(127);
      }
      setCata(0);
      downMode = true;
    }
    if (downMode) {
      setCata(127);
      pros::delay(200);
      setCata(0);
      downMode = false;
      pros::delay(200);

      while (!bumper.get_value()) {
        setCata(127);
      }
      setCata(0);

      downMode = true;
    }
  } else {
    setCata(0);
  }

  // if (controller.get_digital(DIGITAL_L2)) {
  //     setCata(127);
  // }
  // else if (controller.get_digital_new_press(DIGITAL_L1)) {
  //     while (!bumper.get_value()) {
  //         setCata(127);
  //     }
  //     setCata(0);
  // }
  // else {
  //     setCata(0);
  // }
}

void cataAsync() {}
