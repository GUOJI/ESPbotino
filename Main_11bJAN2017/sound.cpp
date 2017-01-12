
#include "sound.h"

#include <Arduino.h>

//const int pin_spk_en = 15;
//const int pin_spk_dir = 23;
const int pin_spk = 23;

#define BITTIME 93      // adjusted to obtain 104 milliseconds delay (9600bauds).

void init_sound() {
  pinMode(pin_spk, OUTPUT);
  mp3_volume(20);
}

void chip_tone(unsigned long for_millis, unsigned long period_micros, int volume) {
  //  play(1);
  //  delay(1000);      //delays would not be needed
  //  play(2);
  //  delay(1000);
  //  play(3);
  //  delay(1000);
  mp3_play(3);
  delay(for_millis);
  mp3_stop();
}



void mp3_play(int a)
{
  //FD 04 41 00 04 DF
  sendChar(0xFD);
  sendChar(0x04);
  sendChar(0x41);
  sendChar((byte)0);
  sendChar(a);
  sendChar(0xDF);
}



void mp3_volume(int a)
{
  //FD 03 31 (0 to 30) DF
  sendChar(0xFD);
  sendChar(0x03);
  sendChar(0x31);
  sendChar(a);
  sendChar(0xDF);
  // delay(100);
}

void mp3_stop( void ) {
  //FD 02 02 DF
  sendChar(0xFD);
  sendChar(0x02);
  sendChar(0x02);
  sendChar(0xDF);
  // delay(100);
}

//----------------------------------------------------------------------------
void sendChar(char c) {
  delayMicroseconds(BITTIME * 2);        // wait 2 Stop bits before sending the char
  digitalWrite(pin_spk, LOW);             // low the line
  delayMicroseconds(BITTIME);            // wait Start bit
  for (int i = 0; i < 8; i++) {
    digitalWrite(pin_spk, bitRead(c, i)); // bit out.
    delayMicroseconds(BITTIME);          // wait bit
  }
  digitalWrite(pin_spk, HIGH);           //Return TXDATA pin to "1".
}

