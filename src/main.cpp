#include <Arduino.h>
#include <string.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "display.h"
#include "dht22.h"
#include "status.h"
#include "button.h"
#include "led.h"

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define topic "Waschhaus"
#define BUTTON_GPIO 13

status_t status;
Display display;
Button button;

void setup()
{
  Serial.begin(115200);
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  dhtSetup();
  display.setup();
  button.setup(BUTTON_GPIO);
}

void loop()
{
  dhtGetValues(&status);
  display.show_status(&status);
  Serial.printf("Ti: %.1f, To: %.1f\n", status.insideTemperature, status.outsideTemperature);
  Serial.printf("button pressed: %i\n", button.pressed());
  delay(100);
}
