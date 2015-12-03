#include "DHTSensor.h"
#include "Display.h"

DHT DHTSensor::sensor = DHT(DHT_PIN_DATA, DHT_TYPE);

long DHTSensor::lastUpdate = 0;

float DHTSensor::humidityValue = 0;

float DHTSensor::temperatureValue = 0;
  
void DHTSensor::Initialize() {
  Display::ShowMessage(F("   #IoT ;-)   "), F("Initializing Sensor"));
  Serial.println(F("## Initializing Sensor..."));
  DHTSensor::sensor.begin();
}

bool DHTSensor::UpdateValues() {

  /*
      Reading temperature or humidity takes about 250 milliseconds!
      Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  */
  DHTSensor::humidityValue = DHTSensor::sensor.readHumidity();
  DHTSensor::temperatureValue = DHTSensor::sensor.readTemperature();

  if (isnan(DHTSensor::humidityValue) || isnan(DHTSensor::temperatureValue)) {
    return false;
  }

  return true;
  
}
