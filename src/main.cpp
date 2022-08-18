#include <Arduino.h>
#include <string.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "display.h"
#include "dht22.h"
#include "status.h"
#include "button.h"
#include "led.h"
#include "mqtt.h"

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define topic "Waschkueche"
#define BUTTON_GPIO 13

status_t status;
Display display;
Button button;

void setup()
{
  Serial.begin(115200);
  dhtSetup();
  display.setup();
  button.setup(BUTTON_GPIO);
  mqttSetup();
}

uint16_t lastMsg = 0;
void loop()
{
  reconnect();
  mqttLoop();

  uint16_t now = millis();
  if (now-lastMsg > 1000) {
    dhtGetValues(&status);
    display.show_status(&status);
    Serial.printf("Ti: %.1f, To: %.1f\n", status.insideTemperature, status.outsideTemperature);
    Serial.printf("button pressed: %i\n", button.pressed());
    
    char buffer[256];
    sprintf(buffer, "{\"TemperaturInnen\": %.2f, \"LuftfeuchtigkeitInnen\": %.2f, \"TemperaturAussen\": %.2f, \"LuftfeuchtigkeitAussen\": %.2f}", status.insideTemperature, status.insideHumidity, status.outsideTemperature, status.outsideHumidity);
    mqttPublish(buffer);
    delay(100);
  }
}
