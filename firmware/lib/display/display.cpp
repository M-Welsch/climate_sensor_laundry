#include <U8g2lib.h>

#include <Wire.h>
#include "display.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void Display::setup(void) {
    u8g2.begin();
}

void Display::waitForWifi(void) {
    Display::show_line("Waiting for Wifi ...", 0);   
}

void Display::u8g2_prepare(void) {
    u8g2.setFont(u8g2_font_6x10_tf);  // u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}

void Display::show_line(const char* const content, int line) {
    u8g2.drawStr(0, line*14, content);
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

void Display::show_status(const status_t *status) {
    char buffer[32];
    u8g2.clearBuffer();
    u8g2_prepare();
    static const char headline[] = "     Innen    Aussen";
    show_line(headline, 0);
    char minusSignInside = status->insideTemperature>0 ? ' ' : '-';
    char minusSignOutside = status->outsideTemperature>0 ? ' ' : '-';
    sprintf(buffer, "T   %c%4.1f %sC %c%4.1f %sC", minusSignInside, status->insideTemperature, "\xB0", minusSignOutside, status->outsideTemperature, "\xB0");
    show_line(buffer, 1);
    sprintf(buffer, "H    %4.1f %%   %4.1f %%", status->insideHumidity, status->outsideHumidity);
    show_line(buffer, 2);
    sprintf(buffer,"Tp  %4.1f %sC  %4.1f %sC", status->insideDewPoint, "\xB0", status->outsideDewPoint, "\xB0");
    show_line(buffer, 3);
    u8g2.sendBuffer();
}

void Display::off(void) {
    u8g2.clear();
    u8g2.setPowerSave(1);
    u8g2.sleepOn();
}

void Display::on(void) {
    u8g2.setPowerSave(0);
}