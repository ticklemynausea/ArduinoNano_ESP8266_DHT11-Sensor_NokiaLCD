#ifndef _buttons_h_
#define _buttons_h_

#ifndef _include_libs_arduino_
#define _include_libs_arduino_
#include <Arduino.h>
#endif

#define GPIO_BUTTON_A 11
#define GPIO_BUTTON_B 12
#define NUM_BUTTONS 2

#define FOR_b for (int b = 0; b < NUM_BUTTONS; b++)

class Buttons {
  public:
  
  static uint8_t pinout[NUM_BUTTONS];
  static uint8_t state[NUM_BUTTONS];
  
  /* Initialize Buttons */
  static void Initialize();
  
  /* Reads the input from the tactile switches connected to the digital input pins in Buttons_Pinout[] */
  static void Read();
  
  /* button callbacks */
  static void (*callbacks[NUM_BUTTONS])();

  static bool IsPressed(uint8_t gpio);
  
};

#endif
