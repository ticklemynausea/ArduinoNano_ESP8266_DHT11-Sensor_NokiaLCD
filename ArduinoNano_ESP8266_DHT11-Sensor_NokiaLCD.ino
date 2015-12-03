/*
   DHT11 Temperature/Humidity Sensor in the IoT
   Arduino Nano + ESP8266 Serial2Wifi

   https://thingspeak.com/channels/56753

*/

#include "Display.h"
#include "WifiSerial.h"
#include "DHTSensor.h"
#include "Routine.h"

/* Baud rate for the hardware serial */
#define SERIAL_BAUD_RATE 115200

void setup(void) {

  /* stores the output value of commands (passed by ref) */
  String output;

  /* Initialize hw serial port for debug */
  Serial.begin(SERIAL_BAUD_RATE);

  /* Initialize WifiSerial */
  WifiSerial::Initialize();

  /* Initialize Nokia LCD display */
  Display::Initialize();

  /* Initialize DHT11 sensor */
  DHTSensor::Initialize();

  /* Initialize ESP8266 device */
  WifiSerial::Initialize();

  /* Initialize buttons */
  Buttons::Initialize();

  /* Completed message */
  Display::ShowMessage(F("   #IoT ;-)   "), F("Setup completed!"));
  Serial.println(F("Setup End!"));
  delay(500);

  /* we done here. */
}

void loop(void) {

  Routine::DHTSensor();
  
  Routine::Display();

  Routine::WifiSerial();
  
  //Routine::Buttons();

}
