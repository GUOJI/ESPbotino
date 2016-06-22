#include "Connection.h"


void setup() {

  Serial.begin(115200);
  //LED
  pinMode(BLUEPIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  //motor
  pinMode( PWMA, OUTPUT);
  pinMode( DIRA, OUTPUT);
  pinMode( PWMB, OUTPUT);
  pinMode( DIRB, OUTPUT);
  
  WifiConnect();
  WebSocketConnect();
  MDNSConnect();
  HTTPUpdateConnect();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WifiConnect();
    WebSocketConnect();
    MDNSConnect();
  }
  else {

    webSocket.loop();
    if (millis() - lastTimeHost > 10) {
      httpServer.handleClient();
      lastTimeHost = millis();
    }
//    if (millis() - lastTimeRefresh > WAIT_RAINBOW && millis() - lastTimeRefreshRainbow > rainbowDelay && rainbowFlag) {
//      lastTimeRefreshRainbow = millis();
//      writeWheel(cnt++, RGB);
//    }

DoJob();

  }
}
