
#include<SPIFlash.h>
#include<SPI.h>

#include <Wire.h>
#include <L3G4200D.h>
#include <PID_v1.h>

#include <WS2812.h>

//for MP3 player
//#include "SoftwareSerial.h"

#include <MFRC522.h>

#include <Servo.h> 
#include <SPI.h>

// Before running this test, run:
//  ln -s ../../SPIAudio/SPIAudio.cpp
//  ln -s ../../SPIAudio/SPIAudio.h
#include "SPIAudio.h"

#include "cards.h"
#include "lights.h"
#include "sound.h"
#include "jingles.h"
#include "sense.h"
#include "move.h"
#include "arms.h"


IdleGlow idle_glow(2000000L, 255, 255, 255);
const int between_cards_default_pause = 150;

const int sStackDepthLimit = 200; 

CardSequence main_sequence, stored_sequence;

CardSequence *current_sequence = &main_sequence;

const int battery_level_pin = 26;
const int battery_low_level = 700;
const float sDeadBatteryVolts = (float(battery_low_level) / 1024.0f) * (3.3f * 3.0f);

const int straight_ticks = 800;
const int turn_ticks = 400;

void default_glow() {
  set_glow(idle_glow.get_r(), idle_glow.get_g(), idle_glow.get_b());
}

float battery_voltage() {
  const int battery_level = analogRead(battery_level_pin);
  float battery_voltage = float(battery_level) * ((3.3f * 3.0f) / 1024.0f);
  return battery_voltage;
}

void print_battery_level() {
  Serial.print("Battery voltage: ");
  Serial.print(battery_voltage());
  Serial.print("v");
  Serial.println();
}

void setup() {
  init_movement();
  init_sound();

  init_lights();
  
  Serial.begin(57600);		// Initialize serial communications with the PC

  SPI.begin();			// Init SPI bus
  SPIAudio::Setup();
  
  init_cards();
  init_arms();
  init_sense();
  
  randomSeed(SPIAudio::mic_read());
  
  pinMode(battery_level_pin, INPUT);
  
  set_arms(0.0f, 1.0f, 400);
  
  // Show battery level
  {
    print_battery_level();
    float batt_volts = battery_voltage();
    if(batt_volts > 7.4f) {
      set_glow(0,255,0);
    } else if(batt_volts > 7.0f) {
      set_glow(0,0,255);
    } else if(batt_volts > sDeadBatteryVolts) {
      set_glow(255,255,0);
    }
    delay(1500);
    Serial.println("starting...");
  }
}

void do_reset() {
    main_sequence.clear();
    stored_sequence.clear();
    card_scan_jingle(kCardReset);
}

void set_pause_glow(unsigned long paused_start_ms) {
    const float t_since_paused = float(millis() - paused_start_ms) / 1000.0f;
    const float norm_t = t_since_paused / 0.25f;
    const float norm_level = 0.5f * (1.0f + sin(norm_t * 2 * M_PI));
    uint8_t level = uint8_t(128 + 128 * norm_level);
    set_glow(level,level,level);
}

void do_pause_glow(int pause_millis) {
  for(const unsigned long paused_start_ms = millis();(millis() - paused_start_ms) < pause_millis;) {
    set_pause_glow(paused_start_ms);
  }
}

