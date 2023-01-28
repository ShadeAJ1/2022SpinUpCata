#include "main.h"

void controlTrigger() {
  if (controller.get_digital_new_press(DIGITAL_X)) {
    trigger1.set_value(!trigger1.get_value());
    trigger2.set_value(!trigger2.get_value());
  }
}