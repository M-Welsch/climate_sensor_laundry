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

void Display::show_line(const char* const content, int line) {
    u8g2.drawStr(0, line*16, content);
}

void Display::show_temperature(const float temperature) {
    char buffer[32];
    sprintf(buffer, "Temp: %.1f %sC", temperature, "\xB0");
    Display::show_line(buffer, 0);
}

void Display::show_battery_status(const float voltage) {
    char buffer[32];
    sprintf(buffer, "VBATT: %.1f %sC", voltage, "V");
    Display::show_line(buffer, 10);
}

void Display::show_status(const struct Status *status) {
    char buffer[32];
    u8g2.clearBuffer();
    u8g2_prepare();
    sprintf(buffer, "T(Ofen): %.1f %sC", status->probe_temperature, "\xB0");
    show_line(buffer, 0);
    sprintf(buffer, "T(Umgebung): %.1f %sC", status->ambient_temperature, "\xB0");
    show_line(buffer, 1);
    sprintf(buffer, "VBATT: %.2f V", status->battery_voltage);
    show_line(buffer, 2);
    sprintf(buffer, "IP: %s", status->ip_address);
    show_line(buffer, 3);
    u8g2.sendBuffer();
}


void Display::show_undervoltage(const float voltage) {
    char buffer[32];
    u8g2.clearBuffer();
    u8g2_prepare();
    sprintf(buffer, "VBATT: %.1f %sC", voltage, "V");
    show_line(buffer, 0);
    show_line("! Undervoltage !", 1);
    show_line("Going to sleep!", 3);
    u8g2.sendBuffer();
}

void Display::off(void) {
    u8g2.clear();
    u8g2.setPowerSave(1);
    u8g2.sleepOn();
}