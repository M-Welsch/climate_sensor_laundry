#include <U8g2lib.h>

#include <Wire.h>


class Display {
    void u8g2_prepare(void);
  public:
    void setup(void);
    void draw_string(const char* const content);
};
