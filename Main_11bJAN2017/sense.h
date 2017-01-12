#ifndef SENSE_H
#define SENSE_H

#include <Arduino.h>

void init_sense();

// Returns FLT_MAX when nothing is seen
float sense_distance_cm();

#endif//SENSE_H

