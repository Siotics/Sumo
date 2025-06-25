#include <WifiAP.h>
#include <ESP8266WiFi.h>
#include "config.h"

void WifiAP::initialize(const char* ssidPrefix, const char* password, short maxConnection){
    Serial.println("Initializing Wifi...");
    String WIFI_SSID = ssidPrefix;
    WIFI_SSID += String(ESP.getChipId());
    Serial.print("Starting Access Point with SSID ");
    Serial.print(WIFI_SSID);
    Serial.print(" and password ");
    Serial.println(password);

    WiFi.softAP(WIFI_SSID.c_str(), password, 1, 0, maxConnection);

    Serial.println("Wifi Access Point Started.");
}