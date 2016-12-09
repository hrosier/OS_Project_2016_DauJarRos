#include "basic_include.h"
#include "movement.h"
#include "turn.h"

#define DOOR_POS 100
#define RAMP_UP 500
#define RAMP_DOWN 500

void door_ramp(uint8_t sn3, int position, int speed, int ramp_up, int ramp_down) {
    FLAGS_T state ;
    set_tacho_position_sp( sn3, position );
    set_tacho_speed_sp( sn3, speed);
    set_tacho_ramp_up_sp( sn3, ramp_up );
    set_tacho_ramp_down_sp( sn3, ramp_down );
    set_tacho_command_inx( sn3, TACHO_RUN_TO_REL_POS );
    do {
      get_tacho_state_flags( sn3, &state );
    } while ( state );
    //The door will be prevented to move du to the ball
    set_tacho_stop_action_inx( sn3, TACHO_BRAKE );
}

void door_up_ramp( uint8_t sn3, int speed, int ramp_up, int ramp_down) {
  door_ramp(sn3,- DOOR_POS,speed,ramp_up,ramp_down);
}

void door_down_ramp( uint8_t sn3, int speed, int ramp_up, int ramp_down) {
  door_ramp(sn3,DOOR_POS,speed,ramp_up,ramp_down);
}

void door_up( uint8_t sn3, int speed) {
  door_up_ramp(sn3,speed,RAMP_UP,RAMP_DOWN);
}

void door_down( uint8_t sn3, int speed) {
  door_down_ramp(sn3,speed,RAMP_UP,RAMP_DOWN);
}

void catch_dist(uint8_t *sn, uint8_t sn3, int speed, int position){
   //Open the door
   door_up(sn3,speed);
   Sleep(1000);
   // Go foward a little
   // TODO : Farie la convertion
   run_timed(sn,speed,position);
   Sleep(position);

   // close the door 
   door_down(sn3,speed);
   Sleep(1000);
}

void scan_angle_distance(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int distance){
    float value=0;
    if ( !get_sensor_value0(sn_sonar, &value )) {
      value = 0;
    }
    bi_turn_angle(sn, speed, angle,1);
    while (value > distance || value == 0){
      get_sensor_value0(sn_sonar, &value);
    }
    //TODO :If on the compas value to know if we enconter the ball ?
    stop_running(sn);
    //TODO :run foward to see if it is the ball 
    // We need to convert value to a position used by the tacho
    run_to_rel_pos(sn,speed,value,1);
    //TODO : check if it is the ball
}

void door_up_down( uint8_t sn3, int speed ){
  door_up(sn3,speed);
  Sleep(1000);
  door_down(sn3,speed);
}

