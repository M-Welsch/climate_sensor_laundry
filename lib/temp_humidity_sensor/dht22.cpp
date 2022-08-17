#include "DHTesp.h"

#include "dht22.h"

DHTesp dhtInside;
DHTesp dhtOutside;

void dhtSetup() {
    Serial.println("setting up dhts");
    dhtInside.setup(DHT_INSIDE_GPIO, DHTesp::DHT22);
    dhtOutside.setup(DHT_OUTSIDE_GPIO, DHTesp::DHT22);
    Serial.println("set up dhts");
}

dpError_e dhtGetValues(status_t *status) {
    delay(dhtInside.getMinimumSamplingPeriod());
    status->insideTemperature = dhtInside.getTemperature();
    status->insideHumidity = dhtInside.getHumidity();
    status->outsideTemperature = dhtOutside.getTemperature();
    status->outsideHumidity = dhtOutside.getHumidity();
    return dpSUCCESS;
}