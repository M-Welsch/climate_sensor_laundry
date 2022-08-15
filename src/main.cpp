#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "display.h"
#include "dht22.h"
#include "battery_monitor.h"
#include "logger.h"
#include "mqtt.h"

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define topic "Waschhaus"

Display display;
status_t status;

void setup(void) {
  Serial.begin(9600);
  mqttSetup();
  //dhtSetup();
  //display.setup();
}

long lastMsg = 0;
void loop() {
  Serial.println("Loop");
  reconnect();
  mqttLoop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;

    //dhtGetValues(&status);
    //display.show_status(&status);
    log_to_console(&status);
    status.insideTemperature = 4;
    status.outsideTemperature = 12;
    char buffer[128];
    sprintf(buffer, "{\"Keller Innentemperatur\": %.2f, \"Keller Aussentemperatur\": %.2f}", status.insideTemperature, status.outsideTemperature);
    mqttPublish(buffer);
  }
}