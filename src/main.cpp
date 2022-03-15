#include <Arduino.h>
#include <string.h>
#include "display.h"

Display display;

void setup(void) {
    display.setup();
}

void loop(void) {
  float temperature = 21.123;
  display.show_temperature(temperature);
}
