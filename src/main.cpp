#include <config.h>
#include <Arduino.h>
#include <DNS.h>
#include <WebServer.h>
#include <WifiAP.h>
#include <WheelController.h>

WheelController wheels(MOTOR_LEFT_BACKWARD, MOTOR_LEFT_FORWARD, MOTOR_RIGHT_BACKWARD, MOTOR_RIGHT_FORWARD);

void setup() {
  Serial.begin(115200);

  WifiAP::initialize(WIFI_AP_SSID_PREFIX, WIFI_AP_PASSWORD, WIFI_AP_MAX_CONNECTION);
  DNS::initialize();
  WebServer::initialize(wheels);
}

void loop() {
  DNS::processRequest();
  WebServer::loop();
}
