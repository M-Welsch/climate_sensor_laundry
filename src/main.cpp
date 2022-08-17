#include <Arduino.h>
#include <string.h>
#include "DHTesp.h"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define topic "Waschhaus"


DHTesp dht;
DHTesp dht2;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);

  dht.setup(12, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
  dht2.setup(14, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  float humidity2 = dht2.getHumidity();
  float temperature2 = dht2.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(humidity2, 1);
  Serial.print("\t\t");
  Serial.print(temperature2, 1);
  Serial.print("\n");
  delay(2000);
}
