#define HOST_ME "ESPBOT"

/* Soft AP network parameters */

const char *softAP_password = "12345678";
char mysoftAP[32] = "";


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <ArduinoJson.h>   
#include <FS.h>   
#include "Credentials.h"
#include "LED.h"
#include "motor.h"
#include "HandleHttp.h"
#include "ESP8266BASIC.h"


//Globals
/* Don't set this wifi credentials. They are configurated at runtime and stored on EEPROM */


WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
const char* host = HOST_ME;
IPAddress apIP(66, 66, 6, 1);
IPAddress netMsk(255, 255, 255, 0);
/** Should I connect to WLAN asap? */
boolean connect;
/** Last time I tried to connect to WLAN */
long lastConnectTry = 0;
/** Current WLAN status */
int status = WL_IDLE_STATUS;

char mqtt_server[40];
char mqtt_port[6] = "8080";
char blynk_token[34] = "YOUR_BLYNK_TOKEN";



// WebSOcket Events
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  Serial.println( "socket event " + (String)num + " " + (String)type );

  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        //String text = String((char *) &payload[0]);
        Serial.println((String)ip);
      }
      break;

    case WStype_TEXT:
      {
        lastTimeRefresh = millis();
        String text = String((char *) &payload[0]);


        Serial.println( text );
        String result=iHandleCommand(text);
        LEDcommond(text);
        MotorCommond(text);
        //String R=(String)result;
        webSocket.sendTXT(num, result);
      }
      break;

    case WStype_BIN:
      {
        hexdump(payload, length);
        // echo data back to browser
        webSocket.sendBIN(num, payload, length);
      }
      break;
  }
}

//softAP init
void SetupSoftAP() {
  loadWifiName();
  WiFi.softAPConfig(apIP, apIP, netMsk);
  //WiFi.softAP(softAP_ssid, softAP_password);
  String thisname=(String)ESP.getChipId()+"_Need_Setup_WiFi";
  thisname.toCharArray(mysoftAP, 32);
     // sprintf(mysoftAP, thisname);
  WiFi.softAP(mysoftAP);
  delay(500); // Without delay I've seen the IP address blank
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void handleHome() {
  httpServer.sendContent(Header());
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  String ContentFinal = "";
  ContentFinal = Content1() + Content2();
  String ContentX = "";
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      ContentX = ContentX + "<option>" + (String)WiFi.SSID(i) + "</option>";
    }
  }
  else {
    ContentX = "<option value=\"\" disabled=\"disabled\" selected=\"selected\">NO WiFi FOUND</option>" ;
  }
  ContentFinal = ContentFinal + ContentX + Content3();
  httpServer.sendContent(ContentFinal);
  httpServer.sendContent(Script1());
   httpServer.sendContent(Script2());
    httpServer.sendContent(Script3());
  httpServer.client().stop(); // Stop is needed because we sent no content
}





/** Handle the WLAN save form and redirect to WLAN config page again */
void handleWifiSave() {
  Serial.println("wifi save");
  httpServer.arg("n").toCharArray(ssid, sizeof(ssid) - 1);
  httpServer.arg("p").toCharArray(password, sizeof(password) - 1);
  if(httpServer.arg("wn").length()>0){
  httpServer.arg("wn").toCharArray(iname, sizeof(iname) - 1);
  }
  httpServer.sendContent("JOB DONE, YOU MIGHT NEED TO RESTART YOUR ESP");
  httpServer.client().stop(); // Stop is needed because we sent no content length
  saveCredentials();
  saveWifiName();
  connect = strlen(ssid) > 0; // Request WLAN connect with new credentials if there is a SSID
}

void handleContent1() {
  httpServer.sendContent("test page :P");
}

void SetupFS(){
   if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(blynk_token, json["blynk_token"]);

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read
}


//init config pages
void SetupConfigPages() {
  httpServer.on("/test", handleContent1);
  httpServer.on("/", handleHome);
  httpServer.on("/wifisave", handleWifiSave);
  httpServer.serveStatic("/", SPIFFS, "/");
}

//get WiFiSetting
void GetWifiSetting() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println ( "reset AP" );
    WiFi.softAPConfig(apIP, apIP, netMsk);
      sprintf(mysoftAP,"_%d:%d:%d:%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
    String thisname=iname+(String)mysoftAP;
      thisname.toCharArray(mysoftAP, 32);
    WiFi.softAP(mysoftAP, softAP_password);
    Serial.println ( "AP ok " + (String)mysoftAP );
  }
  loadCredentials(); // Load WLAN credentials from network
  loadWifiName();
  connect = strlen(ssid) > 0; // Request WLAN connect if there is a SSID
  Serial.println ( "get wifi setting");
  Serial.println ( (String)ssid + " " + (String)password+"  "+(String)iname );
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
    //while (1) {
    // delay(50);
    // }
  }
  //DEBUGGING("mDNS responder started");
  Serial.println("mDNS responder started");
  MDNS.addService("ws", "tcp", 81);
  MDNS.addService("http", "tcp", 80);
}


//to connect wifi
void connectWifi() {
  //GetWifiSetting();
  Serial.println("Connecting as wifi client...");
  WiFi.disconnect();
  WiFi.begin ( ssid, password );
  int connRes = WiFi.waitForConnectResult();
  Serial.print ( "connRes: " );
  Serial.println ( connRes );
}

// Wifi Connection
void WifiConnect() {


  if (connect) {
    Serial.println ( "Connect requested" );
    connect = false;
    Serial.println ( (String)ssid + (String)password );
    connectWifi();
    lastConnectTry = millis();
  }

  int s = WiFi.status();
  if (s == 0 && millis() > (lastConnectTry + 60000) ) {

    connect = true;
  }
  if (status != s) { // WLAN status change
    Serial.print ( "Status: " );
    Serial.println ( s );
    status = s;
    if (s == WL_CONNECTED) {

      Serial.println ( "" );
      Serial.print ( "Connected to " );
      Serial.println ( ssid );
      Serial.print ( "IP address: " );
      Serial.println ( WiFi.localIP() );

      Serial.println ( "reset AP" );
      WiFi.softAPConfig(apIP, apIP, netMsk);
    sprintf(mysoftAP,"_%d:%d:%d:%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
    String thisname=iname+(String)mysoftAP;
    thisname.toCharArray(mysoftAP, 32);
    WiFi.softAP(mysoftAP, softAP_password);
      Serial.println ( "AP ok " + (String)mysoftAP );
      WebSocketConnect();
      MDNSConnect();
      if (s == WL_NO_SSID_AVAIL) {
        WiFi.disconnect();
      }
    }
  }

}




// HTTP updater connection
void HTTPUpdateConnect() {
  httpUpdater.setup(&httpServer);
  httpServer.begin();

  Serial.println("HTTPUpdateServer ready! Open http://");
  Serial.println(host);

}











