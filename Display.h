#ifndef _display_h_
#define _display_h_

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

/* Phsyical circuit connections */
#define LCD_PIN_SCLK 9
#define LCD_PIN_DIN 8
#define LCD_PIN_DC 5
#define LCD_PIN_CS 6
#define LCD_PIN_RST 7

/* LCD characteristics */
#define LCD_WIDTH 84
#define LCD_HEIGHT 48
#define LCD_HEIGHT8 (LCD_HEIGHT >> 3)

/* * set/unset */
#define PIXEL_SET(x, y) Display::controller.drawPixel(x, y, BLACK);
#define PIXEL_UNSET(x, y) Display::controller.drawPixel(x, y, WHITE);

/* * checks if n is in the interval [a, b] * */
#define BETWEEN(n, a, b) ((n >= a) && (n <= b))

/* * over matrix buffer width */
#define FOR_i for (uint8_t i = 0; i < LCD_WIDTH; i++)
/* * over matrix buffer height */
#define FOR_j for (uint8_t j = 0; j < LCD_HEIGHT8; j++)

/* * over screen width * */
#define FOR_x for (uint8_t x = 0; x < LCD_WIDTH; x++)

/* * over screen height * */
#define FOR_y for (uint8_t y = 0; y < LCD_HEIGHT; y++)

class Display {

  public:

  static Adafruit_PCD8544 controller;

  static long lastUpdate;

  static int updateCounter;

  /* Helpers */
  static void Set(uint8_t  x, uint8_t y);
  static void Unset(uint8_t  x, uint8_t y);
  static void DrawLine(uint8_t x0, uint8_t  y0, uint8_t  x1, uint8_t  x2, uint8_t color);
  static void DrawText(uint8_t x, uint8_t y, String &text);
  static void UpdateFromDisplay();

  /* Initialize the LED display */
  static void Initialize();
  static void TemperatureScreen();
  static void StatusScreen();
  static void ShowMessage(String title, String message, bool clearDisplay = true);

};



#endif //_display_h_
