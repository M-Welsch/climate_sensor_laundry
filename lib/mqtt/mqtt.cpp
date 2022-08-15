#include "mqtt.h"

#define wifi_ssid "NETGEAR"
#define wifi_password "XL12ABZXYGKIDO"

#define mqtt_server "192.168.0.2"
#define mqtt_user "iot"
#define mqtt_password "test123"

#define topic "Backofen"

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

void mqttSetup() {
    setup_wifi();
    client.setServer(mqtt_server, 1883);   
}

void reconnect() {
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

void mqttPublish(char* buffer) {
    client.publish(topic, buffer, true);
}

void mqttLoop() {
    client.loop();
}






typedef enum {bsSUCCESS, bsERROR} bsError;

bsError wrapIntoJson(char* outstr, const char* instr) {
    if (instr==NULL || outstr==NULL) {
        return bsERROR;
    }
    sprintf(outstr, "{%s}", instr);
    return bsSUCCESS;
}

bsError jsonLine(char* outstr, const char* identifier, const float value, const bool lastLine) {
    if (identifier==NULL || outstr == NULL) {
        return bsERROR;
    }

    if (lastLine) {
        sprintf(outstr, "\"%s\": %f", identifier, value);
    } else {
        sprintf(outstr, "\"%s\": %f,", identifier, value);
    }
    return bsSUCCESS;
}

// void sendToServer(const struct Status *status) {
//     connect();
//     char dataDictBuffer[256];
//     jsonLine(dataDictBuffer, "Ofentemperatur", status->probe_temperature, false);
//     jsonLine(dataDictBuffer, "Aussentemperatur", status->ambient_temperature, false);
//     jsonLine(dataDictBuffer, "Batteriespannung", status->battery_voltage, true);

//     char dataDict[256];
//     wrapIntoJson(dataDict, dataDictBuffer);
//     mqttClient.publish(mqtt_topic, dataDict, true);
// }