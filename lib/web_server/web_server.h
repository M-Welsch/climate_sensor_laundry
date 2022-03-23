#ifndef _web_server_h_
#define _web_server_h_

#include <ESP8266WebServer.h>
#include "status.h"

class WebServer {
        const char* ssid = "WERKSTATT_WLAN";
        const char* password = "XL12ABZXYGKIDO";
        char *_ip_address;
    public:
        void handle_clients(void);
        void setup(Status *main_status);
        void connect(void);
        bool connected(void);
        void ip_address(char *buffer);
};

#endif