#include <U8g2lib.h>

#include <Wire.h>
#include "display.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void Display::setup(void) {
    u8g2.begin();
}

void Display::u8g2_prepare(void) {
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}

void Display::draw_string(const char* const content) {
    u8g2.clearBuffer();
    u8g2_prepare();
    u8g2.drawStr(0,0, content);
    u8g2.sendBuffer();
}

void Display::show_temperature(const float temperature) {
    char buffer[32];
    sprintf(buffer, "Temperatur: %.1f %sC", temperature, "\xB0");
    Display::draw_string(buffer);
}