void execute_sequence(CardSequence const&sequence, int depth = 1) {  
  static float arm_pos = 0.65f;
  boolean paused = false;
  unsigned long paused_start_ms = 0;
  
  // If condition is -1, the action is not taken. 
  int condition = 0;
  
  default_glow();
  
  for(int card_idx=0;card_idx<sequence.count();) {
    Serial.print("Condition IS ");
    Serial.println(condition);
    unsigned long pause_millis = 1;
    
    const CardId card = sequence.atIndex(card_idx);
    if(!paused) {
      if(condition != -1) {
        switch(card) {
          case kCardForward:
            move_straight(straight_ticks);
            break;
          case kCardBackward:
            move_straight(-straight_ticks);
            break;
          case kCardLeft:
            turn(90);
            break;
          case kCardRight:
            turn(-90);
            break;
          case kCardLift:
            set_arms(arm_pos, 1.0f - arm_pos, 400);
            arm_pos = (arm_pos == 0.0f) ? 0.65f : 0.0f;
            pause_millis = between_cards_default_pause;
            break;
          case kCardPause:
            do_pause_glow(1000);
            break;
          case kCardRandom:
            condition = (random(0,2) == 0) ? -1 : 1;
            break;
          case kCardSee:
            condition = (sense_distance_cm() > 10.0f) ? -1 : 1;
            break;
          case kCardRepeat:
            // TODO: Infinite recursion
            if(&sequence != &stored_sequence && condition == 0) {
              if(depth <= sStackDepthLimit) {
                execute_sequence(stored_sequence, depth+1);
              } else {
                // Refuse to recurse too deeply
                error_jingle();
              }
            } else {
              // Support infinite recursion without stack overflow
              // NOTE: THIS MUST BE UNCONDITIONAL
              card_idx = -1;
              condition = 0;
            }
            break;
          default: {
            if(is_note_card(card)) {
              play_note(card);
              pause_millis = 100;
            }
            break;
          }
        }
      }
      if(!card_sets_condition(card)) {
        condition = 0;
      }
      ++card_idx;
      default_glow();
    } else if(paused) {
      set_pause_glow(paused_start_ms);
      pause_millis = 1;
    }
        
    for(const unsigned long smillis = millis();(millis() - smillis) < pause_millis;) {
      CardId scanned = read_one_card();
      if(scanned == kCardReset) {
        do_reset();
        return;
      } else if(scanned == kCardStart) {
        card_idx = 0;  // Loop will increment
        paused = false;
        card_scan_jingle(kCardStart);
        break;
      } else if(scanned == kCardPause) {
        paused = !paused;
        pause_jingle(paused);
        paused_start_ms = millis();
      }
    }
  }
}

void do_go() {
  if(!main_sequence.empty()) {
    card_scan_jingle(kCardStart);
  } else {
    error_jingle();
    return;
  }
  
  execute_sequence(main_sequence);
  
 finished_actions:
  flush_cards();

}

void loop() {
/* //this was causing problems when testing other batteries
  const int battery_level = analogRead(battery_level_pin);
  if(battery_level < battery_low_level) {
    set_glow(255,0,0);
    Serial.println("!!!! LOW BATTERY !!!!");
    print_battery_level();
    delay(1000);
    set_glow(0,0,0);
    //while(1); 
  }
*/  
  // Glow
  idle_glow.do_glow();

  // Card reading
  CardId scanned;
  if(scanned = read_one_card()) {
    Serial.println(scanned);
  
    // Card handling
    if(is_key_card(scanned)) {
      if(scanned == kCardRed) {
        idle_glow.set(255,0,0);
      } else if(scanned == kCardGreen) {
        idle_glow.set(0,255,0);
      } else if(scanned == kCardBlue) {
        idle_glow.set(0,0,255);
      } else if(scanned == kCardOrange) {
        idle_glow.set(255,128,0);
      } else if(scanned == kCardPink) {
        idle_glow.set(255,0,255);
      } else if(scanned == kCardYellow) {
        idle_glow.set(255,200,0);
      } else if(scanned == kCardPurple) {
        idle_glow.set(127,0,255);
      } else if(scanned == kCardStart) {
        do_go();
      } else if(scanned == kCardReset) {
        do_reset();
      } else if(scanned == kCardStore) {
        if(current_sequence == &main_sequence) {
          stored_sequence.clear();
          current_sequence = &stored_sequence;
          subroutine_jingle(false);
        } else if(current_sequence == &stored_sequence) {
          current_sequence = &main_sequence;
          subroutine_jingle(true);
        }
      }
    } else {
        if(!current_sequence->queue(scanned)) {
          error_jingle();
        } else {
           card_scan_jingle(scanned);
        }
    }
  }
}


