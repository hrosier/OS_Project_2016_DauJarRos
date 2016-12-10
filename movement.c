#include "basic_include.h"
#include "movement.h"

#define RAMP_UP 1000
#define RAMP_DOWN 1000

void stop_running(uint8_t *sn){
    multi_set_tacho_command_inx( sn , TACHO_STOP);
}

void tacho_settings(uint8_t *sn, int speed, int ramp_up, int ramp_down, INX_T FLAGS){
  int max_speed=0;
  // Check if the robot can run at this speed
  get_tacho_max_speed(sn[0], &max_speed);
  if (speed> max_speed ){
    printf("the robot can run this fast (%d), its max speed is %d  \n", speed, max_speed );
    return;
  }
  multi_set_tacho_stop_action_inx( sn, TACHO_COAST );
  multi_set_tacho_speed_sp( sn, speed);
  multi_set_tacho_ramp_up_sp( sn, ramp_up);
  multi_set_tacho_ramp_down_sp( sn, ramp_down);
  multi_set_tacho_command_inx( sn, FLAGS);
}

void run_forever_ramp(uint8_t *sn, int speed, int ramp_up, int ramp_down){
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_FOREVER);
}

void run_timed_ramp(uint8_t *sn, int speed, int ramp_up, int ramp_down, int time, int search_obstacle){
  FLAGS_T state;
  multi_set_tacho_time_sp( sn , time);
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TIMED);
  
  if (search_obstacle==0){
  // Wait until the robot finishes running
  do {
    get_tacho_state_flags( sn[0], &state );
  } while ( state );
  }
}

void run_to_abs_pos_ramp(uint8_t *sn, int speed, int ramp_up, int ramp_down, int search_obstacle){
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TO_ABS_POS);
  if(search_obstacle==0){
    FLAGS_T state;
    //To be more accurate on the absolute position 
    do {
      get_tacho_state_flags( sn[0], &state );
    } while ( state );

    //  for ( int i = 0; i < 2; i++ ) {
    //    multi_set_tacho_command_inx( sn, TACHO_RUN_TO_ABS_POS );
    //    Sleep( 500 );
    //}       
  }
}

void run_to_rel_pos_ramp(uint8_t *sn, int speed, int position, int ramp_up, int ramp_down, int search_obstacle){
  multi_set_tacho_position_sp(sn, position);
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TO_REL_POS);
  if(search_obstacle==0){
    FLAGS_T state;
    //To be more accurate on the absolute position 
    do {
      get_tacho_state_flags( sn[0], &state );
    } while ( state );

    //for ( int i = 0; i < 2; i++ ) {
    //  multi_set_tacho_command_inx( sn, TACHO_RUN_TO_ABS_POS );
    //  Sleep( 500 );
    //}   
  }    
}
void check_for_obstacle(uint8_t sn_sonar, uint8_t *sn){
  float value=0;
  // TODO: understand what these lines means 
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  //While no obstacle run tacho 
  while (value>100 || value == 0){
    get_sensor_value0(sn_sonar, &value);
  }
  multi_set_tacho_command_inx( sn, TACHO_STOP );
  printf("Il y a un obstacle \n");
  Sleep( 100 );
}

void run_forever_unless_obstacle_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down){
  run_forever_ramp(sn, speed, ramp_up, ramp_down);
  check_for_obstacle(sn_sonar, sn);
}

void run_timed_unless_obstacle_ramp(uint8_t *sn, uint8_t sn_sonar ,int speed ,int ramp_up, int ramp_down, int time){
  run_timed_ramp(sn, speed, ramp_up, ramp_down, time, 1);
  check_for_obstacle(sn_sonar, sn);
}

void run_forever(uint8_t *sn, int speed){
  run_forever_ramp(sn, speed, RAMP_UP, RAMP_DOWN);
}

void run_timed(uint8_t *sn, int speed, int time){
  run_timed_ramp(sn, speed, RAMP_UP, RAMP_DOWN, time, 1);
}

void run_forever_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed){
  run_forever_unless_obstacle_ramp(sn, sn_sonar, speed, RAMP_UP, RAMP_DOWN);
}

void run_timed_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed, int time){
  run_timed_unless_obstacle_ramp(sn, sn_sonar, speed, RAMP_UP, RAMP_DOWN, time);
}

void run_to_abs_pos(uint8_t *sn, int speed, int search_obstacle){
  run_to_abs_pos_ramp(sn, speed, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void run_to_rel_pos(uint8_t *sn, int speed, int position, int search_obstacle){
  run_to_rel_pos_ramp(sn, speed, position, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void run_distance(uint8_t *sn, int speed, int distance, int search_obstacle){
  run_to_rel_pos_ramp(sn, speed, distance*1000/480, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void run_distance_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed, int distance){
  run_to_rel_pos_ramp(sn, speed, distance*1000/480, RAMP_UP, RAMP_DOWN, 1);
  check_for_obstacle(sn_sonar, sn);
}
