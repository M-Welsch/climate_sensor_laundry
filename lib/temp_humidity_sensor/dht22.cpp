#include "DHT.h"

#include "dht22.h"

DHT dhtInside;
DHT dhtOutside;

void dhtSetup() {
    Serial.println("setting up dhts");
    dhtInside.setup(DHT_INSIDE_PIN);
    dhtOutside.setup(DHT_OUTSIDE_PIN);
    Serial.println("set up dhts");
}

dpError_e dhtGetValues(status_t *status) {
    status->insideTemperature = dhtInside.getTemperature();
    status->insideHumidity = dhtInside.getHumidity();
    status->outsideTemperature = dhtOutside.getTemperature();
    status->outsideHumidity = dhtOutside.getHumidity();
    return dpSUCCESS;
}