#include "Routine.h"
#include "GFX.h"
#include "Display.h"
#include "WifiSerial.h"
#include "DHTSensor.h"

void (*Routine::Buttons)() = Buttons::Read;

uint16_t Routine::sleep;

uint16_t Routine::pause;

void Routine::Initialize() {

}

void Routine::Nop() {
    
}

void Routine::Sleep() {
  if (Routine::sleep > 0) {
    delay(Routine::sleep); 
  }
}


void Routine::DHTSensor() {

  if (DHTSensor::lastUpdate + SENSOR_POLL_INTERVAL <= millis()) {
    if (!DHTSensor::UpdateValues()) {
      Serial.println(F("Failed to read from DHT11"));
      Display::ShowMessage(F("  Error! ;-) "), F("Failed to read from DHT11"));
      delay(5000);
    };

    DHTSensor::lastUpdate = millis();
  }

}

void Routine::Display() {

  if (Display::lastUpdate + LCD_DISPLAY_INTERVAL <= millis()) {
    Display::TemperatureScreen();
    Display::lastUpdate = millis();
  }


}

void Routine::WifiSerial() {

  if (WifiSerial::lastUpdate + HTTP_POST_INTERVAL <= millis()) {
    Display::ShowMessage(F(" #IoT FTW ;-D "), F(""), false);
    if (WifiSerial::DoThingSpeakUpdate()) {
      Display::ShowMessage(F(" #IoT FTW :-) "), F(""), false);
    }
    WifiSerial::lastUpdate = millis();
  }

}
