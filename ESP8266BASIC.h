#include <Servo.h> 

int iGetPin(String pin) {
  if (pin == "00")
    return 0;
  if (pin == "01")
    return 1;
  if (pin == "02")
    return 2;
  if (pin == "03")
    return 3;
  if (pin == "04")
    return 4;
  if (pin == "05")
    return 5;

  if (pin == "09")
    return 9;
  if (pin == "10")
    return 10;

  if (pin == "12")
    return 12;
  if (pin == "13")
    return 13;
  if (pin == "14")
    return 14;
  if (pin == "15")
    return 15;
  if (pin == "16")
    return 16;
  if (pin == "17")
    return 17;
}

//Servo setup
Servo iServo[32];



void iPinMode(int pin, String IO) {
  if (IO == "I")
    pinMode(pin, INPUT);
  else if (IO == "O")
    pinMode(pin, OUTPUT);
}

void iDigitalWrite(int pin, String HL) {
  if (HL == "H")
    digitalWrite(pin, HIGH);
  else if (HL == "L")
    digitalWrite(pin, LOW);
}

void iAnalogWrite(int pin, String value) {
  analogWrite(pin, value.toInt());
}

int iDigitalRead(int pin){
  return digitalRead(pin);
}

int iAnalogRead(int pin){
  return analogRead(pin);
}

int iHandleCommand(String Comm) {
   int pin=-1;
   String value=""; 
   
  String F = Comm.substring(0, 2);
  if(F=="PM"){
    //pinMode
    pin = iGetPin(Comm.substring(2, 4));
    value = Comm.substring(4, Comm.length());
    iPinMode(pin, value); 
    return 1;
  }
  else if(F=="DW"){
    //digitalWrite
    pin = iGetPin(Comm.substring(2, 4));
    value = Comm.substring(4, Comm.length());
    iDigitalWrite(pin,value);
     return 2;
  }
  else if(F=="AW"){
    //analogWrite
    pin = iGetPin(Comm.substring(2, 4));
    value = Comm.substring(4, Comm.length());
    iAnalogWrite(pin,value);
    return 3;
  }
  else if(F=="DR"){
    pin = iGetPin(Comm.substring(2, 4));
    return iDigitalRead(pin);
    //return 4;
  }
  else if(F=="AR"){
    pin = iGetPin(Comm.substring(2, 4));
    return iAnalogRead(pin);
    //return 5;
  }  
  Serial.println(F + "....." + (String)pin + "...." + (String)value);
}









long iMap(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




