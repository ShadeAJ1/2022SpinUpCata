#include "main.h"
#include "pros/rtos.hpp"
#include <future>
bool downMode = bumper.get_value();

void setCata(int power) { cata = power; }

void setCataV(int voltage) { cata.move_voltage(voltage * 12001); }

void controlCata() {

  if (controller.get_digital_new_press(DIGITAL_UP)) {
    setCataV(1);
    pros::delay(200);
    setCataV(0);
    pros::delay(200);

    Task cataA(cataAsync);
    
  }

  if (controller.get_digital_new_press(DIGITAL_L1)) {
    if (!downMode) {
      while (!bumper.get_value()) {
        setCataV(1);
      }
      setCataV(0);
      downMode = true;
    }
    if (downMode) {
      setCataV(1);
      pros::delay(200);
      setCataV(0);
      downMode = false;
      pros::delay(200);

      Task cataA(cataAsync);
      // while (!bumper.get_value()) {
      //   setCata(127);
      // }
      // setCata(0);

      downMode = true;
    }
  } else {
    setCataV(0);
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

void cataAsync() {
  while (!bumper.get_value()) {
    setCataV(1);
  }
  setCataV(0);
}