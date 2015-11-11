#include "display.h"
#include "dhtsensor.h"

Adafruit_PCD8544 Display::controller = Adafruit_PCD8544(LCD_PIN_SCLK, LCD_PIN_DIN, LCD_PIN_DC, LCD_PIN_CS, LCD_PIN_RST);

long Display::lastUpdate = 0;

int Display::updateCounter = 0;

/* Initialize Nokia LCD Display */
void Display::Initialize() {

  Display::controller.begin();
  
  Display::controller.setContrast(50);
  Display::controller.setRotation(2);

  //Display::controller.display(); // show splashscreen
  Display::controller.clearDisplay();   // clears the screen and buffer

  //delay(2000);
}

void Display::TemperatureScreen() {
    Display::controller.setTextSize(1);
    
    Display::controller.clearDisplay();   // clears the screen and buffer
    Display::controller.setCursor(0,0);
    Display::controller.setTextColor(WHITE, BLACK); // 'inverted' text
    Display::controller.println(F(" #IoT FTW :-) "));
    Display::controller.setTextColor(BLACK, WHITE);
    Display::controller.print(F("Temp:  "));
    Display::controller.println(String(DHTSensor::temperatureValue) + F(" C"));
    Display::controller.print(F("Humi:  "));
    Display::controller.println(String(DHTSensor::humidityValue) + F(" %"));

    for (int i=0; i <= Display::updateCounter % 6; i++) {
      Display::controller.drawPixel((84/2)+(i*2), 44, BLACK);
      Display::controller.drawPixel((84/2)-(i*2), 44, BLACK);
      Display::controller.drawPixel((84/2)+(i*2), 45, BLACK);
      Display::controller.drawPixel((84/2)-(i*2), 45, BLACK);
    }

    Display::controller.setCursor(3,0);

    Display::controller.display();
    Display::updateCounter++;
}


void Display::ShowMessage(String title, String message, bool clearDisplay) {

    Display::controller.setTextSize(1);

    if (clearDisplay) {
      Display::controller.clearDisplay();   // clears the screen and buffer
    }

    Display::controller.setCursor(0,0);
    Display::controller.setTextColor(WHITE, BLACK); // 'inverted' text
    Display::controller.println(title);
    Display::controller.setTextColor(BLACK, WHITE);
    Display::controller.println(message);
    Display::controller.display();
}
