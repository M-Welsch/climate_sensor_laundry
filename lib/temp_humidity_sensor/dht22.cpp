#include <cmath>

#include "DHTesp.h"

#include "dht22.h"

DHTesp dhtInside;
DHTesp dhtOutside;

#define MAGNUS_CONSTANT 6.1078f
#define PARAM_A_ABOVE_ZERO 7.5f
#define PARAM_A_BELOW_ZERO 7.6f
#define PARAM_B_ABOVE_ZERO 237.3f
#define PARAM_B_BELOW_ZERO 240.7f


void dhtSetup() {
    Serial.println("setting up dhts");
    dhtInside.setup(DHT_INSIDE_GPIO, DHTesp::DHT22);
    dhtOutside.setup(DHT_OUTSIDE_GPIO, DHTesp::DHT22);
    Serial.println("set up dhts");
}

static inline float _a(const float temperature) {
    return temperature > 0 ? PARAM_A_ABOVE_ZERO : PARAM_A_BELOW_ZERO;
}

static inline float _b(const float temperature) {
    return temperature > 0 ? PARAM_B_ABOVE_ZERO : PARAM_B_BELOW_ZERO;
}

static float _magnusFormula(const float temperature) {
    float a = _a(temperature);
    float b = _b(temperature);
    float exponent = (a * temperature) / (b + temperature);
    return pow(MAGNUS_CONSTANT, exponent);
}

float dewPoint(const float temperature, const float humidity) {
    float magnus = _magnusFormula(temperature);
    float numerator = _b(temperature) * log10((magnus * humidity/100) / MAGNUS_CONSTANT);
    float denominator = _a(temperature) * log10((magnus * humidity/100) / MAGNUS_CONSTANT);
    return numerator/denominator;
}

dpError_e dhtGetValues(status_t *status) {
    delay(dhtInside.getMinimumSamplingPeriod());
    status->insideTemperature = dhtInside.getTemperature();
    status->insideHumidity = dhtInside.getHumidity();
    status->outsideTemperature = dhtOutside.getTemperature();
    status->outsideHumidity = dhtOutside.getHumidity();
    return dpSUCCESS;
}