/* this file contains the functions used to deal with the catapult */

#include "basic_include.h"
#include "grab.h"

#define RAMP_UP 10 
#define RAMP_DOWN 10
#define THROW_POS -130 
#define THROW_SPEED 1170

/**
* \brief : function used to make the motor of the catapult run at a certain speed to a certain position
* \param uint8_t sn4 : the sequence number of the catapult motor
* \param int speed : th speed of the motor we want the motor to run
* \param int position : the position we want the motor to run
*/
void throw_pos(uint8_t sn4, int speed, int position){
  door_ramp(sn4, position, speed, RAMP_UP, RAMP_DOWN);
}

/**
* \brief : function used to thrown the projectiles
* \param uint8_t sn4 : the sequence number of the catapult motor
*/
void throw(uint8_t sn4){
	// THROW_SPEED and THROW_POS are defined in common_variables, there are chosen after several tries	
  throw_pos(sn4,THROW_SPEED,THROW_POS);
}
