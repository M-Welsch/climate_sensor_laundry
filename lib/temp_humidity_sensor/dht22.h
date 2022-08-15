#include "status.h"

#define DHT_INSIDE_PIN 5
#define DHT_OUTSIDE_PIN 6

typedef enum {
    dpSUCCESS, dpERROR
} dpError_e;

void dhtSetup();
dpError_e dhtGetValues(status_t *status);