#ifndef _routine_h_
#define _routine_h_

#include "Display.h"
#include "Buttons.h"


/* Time intervals between updates */
#define SENSOR_POLL_INTERVAL 2000
#define LCD_DISPLAY_INTERVAL 1000
#define HTTP_POST_INTERVAL 30000

#define SLEEP_MAX 200
#define SLEEP_STEP 20

/* Loop Routines */
class Routine {

  public:
  
  static uint16_t sleep;
  static uint16_t pause;
  
  static void (*Buttons)();

  static void Initialize();
  static void Nop();
  static void Sleep();

  static void DHTSensor();
  static void Display();
  static void WifiSerial();

};

#endif
