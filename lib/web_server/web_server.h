#include <ESP8266WebServer.h>


class WebServer {
        //ESP8266WebServer server;
        const char* ssid = "WERKSTATT_WLAN";
        const char* password = "XL12ABZXYGKIDO";
        char *_ip_address;
    public:
        //void handle_root(void);
        void handle_clients(void);
        void setup(void);
        void connect(void);
        bool connected(void);
        void ip_address(char *buffer);
};