#include "basic_include.h"
#include "grab.h"

#define RAMP_UP 10 
#define RAMP_DOWN 10
#define THROW_POS -130 
#define THROW_SPEED 1170

void throw_pos(uint8_t sn, int speed, int position){
  door_ramp(sn, position, speed, RAMP_UP, RAMP_DOWN);
}

void throw(uint8_t sn){
  throw_pos(sn,THROW_SPEED,THROW_POS);
}

