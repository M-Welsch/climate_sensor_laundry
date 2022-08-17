#include <Arduino.h>
#include <string.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "dht22.h"
#include "status.h"

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define topic "Waschhaus"

status_t status;

void setup()
{
  Serial.begin(115200);
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  dhtSetup();

}

void loop()
{
  dhtGetValues(&status);
  Serial.printf("Ti: %.1f, To: %.1f\n", status.insideTemperature, status.outsideTemperature);
  delay(1000);
}
