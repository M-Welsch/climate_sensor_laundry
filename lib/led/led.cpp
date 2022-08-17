#include <Arduino.h>

#include "led.h"

void Led::setup(uint8_t gpio_pin) {
  ledPin = gpio_pin;
  pinMode(ledPin, OUTPUT);
}

void Led::on() {
  digitalWrite(ledPin, HIGH);
}

void Led::off() {
  digitalWrite(ledPin, LOW);
}
