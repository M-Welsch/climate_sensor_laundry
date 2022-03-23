#include "web_server.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <string.h>


ESP8266WebServer server(80);

void handle_root(void) {
    server.send(200, "text/html", "Blabla");
}

void WebServer::handle_clients(void) {
    server.handleClient();
}

void WebServer::setup(void) {
    WiFi.begin(ssid, password);
    connect();
    server.on("/", handle_root);
    server.begin();
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