#ifndef __BUTTON_H
#define __BUTTON_H

#define BUTTON 0              // button pin
#define BUTTON_TIME_LONG  500 // in miliseconds

enum button_press_state {
  BUTTON_PRESS_NONE,
  BUTTON_PRESS_SHORT,
  BUTTON_PRESS_LONG
};

#endif
