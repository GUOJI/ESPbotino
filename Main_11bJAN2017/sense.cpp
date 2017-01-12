
#include "sense.h"

#include <float.h>

const int trigPin = 19;
const int echoPin = 20;

void init_sense() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float sense_distance_cm() {
  float num = 0, denum = 0;

  for(int s=0;s<5;++s){
    long duration;
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 10000L);
    float distance = (duration/2) / 29.1;
    if (distance < 200 && distance > 0){
      num += distance;
      denum += 1.0f;
    }
    delay(50);
  }

  if(denum == 0.0f)
    return FLT_MAX;

  return num / denum;
}
