#include <Arduino.h>

#include <battery_monitor.h>

float BatteryMonitor::voltage() {
    int raw_value = analogRead(ANALOGPIN);
    return (float) raw_value;
}