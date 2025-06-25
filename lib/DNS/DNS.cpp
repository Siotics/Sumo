#include <DNSServer.h>
#include <DNS.h>
#include <Arduino.h>
#include <config.h>
#include <ESP8266WiFi.h>

DNSServer dnsServer;

void DNS::initialize() {
    Serial.println("Initializing DNS Server...");
    IPAddress WiFiAccessPointIP = WiFi.softAPIP();
    dnsServer.start(53, "*", WiFiAccessPointIP);
}

void DNS::processRequest() {
    dnsServer.processNextRequest();
}