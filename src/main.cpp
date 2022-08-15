#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "display.h"
#include "temperature_sensor.h"
#include "battery_monitor.h"
#include "logger.h"
#include "mqtt.h"

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define topic "Backofen"

Display display;
Temperature_Sensor temperature_sensor;
BatteryMonitor battery_monitor;
Status status;

void setup(void) {
  Serial.begin(9600);
  display.setup();
  temperature_sensor.setup();
  mqttSetup();
}

void undervoltage_check(const float voltage) {
  if (battery_monitor.undervoltage(voltage)) {
    display.show_undervoltage(voltage);
    delay(3000);
    display.off();
    ESP.deepSleep(0);
  }
}

long lastMsg = 0;
void loop() {
  reconnect();
  mqttLoop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    status.ambient_temperature = temperature_sensor.get_ambient_temperature_degrees();
    status.probe_temperature = temperature_sensor.get_probe_temperature_degrees();
    status.battery_voltage = battery_monitor.voltage();

    undervoltage_check(status.battery_voltage);

    display.show_status(&status);
    log_to_console(&status);

    char buffer[128];
    sprintf(buffer, "{\"Ofentemperatur\": %.2f, \"Aussentemperatur\": %.2f, \"Batteriespannung\": %.2f}", status.ambient_temperature, status.ambient_temperature, status.battery_voltage);
    mqttPublish(buffer);
  }
}