
#include "arms.h"
#include <Arduino.h>

const int pin_left_servo = 3;
const int pin_right_servo = 4;

void init_arms() {
  pinMode(pin_left_servo, OUTPUT);
  pinMode(pin_right_servo, OUTPUT);
}

// pos is -50 to 50
// duration is in millis
void set_arms(float left_pos_norm, float right_pos_norm, int duration) {
  const unsigned long min_val = 750L, max_val = 2500L;
  const unsigned long left_pulse_duration = min_val + (unsigned long)((max_val - min_val) * max(0.0f, min(1.0f, left_pos_norm)));
  const unsigned long right_pulse_duration = min_val + (unsigned long)((max_val - min_val) * max(0.0f, min(1.0f, right_pos_norm)));
  const unsigned long left_dead_time = 10000L - left_pulse_duration;
  const unsigned long right_dead_time = 10000L - right_pulse_duration;
  for(int cycles = max(2, duration / 10);cycles;--cycles) {
    if(cycles % 2 == 0) {
      digitalWrite(pin_left_servo, HIGH);
      delayMicroseconds(left_pulse_duration);
      digitalWrite(pin_left_servo, LOW);
      delayMicroseconds(left_dead_time);
    } else {
      digitalWrite(pin_right_servo, HIGH);
      delayMicroseconds(right_pulse_duration);
      digitalWrite(pin_right_servo, LOW);
      delayMicroseconds(right_dead_time);
    }
  }
}


