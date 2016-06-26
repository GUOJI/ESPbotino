
#define REFRESH_RAINBOW 500
#define WAIT_RAINBOW 10000
#define BLUEPIN 13
#define REDPIN 12
#define GREENPIN 14




unsigned long lastTimeHost = 0;
unsigned long lastTimeRefresh = 0;
unsigned long lastTimeRefreshRainbow = 0;
boolean rainbowFlag = 1;
int RGB[3];
int cnt = 0;
int rainbowDelay = REFRESH_RAINBOW;

//Wheel - return HUE[iii] in RGB
void Wheel(int WheelPos, int* RGB) {
  WheelPos = WheelPos % 256;

  if (WheelPos < 85) {
    RGB[0] = WheelPos * 3;
    RGB[1] = 255 - WheelPos * 3;
    RGB[2] = 0;
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    RGB[2] = WheelPos * 3;
    RGB[0] = 255 - WheelPos * 3;
    RGB[1] = 0;
  }
  else if (WheelPos < 255) {
    WheelPos -= 170;
    RGB[1] = WheelPos * 3;
    RGB[2] = 255 - WheelPos * 3;
    RGB[0] = 0;

  }
  else
  {
    WheelPos -= 255;
    RGB[0] = WheelPos * 3;
    RGB[1] = 255 - WheelPos * 3;
    RGB[2] = 0;
  }
}

// Write wheel to leds
void writeWheel(int WheelPos, int* RGB) {
  Wheel(WheelPos, RGB);
  analogWrite(REDPIN, map(RGB[0], 0, 255, 0, 1023));
  analogWrite(GREENPIN, map(RGB[1], 0, 255, 0, 1023));
  analogWrite(BLUEPIN, map(RGB[2], 0, 255, 0, 1023));
}

void LEDcommond(String text)
{
          if (text == "LED") {
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13, LOW);
          Serial.println("led just lit");
         // webSocket.sendTXT(num, "led just lit", length);
        }

        else if (text.startsWith("x")) {
          String xVal = (text.substring(text.indexOf("x") + 1, text.length()));
          int xInt = xVal.toInt();
          analogWrite(REDPIN, xInt);
         // DEBUGGING(xVal);
        }

        else if (text.startsWith("y")) {
          String yVal = (text.substring(text.indexOf("y") + 1, text.length()));
          int yInt = yVal.toInt();
          analogWrite(GREENPIN, yInt);
        //  DEBUGGING(yVal);
        }

        else if (text.startsWith("z")) {
          String zVal = (text.substring(text.indexOf("z") + 1, text.length()));
          int zInt = zVal.toInt();
          analogWrite(BLUEPIN, zInt);
         // DEBUGGING(zVal);
        }
        else if (text.startsWith("t")) {
          String tVal = (text.substring(text.indexOf("t") + 1, text.length()));
          rainbowDelay = tVal.toInt();
          lastTimeRefreshRainbow = 0;
          lastTimeRefresh = 0;
         // DEBUGGING(tVal);        
        }        
        else if (text == "RESET") {
          rainbowFlag = 0;
          analogWrite(BLUEPIN, LOW);
          analogWrite(REDPIN, LOW);
          analogWrite(GREENPIN, LOW);
        //  DEBUGGING("reset");

        }
        else if (text == "RAINBOW") {
          rainbowFlag = 1;
          lastTimeRefreshRainbow = 0;
          lastTimeRefresh = 0;

          
        }
       
}

void LEDRainBow(){
      if (millis() - lastTimeRefresh > WAIT_RAINBOW && millis() - lastTimeRefreshRainbow > rainbowDelay && rainbowFlag) {
      lastTimeRefreshRainbow = millis();
      writeWheel(cnt++, RGB);
    }
}


