#include <Arduino.h>
#include <string.h>
#include "display.h"
#include "temperature_sensor.h"
#include "battery_monitor.h"
#include "web_server.h"
#include "logger.h"

Display display;
Temperature_Sensor temperature_sensor;
BatteryMonitor battery_monitor;
WebServer web_server;
Status status;

void setup(void) {
  Serial.begin(9600);
  display.setup();
  temperature_sensor.setup();
  web_server.setup(&status);
}

void undervoltage_check(const float voltage) {
  if (battery_monitor.undervoltage(voltage)) {
    display.show_undervoltage(voltage);
    delay(3000);
    display.off();
    ESP.deepSleep(0);
  }
}

void loop(void) {
  status.ambient_temperature = temperature_sensor.get_ambient_temperature_degrees();
  status.probe_temperature = temperature_sensor.get_probe_temperature_degrees();
  status.battery_voltage = battery_monitor.voltage();
  undervoltage_check(status.battery_voltage);
  web_server.ip_address(status.ip_address);
  display.show_status(&status);
  log_to_console(&status);
  web_server.handle_clients();
  delay(1000);
}
