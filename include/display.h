#include <U8g2lib.h>

#include <Wire.h>


class Display {
    void u8g2_prepare(void);
    void draw_string(const char* const content);
  public:
    void setup(void);
    void show_temperature(const float temperature);
};
