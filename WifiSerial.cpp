#include "WifiSerial.h"
#include "secrets.h"
#include "Display.h"
#include "DHTSensor.h"

SoftwareSerial WifiSerial::serial = SoftwareSerial(ESP8266_PIN_RX, ESP8266_PIN_TX);

long WifiSerial::lastUpdate = 0;

void WifiSerial::Initialize() {
  String output;

  /* Initialize software serial port to talk with the ESP8266 */
  WifiSerial::serial.begin(SOFTSERIAL_BAUD_RATE);

  /* Initialize the Arduino pin that will control the ESP8266 on/off state */
  pinMode(ESP8266_PIN_CHPD, OUTPUT);

  Display::ShowMessage(F("   #IoT ;-)   "), F("Initializing Wifi Serial"));
  do {
    Serial.println(F("## Initializing WiFi Serial..."));
  } while (!WifiSerial::HardReset());
  WifiSerial::FlushSerialBuffer();

  /* Wait for a positive "AT" test command reponse */
  Display::ShowMessage(F("   #IoT ;-)   "), F("Setting up WiFi..."));
  do {
    Serial.println(F("## Setting up WiFi..."));
  }
  while (!WifiSerial::SendCommand(F("AT"), F("OK"), output));

  /* Set ESP8266's operation mode to station (client) */
  if (SETUP_WLAN) {
    Serial.println(F("## Setting up WLAN..."));
    Display::ShowMessage(F("   #IoT ;-)   "), F("Setting up WLAN..."));
    WifiSerial::SendCommand(F("AT+CWMODE=1"), output);

    WifiSerial::SendCommand(F("AT+RST"), F("System Ready"), output);

    /* Connect ESP8266 to the wlan network specified in secrets.h */
    WifiSerial::SendCommand(String(F("AT+CWJAP=\"")) +
                String(S_WLAN_SSID) +
                String(F("\",\"")) +
                String(S_WLAN_PASSWORD) +
                String(F("\"")), F("OK"), output);
  }

  /* Get some debug output (device's IP address) */
  Display::ShowMessage(F("   #IoT ;-)   "), F("Getting connection status..."));
  do {
    Serial.println(F("## Getting connection status..."));
  } while (!WifiSerial::SendCommand(F("AT+CIFSR"), F("OK"), output));
}

/* Reset the device by turning it off and on again via the CH_PD pin.
   Returns a logic value indicating wether the acknowlegement string
   was indeed received. */
bool WifiSerial::HardReset() {

  String temp;

  WifiSerial::FlushSerialBuffer();

  digitalWrite(ESP8266_PIN_CHPD, LOW);
  delay(100);
  digitalWrite(ESP8266_PIN_CHPD, HIGH);
  delay(1000);

  while (WifiSerial::serial.available() > 0) {
    char c = WifiSerial::serial.read();
    temp += c;
    if (temp.indexOf(F("System Ready")) > -1) {
      return true;
    }
  }

  return false;

}

/* Send command 'cmd'. Wait until confirmation message 'ack' is received
   or until timeout occurs, then set 'output' as the data it received.
   If 'cmd' is empty string no command is sent. */
bool WifiSerial::SendCommand(String cmd, String ack, String& output) {

  Serial.print(F("## CMD="));
  Serial.println(cmd);
  Serial.print(F("## ACK="));
  Serial.println(ack);
    
  output = F("");
  String temp;

  if (cmd != "") {
    WifiSerial::serial.print(cmd);
    WifiSerial::serial.print(SOFTSERIAL_LINE_ENDING);
  }

  char c;
  bool skippedCommandEcho = false;
  long timeout = millis() + TIMEOUT;

  while (millis() < timeout) {

    if (WifiSerial::serial.available() > 0) {

      c = WifiSerial::serial.read();
      temp += c;

      if (temp.indexOf(cmd) > -1 && !skippedCommandEcho) {
        temp = "";
        skippedCommandEcho = true;
      }

      if (ack != F("") && temp.indexOf(ack) > -1) {
        temp.trim();
        output = temp;
        
        Serial.println(output);
        Serial.println(F("## ACK!!"));
        return true;
      }
    }

  }

  temp.trim();
  output = temp;

  Serial.println(output);
  Serial.println(F("## TIMEOUT!!"));
  
  return false;

}

/* Send command 'cmd'. Wait until timeout occurs then set 'output' to
   the data it received . */
void WifiSerial::SendCommand(String cmd, String& output) {
  WifiSerial::SendCommand(cmd, F(""), output);
}

/* Waits for the acknowledge string 'ack'. */
void WifiSerial::WaitAckString(String ack, String& output) {
  WifiSerial::SendCommand(F(""), ack, output);
}

/* Flushes serial buffer (discards data) */
void WifiSerial::FlushSerialBuffer() {

  while (WifiSerial::serial.available() > 0) {
    WifiSerial::serial.read();
  }

}

/* Flushes software serial buffer (outputs to hw serial) */
void WifiSerial::DumpSerialBuffer() {

  while (WifiSerial::serial.available() > 0) {
    Serial.write(WifiSerial::serial.read());
  }

}


bool WifiSerial::DoThingSpeakUpdate() {

  bool returnValue = false;

  /* stores the output value of commands (passed by ref) */
  String output;

  /*
     Build HTTP request buffer
  */
  String message = String("") + F("field1=") + String(DHTSensor::humidityValue) + F("&field2=") + String(DHTSensor::temperatureValue);
  String request = "";
  request += F("POST /update HTTP/1.1\n");
  request += F("Host: api.thingspeak.com\n");
  request += F("Connection: close\n");
  request += F("X-ThingSpeakAPIKey: ");
  request += F(S_THINGSPEAK_API_KEY);
  request += F("\n");
  request += F("Content-Type: application/x-www-form-urlencoded\n");
  request += F("Content-Length: ");
  request += String(message.length());
  request += F("\n");
  request += F("\n");
  request += message;
  request += F("\n");

  /* Establish TCP connection */
  bool linked;
  do {
    Serial.println(F("## Establishing connection..."));
    linked = WifiSerial::SendCommand(F("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80"), F("Linked"), output);
  } while (!linked);

  /* Enters transmission mode */
  returnValue = WifiSerial::SendCommand(String("") + F("AT+CIPSEND=") + String(request.length()), F(">"), output);
  delay(500);
  
  /* Sends data */
  returnValue = returnValue && WifiSerial::SendCommand(request, F("SEND OK"), output);
  delay(500);

  /* Closes TCP connection */
  returnValue = returnValue && WifiSerial::SendCommand(F("AT+CIPCLOSE"), F("Unlink"), output);

  return returnValue;

}

