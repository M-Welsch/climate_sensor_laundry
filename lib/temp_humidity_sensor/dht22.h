#include "status.h"

#define DHT_INSIDE_GPIO 12
#define DHT_OUTSIDE_GPIO 14

typedef enum {
    dpSUCCESS, dpERROR
} dpError_e;

void dhtSetup();
dpError_e dhtGetValues(status_t *status);