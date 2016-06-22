#define REFRESH_RAINBOW 500
#define WAIT_RAINBOW 10000
#define BLUEPIN 13
#define REDPIN 12
#define GREENPIN 14
#define SSID_ME "code4fun"      //WIFI
#define PW_ME "00000000"
#define HOST_ME "ESPBOT"



#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <Arduino.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include "Main.h"

//Globals
WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
const char* host = HOST_ME;
const char* ssid     = SSID_ME;
const char* password = PW_ME;


// WebSOcket Events
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

 Serial.println( "socket event "+(String)num+" "+(String)type );

  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
      }
      break;
      
    case WStype_TEXT:
      {
        lastTimeRefresh = millis();
        String text = String((char *) &payload[0]);
        HandleCommond(text);
      }
      break;

    case WStype_BIN:
      hexdump(payload, length);
      // echo data back to browser
      webSocket.sendBIN(num, payload, length);
      break;
  }
//webSocket.sendTXT(num, "led just lit", length);
  
}


// Wifi Connection
void WifiConnect() {

 // WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println( "Connecting...." );
    delay(300);
  }
  

  Serial.println( "Connected" );

 Serial.println( WiFi.localIP() );

}

// WebSocket Connection
void WebSocketConnect() {
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

// MDNS 
void MDNSConnect() {
  if (!MDNS.begin(host)) {
   //DEBUGGING("Error setting up MDNS responder!");
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  //DEBUGGING("mDNS responder started");
   Serial.println("mDNS responder started");
  MDNS.addService("ws", "tcp", 81);
  MDNS.addService("http", "tcp", 80);
}

// HTTP updater connection
void HTTPUpdateConnect() {
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  //DEBUGGING_L("HTTPUpdateServer ready! Open http://");
   Serial.println("HTTPUpdateServer ready! Open http://");
  //DEBUGGING_L(host);
   Serial.println(host);
  //DEBUGGING(".local/update in your browser\n");
   Serial.println(".local/update in your browser\n");
}


