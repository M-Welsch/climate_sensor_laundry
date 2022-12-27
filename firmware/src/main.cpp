#include <Arduino.h>
#include <string.h>

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

#include "display.h"
#include "dht22.h"
#include "status.h"
#include "button.h"
#include "led.h"
#include "mqtt.h"

#define WIFI_HOTSPOT_NAME "Taupunktsensor"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define BUTTON_GPIO 13
#define LED_GREEN_GPIO 15

status_t status;
Display display;
Button button;
Led ledGreen;
Dht dht;

void wifiConnection() {
  WiFiManager wifiManager;
  if (button.pressed()) {
    Serial.println("resetting wifi credentials ...");
    wifiManager.resetSettings();
    wifiManager.startConfigPortal(WIFI_HOTSPOT_NAME);
  }
  else {
    wifiManager.autoConnect(WIFI_HOTSPOT_NAME);
  }
}

typedef enum {displayOn, displayOff} displayState_e;
volatile displayState_e displayState;
volatile uint16_t displayCounter = 0;

void ICACHE_RAM_ATTR ISR() {
  Serial.println("Pressed!");
  displayCounter = 0;
  displayState = displayOn;
}

void setup()
{
  displayState = displayOn;
  Serial.begin(115200);
  dht.setup();
  display.setup();
  ledGreen.setup(LED_GREEN_GPIO);
  button.setup(BUTTON_GPIO);
  attachInterrupt(BUTTON_GPIO, ISR, FALLING);
  wifiConnection();
  mqttSetup();
}

uint16_t lastMsg = 0;
void loop()
{
  reconnect();

  uint16_t now = millis();
  if (now-lastMsg > 1000) {
    dht.getValues(&status);
    getOutsideValues(&status);
    Serial.printf("Ti: %.1f, To: %.1f\n", status.insideTemperature, status.outsideTemperature);
    
    char buffer[256];
    sprintf(buffer, "{\"WaschkuecheTemperaturInnen\": %.2f, \"WaschkuecheLuftfeuchtigkeitInnen\": %.2f, \"WaschkuecheTaupunktInnen\": %.2f, \"WaschkuecheTemperaturAussen\": %.2f, \"WaschkuecheLuftfeuchtigkeitAussen\": %.2f, \"WaschkuecheTaupunktAussen\": %.2f}", status.insideTemperature, status.insideHumidity, status.insideDewPoint, status.outsideTemperature, status.outsideHumidity, status.outsideDewPoint);
    mqttPublish(buffer);
    //mqttPublishStatus(&status);
    if (status.insideDewPoint < status.outsideDewPoint) {
      ledGreen.on();
    }
    else {
      ledGreen.off();
    }
    delay(100);
  }

  static bool displayOnTriggered = false;
  if (displayState == displayOn) {
    if (!displayOnTriggered) {
      display.on();
      displayOnTriggered = true;
    }
    display.show_status(&status);
    displayCounter++;
    Serial.printf("displaycounter: %i\n", displayCounter);
    if (displayCounter > 12) {
      displayState = displayOff;
      display.off();
      displayOnTriggered = false;
    }
  }
}
