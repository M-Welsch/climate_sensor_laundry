#include <Arduino.h>
#include <Wire.h>
#include <string.h>
#include "display.h"
#include "temperature_sensor.h"
#include "battery_monitor.h"
#include "web_server.h"

Display display;
Temperature_Sensor temperature_sensor;
BatteryMonitor battery_monitor;
WebServer web_server;
Status status;

void setup(void) {
  Wire.begin();
  Serial.begin(9600);
  display.setup();
  temperature_sensor.setup();
  web_server.setup(&status);
}

void loop(void) {
  status.ambient_temperature = temperature_sensor.get_ambient_temperature_degrees();
  status.probe_temperature = temperature_sensor.get_probe_temperature_degrees();
  status.battery_voltage = battery_monitor.voltage();
  web_server.ip_address(status.ip_address);
  display.show_status(&status);
  Serial.printf("Temperature %f\n", status.probe_temperature);
  web_server.handle_clients();
  delay(1000);
}
