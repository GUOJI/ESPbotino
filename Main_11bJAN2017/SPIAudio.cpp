
#include<SPIFlash.h>
#include<SPI.h>

#include "SPIAudio.h"

const int pin_spk_en = 15;
const int pin_spk_dir = 23;
const int mic = 31;

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

void SPIAudio::Setup()
{
  pinMode(pin_spk_dir, OUTPUT);
  pinMode(pin_spk_en, OUTPUT);
  pinMode(mic, INPUT);

  // Fast ADC for record
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);

  // Off: don't burn speaker
  OCR2A = 0;
  TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);
  
  // 62.5Khz fast PWM

  // Use internal clock (datasheet p.160)
  ASSR &= ~(_BV(EXCLK) | _BV(AS2));

  // Set fast PWM mode  (p.157)
  TCCR2A |= _BV(WGM21) | _BV(WGM20);
  TCCR2B &= ~_BV(WGM22);

  // Do non-inverting PWM on pin OC2A (p.155)
  // On the Arduino this is pin 11.
  TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
  TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
  TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);
}

int SPIAudio::mic_read() {
  return analogRead(mic);
}

boolean SPIAudio::StreamBlocks(SPIFlash &flash, unsigned long block, unsigned long count, AudioRate rate)
{
  uint8_t rateDelay = 0;
  
  switch(rate) {
    case AudioRate_16khz:
      rateDelay = 100;
      break;
    case AudioRate_32khz:
      rateDelay = 23;
      break;
    default:
      Serial.println("Unsupported sample rate");
      return false;
  }
    
  flash._beginRead(flash._prepRead((uint16_t)block));
  noInterrupts();
  for(uint32_t i=0;i<(uint32_t(count) * uint32_t(256L));++i) {
      _delay_loop_1(rateDelay);
      
      uint8_t sample = flash._readNextByte(true);
  
      int setI = int(sample) - 128;
      digitalWrite(pin_spk_dir, (setI < 0) ? HIGH : LOW);
      
      // 250 to protect bridge (bootstrap)
      // TODO: 1 bit of wasted precision
      OCR2A = min(250, abs(setI) << 1);
  }
  OCR2A = 0;
  flash._endProcess();
  interrupts();
  return true;
}

boolean SPIAudio::RecordBlocks(SPIFlash &flash, unsigned long block, unsigned long count, AudioRate rate)
{
  uint8_t rateDelay = 0;
  
  switch(rate) {
    case AudioRate_16khz:
      rateDelay = 40;
      break;
    default:
      Serial.println("Unsupported sample rate");
      return false;
  }
      
  const uint32_t address = flash._prepWrite((uint16_t)block);
  
  uint32_t size32 = (uint32_t(count) * uint32_t(256L));
  if(!flash._notPrevWritten(address, size32))
    return false;

  noInterrupts();
  long avg_val_accum = 0L;
  const int n_samples_center = 300;
  for(int i=0;i<n_samples_center;++i) {
    avg_val_accum += analogRead(mic);
    _delay_loop_1(rateDelay);
  }
  const int avg_val = avg_val_accum / n_samples_center;

  for(unsigned long i=0;i<count;++i) {
    uint32_t address = flash._prepWrite((uint16_t)(block + i));
    flash._beginWrite(address);
    for(uint16_t idx=0;idx<256;++idx) {
      const int raw_val = analogRead(mic);
      const int val = raw_val - avg_val;
      uint8_t sample = max(0, min(255, 0x80 + val / 2));
      flash._writeNextByte(sample, true);
      
      _delay_loop_1(rateDelay);
    }
    flash._endProcess();
  }
  interrupts();
  return true; 
}

