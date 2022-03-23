#include <Arduino.h>
#include <Wire.h>
#include <string.h>
#include "display.h"
#include "temperature_sensor.h"
#include "battery_monitor.h"

Display display;
Temperature_Sensor temperature_sensor;
BatteryMonitor battery_monitor;
Status status;

void setup(void) {
  Wire.begin();
  Serial.begin(9600);
  display.setup();
  temperature_sensor.setup();
}

void loop(void) {
  status.ambient_temperature = temperature_sensor.get_ambient_temperature_degrees();
  status.probe_temperature = temperature_sensor.get_probe_temperature_degrees();
  status.battery_voltage = battery_monitor.voltage();
  sprintf(status.ip_address, "192.168.0.34");
  display.show_status(&status);
  Serial.printf("Temperature %f\n", status.probe_temperature);
  delay(1000);
}
