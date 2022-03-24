#include <Arduino.h>
#include "status.h"

void log_to_console(Status *status) {
    Serial.printf("T(Ofen)= %.1f°C, T(Umgebung)= %.1f°C, V(batt)=%.2f, IP: %s\n", status->probe_temperature, status->ambient_temperature, status->battery_voltage, status->ip_address);
}