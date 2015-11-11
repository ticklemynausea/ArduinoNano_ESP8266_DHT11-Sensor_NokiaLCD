/*
   DHT11 Temperature/Humidity Sensor in the IoT
   Arduino Nano + ESP8266 Serial2Wifi

   https://thingspeak.com/channels/56753

*/

#include "Display.h"
#include "WifiSerial.h"
#include "DHTSensor.h"

/* Baud rate for the hardware serial */
#define SERIAL_BAUD_RATE 9600

/* Time intervals between updates */
#define SENSOR_POLL_INTERVAL 2000
#define LCD_DISPLAY_INTERVAL 1000
#define HTTP_POST_INTERVAL 30000

void setup(void) {

  /* stores the output value of commands (passed by ref) */
  String output;

  /* Initialize hw serial port for debug */
  Serial.begin(SERIAL_BAUD_RATE);

  /* Initialize WifiSerial */
  WifiSerial::Initialize();

  /* Initialize Nokia LCD display */
  Display::Initialize();

  Display::ShowMessage(F("   #IoT ;-)   "), F("Hi! Welcome to the thing!"));
  Serial.println(F("Setup Begin!"));

  /* Initialize DHT11 sensor */
  DHTSensor::Initialize();

  /* Initialize ESP8266 device */
  WifiSerial::Initialize();

  Display::ShowMessage(F("   #IoT ;-)   "), F("Setup completed!"));
  Serial.println(F("Setup End!"));
  delay(500);

  /* we done here. */
}

void loop(void) {


  /* stores the output value of commands (passed by ref) */
  String output;

  if (DHTSensor::lastUpdate + SENSOR_POLL_INTERVAL <= millis()) {
    if (!DHTSensor::UpdateValues()) {
      Serial.println(F("Failed to read from DHT11"));
      Display::ShowMessage(F("  Error! ;-) "), F("Failed to read from DHT11"));
      delay(5000);
    };
    DHTSensor::lastUpdate = millis();
  }
  

  if (Display::lastUpdate + LCD_DISPLAY_INTERVAL <= millis()) {
    Display::TemperatureScreen();
    Display::lastUpdate = millis();
  }

  if (WifiSerial::lastUpdate + HTTP_POST_INTERVAL <= millis()) {
    Display::ShowMessage(F(" #IoT FTW ;-D "), F(""), false);
    if (WifiSerial::DoThingSpeakUpdate()) {
      Display::ShowMessage(F(" #IoT FTW :-) "), F(""), false);
    }
    WifiSerial::lastUpdate = millis();
  }

}
