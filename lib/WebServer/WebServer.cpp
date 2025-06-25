#include <Arduino.h>
#include <WebServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "config.h"

AsyncWebServer HTTPServer(80);
AsyncWebSocketMessageHandler WebsocketHandler;
AsyncWebSocket WebsocketServer("/ws", WebsocketHandler.eventHandler());


static uint32_t lastWebsocket = millis();
static uint32_t deltaWebsocket = 2000;

void onNotFoundHandler(AsyncWebServerRequest *request);
void onWebsocketConnect(AsyncWebSocket *server, AsyncWebSocketClient *client);
void onWebsocketDisconnect(AsyncWebSocket *server, uint32_t clientId);
void onWebsocketError(AsyncWebSocket *server, AsyncWebSocketClient *client, uint16_t errorCode, const char *reason, size_t len);
void onWebsocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, const uint8_t *data, size_t len);
void onWebsocketFragment(AsyncWebSocket *server, AsyncWebSocketClient *client, const AwsFrameInfo *frameInfo, const uint8_t *data, size_t len);


void WebServer::initialize() {
    Serial.println("Initializing HTTP WebServer...");
    Serial.println("Mounting LittleFS...");
    if(!LittleFS.begin()){
        Serial.println("ERROR: Failed to mount LITTLEFS");
        return;
    }
    
    HTTPServer.onNotFound(onNotFoundHandler);
    HTTPServer.serveStatic("/", LittleFS, "/")
        .setDefaultFile("index.html");

    Serial.println("Initializing Websocket Server");
    HTTPServer.addHandler(&WebsocketServer).addMiddleware([](AsyncWebServerRequest *request, ArMiddlewareNext next){
        if(WebsocketServer.count() > 1){
            request->send(503, "text/plain", "Server is busy");
        } else {
            next();
        }
    });

    HTTPServer.addHandler(&WebsocketServer);

    HTTPServer.begin();

    Serial.println("HTTP and Websocket Server Started.");
}

void WebServer::loop(){
    uint32_t now = millis();
    if(now - lastWebsocket >= deltaWebsocket){
        WebsocketServer.cleanupClients();
        WebsocketServer.printfAll("now: %" PRIu32 "\n", now);
        lastWebsocket = millis();
    }
}


void onNotFoundHandler(AsyncWebServerRequest *request){
    request->redirect("/");
}