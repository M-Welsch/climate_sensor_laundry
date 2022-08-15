#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "display.h"
#include "temperature_sensor.h"
#include "battery_monitor.h"
// #include "web_server.h"
#include "logger.h"
// #include "mqtt.h"

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define topic "Backofen"

Display display;
Temperature_Sensor temperature_sensor;
BatteryMonitor battery_monitor;
// WebServer web_server;
Status status;
// Mqtt mqtt;
WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(void) {
  Serial.begin(9600);
  display.setup();
  temperature_sensor.setup();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void undervoltage_check(const float voltage) {
  if (battery_monitor.undervoltage(voltage)) {
    display.show_undervoltage(voltage);
    delay(3000);
    display.off();
    ESP.deepSleep(0);
  }
}


long lastMsg = 0;
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    status.ambient_temperature = temperature_sensor.get_ambient_temperature_degrees();
    status.probe_temperature = temperature_sensor.get_probe_temperature_degrees();
    status.battery_voltage = battery_monitor.voltage();

    undervoltage_check(status.battery_voltage);

    display.show_status(&status);
    log_to_console(&status);

    char buffer[128];
    sprintf(buffer, "{\"Ofentemperatur\": %.2f, \"Aussentemperatur\": %.2f, \"Batteriespannung\": %.2f}", status.ambient_temperature, status.ambient_temperature, status.battery_voltage);
    client.publish(topic, buffer, true);
  }
}

void loop_(void) {
  status.ambient_temperature = temperature_sensor.get_ambient_temperature_degrees();
  status.probe_temperature = temperature_sensor.get_probe_temperature_degrees();
  status.battery_voltage = battery_monitor.voltage();
  undervoltage_check(status.battery_voltage);
  // web_server.ip_address(status.ip_address);
  display.show_status(&status);
  log_to_console(&status);
  // web_server.handle_clients();
  delay(1000);
}
