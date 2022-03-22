#include <U8g2lib.h>

#include <Wire.h>
#include "display.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void Display::setup(void) {
    u8g2.begin();
}

void Display::u8g2_prepare(void) {
    u8g2.setFont(u8g2_font_7x14_tf);  // u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}

void Display::draw_string(const char* const content, int line) {
    u8g2.clearBuffer();
    u8g2_prepare();
    u8g2.drawStr(0, line, content);
    u8g2.sendBuffer();
}

void Display::show_temperature(const float temperature) {
    char buffer[32];
    sprintf(buffer, "Temp: %.1f %sC", temperature, "\xB0");
    Display::draw_string(buffer, 0);
}

void Display::show_battery_status(const float voltage) {
    char buffer[32];
    sprintf(buffer, "VBATT: %.1f %sC", voltage, "V");
    Display::draw_string(buffer, 10);
}

void Display::show_status(const struct Status *status) {
    char buffer[32];
    u8g2.clearBuffer();
    u8g2_prepare();
    sprintf(buffer, "Temp: %.1f %sC", status->probe_temperature, "\xB0");
    u8g2.drawStr(0, 0, buffer);
    sprintf(buffer, "VBATT: %.1f V", status->battery_voltage);
    u8g2.drawStr(0, 16, buffer);
    u8g2.sendBuffer();
}
