#ifndef _display_h_
#define _display_h_

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

/* Nokia LCD Pinout */
#define LCD_PIN_SCLK 9
#define LCD_PIN_DIN 8
#define LCD_PIN_DC 5
#define LCD_PIN_CS 6
#define LCD_PIN_RST 7

class Display {

  public:

  static Adafruit_PCD8544 controller;

  static long lastUpdate;

  static int updateCounter;
  
  /* Initialize the LED display */
  static void Initialize();
  static void TemperatureScreen();
  static void ShowMessage(String title, String message, bool clearDisplay = true);

};



#endif //_display_h_
