#include "LED.h"
#include "motor.h"

void HandleCommond(String text) {
  Serial.println( text );
  LEDcommond(text);
  MotorCommond(text);
}


void DoJob(){
LEDRainBow();
}

