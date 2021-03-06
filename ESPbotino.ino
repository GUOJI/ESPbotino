#include "Connection.h"
 



int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {

  pinMode(BUILTIN_LED, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  
//



  

  Serial.setDebugOutput(true);
  String a=(String)ESP.getChipId();
  Serial.println("..");
  Serial.println("Serial number: "+a);
  //LED
  pinMode(BLUEPIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  //motor
  pinMode( PWMA, OUTPUT);
  pinMode( DIRA, OUTPUT);
  pinMode( PWMB, OUTPUT);
  pinMode( DIRB, OUTPUT);

  SetupSoftAP();
  WebSocketConnect();
  MDNSConnect();
  SetupFS();
  SetupConfigPages();
  HTTPUpdateConnect();
  GetWifiSetting();

}

void loop() {

  if (millis() - lastTimeHost > 10) {
      httpServer.handleClient();
      lastTimeHost = millis();
  }
  if (WiFi.status() != WL_CONNECTED) {
   WifiConnect();
    }
  else {
    webSocket.loop();
    
    LEDRainBow();
    }
    
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (ledState == LOW)
        ledState = HIGH;  // Note that this switches the LED *off*
      else
        ledState = LOW;   // Note that this switches the LED *on*
      digitalWrite(BUILTIN_LED, ledState);
  }
}



