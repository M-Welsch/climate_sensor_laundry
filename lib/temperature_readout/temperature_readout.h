#include "MAX31855.h"

/***************************************************************************************************
** Declare all program constants                                                                  **
***************************************************************************************************/
const uint32_t SERIAL_SPEED{115200};   ///< Set the baud rate for Serial I/O
const uint8_t  SPI_CHIP_SELECT{2};     ///< Chip-Select PIN for SPI
const uint8_t  SPI_MISO{MISO};         ///< Master-In, Slave-Out PIN for SPI
const uint8_t  SPI_SYSTEM_CLOCK{SCK};  ///< System Clock PIN for SPI

enum Fault {allright=0, no_probe=1, short_to_gnd=2, short_to_vcc=4};

class Temperature_Sensor {
        MAX31855_Class sens;
        uint8_t cs;
    public:
        Temperature_Sensor();
        void setup();
        float get_ambient_temperature_degrees();
        float get_probe_temperature_degrees();
        Fault get_fault();
};