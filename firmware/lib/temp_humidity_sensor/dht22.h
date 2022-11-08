#include "status.h"
#include "DHTesp.h"

#define DHT_INSIDE_GPIO 12
#define DHT_OUTSIDE_GPIO 14

typedef enum {
    dpSUCCESS, dpERROR
} dpError_e;

class Dht {
        DHTesp dhtInside;
        DHTesp dhtOutside;
    public:
        void setup();
        dpError_e getValues(status_t *status);
};