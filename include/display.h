#include <U8g2lib.h>
#include <string.h>

#include <Wire.h>

struct Status {
  float probe_temperature;
  float ambient_temperature;
  float battery_voltage;
  float battery_soc;
};

class Display {
    void u8g2_prepare(void);
    void draw_string(const char* const content, int line);
  public:
    void setup(void);
    void show_temperature(const float temperature);
    void show_battery_status(const float voltage);
    void show_status(const struct Status *status);
};
