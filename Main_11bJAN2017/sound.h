
#ifndef SOUND_H
#define SOUND_H

#define DEFAULT_VOLUME 70

void play_note(int note_period_micros);

void init_sound();
void chip_tone(unsigned long for_millis, unsigned long period_micros, int volume=DEFAULT_VOLUME);

void mp3_play(int a);
void mp3_volume(int a);
void mp3_stop();

void sendChar(char c);


#endif//SOUND_H

