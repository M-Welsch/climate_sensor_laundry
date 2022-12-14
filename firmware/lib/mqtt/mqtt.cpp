#include <ArduinoJson.h>
#include "mqtt.h"

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define mqtt_topic "Waschkueche"

WiFiClient espClient;
PubSubClient client(espClient);

typedef enum {rjPASS, rjFAIL} rjError_e;

float outsideTemperature = 0;
float outsideHumidity = 0;

/**
 * @brief strip the string after the closing bracket '}' 
 * 
 * @param[in/out] json 
 */
rjError_e repairJson(char* json, uint32_t maxlen) {
  uint8_t bracketCount = 0;
  for (uint32_t ptr = 0; ptr < maxlen; ptr++) {
    if(*(json+ptr) == '{') {
      bracketCount++;
    }
    if(*(json+ptr) == '}') {
      bracketCount--;
      if (bracketCount  == 0) {
        *(json+ptr+1) = '\0';
        return rjPASS;
      }
    }
  }
  return rjFAIL;
}

void callback(char* topic, byte* payload_raw, unsigned int length) {
  char *payload = (char*) payload_raw;
  repairJson(payload, (uint32_t) length);
  
  const int capacity = JSON_OBJECT_SIZE(5);
  StaticJsonDocument<capacity> values;

  DeserializationError err = deserializeJson(values, payload);
  if (err) {
    return;
  }
  outsideTemperature = values["outsideTemperature"];
  outsideHumidity = values["outsideHumidity"];

  Serial.printf("Received Message from topic %s, payload: %s. Temperature = %.2f, Humidity = %.2f\n", topic, payload, outsideTemperature, outsideHumidity);
}

void getOutsideValues(status_t* status) {
  status->outsideHumidity = outsideHumidity;
  status->outsideTemperature = outsideTemperature;
}

void mqttSetup() {
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  client.loop();
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      client.subscribe("aussenKlimaSensor");
      client.setCallback(callback);
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttPublishStatus(status_t *status) {
  static const int capacity = JSON_OBJECT_SIZE(3);
  StaticJsonDocument<capacity> json;

  json["WaschkuecheTemperaturInnen"] = status->insideTemperature;
  json["WaschkuecheLuftfeuchtigkeitInnen"] = status->insideHumidity;
  json["WaschkuecheTaupunktInnen"] = status->insideDewPoint;

  char serializedJson[2048];
  serializeJson(json, serializedJson);
  client.publish(mqtt_topic, serializedJson, true);
}