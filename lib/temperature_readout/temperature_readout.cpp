#include "MAX31855.h"
#include "temperature_readout.h"

#define nCS0 15

Temperature_Sensor::Temperature_Sensor(void) {
}

void Temperature_Sensor::setup() {
    cs = nCS0;
    MAX31855_Class sens;
    Serial.print(F("Initializing MAX31855 sensor\n"));
    pinMode(nCS0, OUTPUT);
    digitalWrite(nCS0, HIGH);
    sens.begin(nCS0);
}

float Temperature_Sensor::get_ambient_temperature_degrees() {
    digitalWrite(cs, LOW);
    int32_t temperature = sens.readAmbient();
    digitalWrite(cs, HIGH);
    return (float) temperature / 1000;
}

float Temperature_Sensor::get_probe_temperature_degrees() {
    digitalWrite(cs, LOW);
    int32_t temperature = sens.readProbe();
    digitalWrite(cs, HIGH);
    return (float) temperature / 1000;
}

Fault Temperature_Sensor::get_fault() {
    digitalWrite(cs, LOW);
    int fault_bits = (int) sens.fault();
    digitalWrite(cs, HIGH);
    Fault fault = static_cast<Fault>(fault_bits);
    return fault;
}