#ifndef _wifiserial_h_
#define _wifiserial_h_

#include <SoftwareSerial.h>

/* ESP8266 pins connection to the arduino () */
#define ESP8266_PIN_CHPD 4
#define ESP8266_PIN_RX 3
#define ESP8266_PIN_TX 2

/* Baud rate and line terminations used in the software serial communication
   These will depend on your specific AT firmware */
#define SOFTSERIAL_BAUD_RATE 9600
#define SOFTSERIAL_LINE_ENDING F("\r\n")

/* Max wait time in milliseconds sendCommand will wait for a command's response */
#define TIMEOUT 5000

/* Should the program try to setup the WLAN conection (dhcp, etc) upon starting? */
#define SETUP_WLAN false

class WifiSerial {
  
  public:
  /* Software serial port for talking to the ESP8266 */
  static SoftwareSerial serial;

  static long lastUpdate;

  static void Initialize();
  static bool HardReset();
  static void SendCommand(String cmd, String& output);
  static bool SendCommand(String cmd, String ack, String& output);
  static void FlushSerialBuffer();
  static void DumpSerialBuffer();
  static bool DoThingSpeakUpdate();

};

#endif //_wifiserial_h_
