#include "web_server.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <string.h>


void WebServer::setup(void) {
    ESP8266WebServer server(80);
    WiFi.begin(ssid, password);
}

void WebServer::connect(void) {
    while(!connected()) {
        delay(500);
        Serial.println("Waiting to connect...");
    }
}

bool WebServer::connected(void) {
    return WiFi.status() == WL_CONNECTED;
}

void WebServer::ip_address(char *buffer) {
    if (connected()) {
        String ip = WiFi.localIP().toString();
        ip.toCharArray(buffer, 32);
    }
    else {
        sprintf(buffer, "No Wifi");
    }
}