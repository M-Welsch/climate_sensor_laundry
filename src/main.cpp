#include <Arduino.h>
#include <Wire.h>
#include <string.h>
#include "display.h"
#include "temperature_readout.h"


Display display;
Temperature_Sensor temperature_sensor;

void setup(void) {
  Wire.begin();
  Serial.begin(9600);
  display.setup();
  temperature_sensor.setup();
}

void loop(void) {
  float temperature = temperature_sensor.get_probe_temperature_degrees();
  display.show_temperature(temperature);
  Serial.printf("Temperature %f\n", temperature);
  delay(1000);
}
