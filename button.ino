#include "button.h"

byte button_get_state() {

  static unsigned int btn_press=0;
  static bool btn_attended=false;

  if (!digitalRead(BUTTON)) {
    if (btn_press) {
      if (xTaskGetTickCount() - btn_press > BUTTON_TIME_LONG) {
        if (btn_attended) {
          return BUTTON_PRESS_NONE;
        } else {
          btn_attended=true;
          return BUTTON_PRESS_LONG;
        }
      }
    } else {
      btn_press=xTaskGetTickCount();
    }
  } else if (btn_press) {
    btn_press=0;
    if (btn_attended) {
      btn_attended=false;
    } else {
      return BUTTON_PRESS_SHORT;
    }
  }
  return BUTTON_PRESS_NONE;

}

