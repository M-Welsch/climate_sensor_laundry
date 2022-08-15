#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "status.h"

void mqttSetup();
void sendToServer(const struct Status *status);
void reconnect();
void mqttPublish(char* buffer); 
void mqttGetIp(char* outstr);
void mqttLoop();