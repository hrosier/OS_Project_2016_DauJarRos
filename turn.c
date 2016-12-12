#include "basic_include.h"
#include "movement.h"
#include "turn.h"

#define RAMP_UP 1000
#define RAMP_DOWN 1000
#define TURN_SPEED 525 //half of the max speed
#define RIGHT_ANGLE 1015


void mono_tacho_settings(uint8_t sn, int speed, int ramp_up, int ramp_down, INX_T FLAGS){
  int max_speed=0;
  // Check if the tacho can turn at this speed
  get_tacho_max_speed(sn, &max_speed);
  if (speed> max_speed ){
    printf("the robot can turn this fast (%d), its max speed is %d  \n", speed, max_speed );
    return;
  }
  set_tacho_stop_action_inx( sn, TACHO_COAST );
  set_tacho_speed_sp( sn, speed);
  set_tacho_ramp_up_sp( sn, ramp_up);
  set_tacho_ramp_down_sp( sn, ramp_down);
  set_tacho_command_inx( sn, FLAGS);
}

void turn_forever_ramp(uint8_t sn, int speed, int ramp_up, int ramp_down){
  mono_tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_FOREVER);
}

void turn_timed_ramp(uint8_t sn, int speed, int ramp_up, int ramp_down, int time, int search_obstacle){
  FLAGS_T state;
  set_tacho_time_sp( sn , time);
  mono_tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TIMED);
  
  if (search_obstacle==0){
  // Wait until the robot finishes turnning
  do {
    get_tacho_state_flags( sn, &state );
  } while(state);
  }
}

void turn_to_abs_pos_ramp(uint8_t sn, int speed, int ramp_up, int ramp_down){
  FLAGS_T state;
  mono_tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TO_ABS_POS );
  //To be more accurate on the absolute position 
  do {
    get_tacho_state_flags( sn, &state );
  } while(state);
  
  for ( int i = 0; i < 2; i++ ) {
    set_tacho_command_inx( sn, TACHO_RUN_TO_ABS_POS );
    Sleep( 500 );
  }       
}

void turn_to_rel_pos_ramp(uint8_t sn, int pos,int speed, int ramp_up, int ramp_down){
  FLAGS_T state;
  set_tacho_position_sp(sn, pos);
  mono_tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TO_REL_POS );
  //wait until the tacho finishes turning
  do {
    get_tacho_state_flags( sn, &state );
  } while(state);
}

void mono_check_for_obstacle(uint8_t sn_sonar, uint8_t sn){
  float value=0;
  // TODO: understand what these lines means 
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  //While no obstacle turn tacho 
  while (value>200 || value == 0){
    get_sensor_value0(sn_sonar, &value);
  }
  set_tacho_command_inx( sn, TACHO_STOP );
}

void bi_turn_pos_ramp(uint8_t *sn, int speed, int position, int ramp_up, int ramp_down, char search_obstacle){
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_STOP);
  set_tacho_position_sp(sn[0], position);
  set_tacho_position_sp(sn[1], -position);
  multi_set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
  if (search_obstacle==0){
    FLAGS_T state;
    //wait until the tacho finishes turning
    do {
      get_tacho_state_flags( sn[0], &state );
    } while(state);
  }
}  

void bi_turn_angle(uint8_t *sn, int speed, int angle, char search_obstacle){
  bi_turn_pos_ramp(sn,speed,angle*RIGHT_ANGLE/360,RAMP_UP,RAMP_DOWN,search_obstacle);
}

void bi_standard_turn_angle(uint8_t *sn, int angle, char search_obstacle){
  bi_turn_pos_ramp(sn,TURN_SPEED,angle*RIGHT_ANGLE/360,RAMP_UP,RAMP_DOWN,search_obstacle);
  int time_to_sleep = (int) abs(angle)*1.98+300;
  Sleep(time_to_sleep);
}

void bi_turn_angle_ramp(uint8_t *sn, int speed, int angle, int ramp_up, int ramp_down, char search_obstacle){
  bi_turn_pos_ramp(sn,speed,angle*RIGHT_ANGLE/360,ramp_up,ramp_down,search_obstacle);
}


void u_turn_right_ramp(uint8_t *sn, int speed, int ramp_up, int ramp_down, char search_obstacle){
  bi_turn_pos_ramp(sn, speed, RIGHT_ANGLE/2, ramp_up, ramp_down,search_obstacle);
}

void u_turn_left_ramp(uint8_t *sn, int speed, int ramp_up, int ramp_down, char search_obstacle){
  bi_turn_pos_ramp(sn, speed, -RIGHT_ANGLE/2, ramp_up, ramp_down,search_obstacle);
}

void bi_turn_pos(uint8_t *sn, int speed, int position, char search_obstacle){
  bi_turn_pos_ramp(sn, speed, position, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void u_turn_right(uint8_t *sn, int speed, char search_obstacle){
  u_turn_right_ramp(sn, speed, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void u_turn_left(uint8_t *sn, int speed, char search_obstacle){
  u_turn_left_ramp(sn, speed, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void turn_forever_unless_obstacle_ramp(uint8_t sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down){
  turn_forever_ramp(sn, speed, ramp_up, ramp_down);
  mono_check_for_obstacle(sn_sonar, sn);
}

void turn_timed_unless_obstacle_ramp(uint8_t sn, uint8_t sn_sonar ,int speed ,int ramp_up, int ramp_down, int time){
  turn_timed_ramp(sn, speed, ramp_up, ramp_down, time, 0);
  mono_check_for_obstacle(sn_sonar, sn);
}

void turn_forever(uint8_t sn, int speed){
  turn_forever_ramp(sn, speed, RAMP_UP, RAMP_DOWN);
}

void turn_timed(uint8_t sn, int speed, int time){
  turn_timed_ramp(sn, speed, RAMP_UP, RAMP_UP, time, 1);
}

void turn_forever_unless_obstacle(uint8_t sn, uint8_t sn_sonar, int speed){
  turn_forever_unless_obstacle_ramp(sn, sn_sonar, speed, RAMP_UP, RAMP_DOWN);
}

void turn_timed_unless_obstacle(uint8_t sn, uint8_t sn_sonar, int speed, int time){
  turn_timed_unless_obstacle_ramp(sn, sn_sonar, speed, RAMP_UP, RAMP_DOWN, time);
}

void turn_to_abs_pos(uint8_t sn, int speed){
  turn_to_abs_pos_ramp(sn, speed, RAMP_UP, RAMP_DOWN);
}

void turn_to_rel_pos(uint8_t sn, int pos, int speed){
  turn_to_rel_pos_ramp(sn, pos, speed, RAMP_UP, RAMP_DOWN);
}

void turn_right_foward(uint8_t *sn, int speed){
  turn_to_rel_pos(sn[0], RIGHT_ANGLE, speed);
}

void turn_left_foward(uint8_t *sn, int speed){
  turn_to_rel_pos(sn[1], RIGHT_ANGLE, speed);
}

void turn_right_backward(uint8_t *sn, int speed){
  turn_to_rel_pos(sn[0], - RIGHT_ANGLE, speed);
}

void turn_left_backward(uint8_t *sn, int speed){
  turn_to_rel_pos(sn[1], - RIGHT_ANGLE, speed);
}

//I think we can implement a bi_turn_forever
