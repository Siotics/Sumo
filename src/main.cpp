#include <config.h>
#include <Arduino.h>
#include <DNS.h>
#include <WebServer.h>
#include <WifiAP.h>

void setup() {
  Serial.begin(115200);

  WifiAP::initialize(WIFI_AP_SSID_PREFIX, WIFI_AP_PASSWORD);
  DNS::initialize();
  WebServer::initialize();
}

void loop() {
  DNS::processRequest();
  WebServer::loop();
}
