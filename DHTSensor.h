#ifndef _dhtsensor_h_
#define _dhtsensor_h_

#include <DHT.h>

/* Arduino pin where the DHT sensor data pin is connected to*/
#define DHT_PIN_DATA 10

/* DHT Sensor Type */
#define DHT_TYPE DHT11

class DHTSensor {

  public:
  static DHT sensor;

  static long lastUpdate;
  
  static float humidityValue;
  static float temperatureValue;

  static void Initialize();
  static bool UpdateValues();
  
    
};

#endif //_dhtsensor_h_
