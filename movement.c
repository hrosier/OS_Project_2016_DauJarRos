#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "movement.h"
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
#include <windows.h>
// UNIX //////////////////////////////////////////
#else
#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
//////////////////////////////////////////////////
#endif

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

void run_timed_ramp(uint8_t *sn, int speed, int ramp_up, int ramp_down, int time, int no_obstacle){
  FLAGS_T state;
  multi_set_tacho_time_sp( sn , time);
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TIMED);
  
  if (no_obstacle){
  // Wait until the robot finishes running
  do {
    get_tacho_state_flags( sn[0], &state );
  } while ( state );
  }
}

void run_to_abs_pos_ramp(uint8_t *sn, int speed, int ramp_up, int ramp_down){
  FLAGS_T state;
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TIMED);
  //To be more accurate on the absolute position 
  do {
    get_tacho_state_flags( sn[0], &state );
  } while ( state );
  
  for ( int i = 0; i < 2; i++ ) {
    multi_set_tacho_command_inx( sn, TACHO_RUN_TO_ABS_POS );
    Sleep( 500 );
  }       
}

void check_for_obstacle(uint8_t sn_sonar, uint8_t *sn){
  float value=0;
  // TODO: understand what these lines means 
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  //While no obstacle run tacho 
  while (value>200 || value == 0){
    get_sensor_value0(sn_sonar, &value);
  }
  multi_set_tacho_command_inx( sn, TACHO_STOP );
  Sleep( 100 );
}

void run_forever_unless_obstacle_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down){
  run_forever_ramp(sn, speed, ramp_up, ramp_down);
  check_for_obstacle(sn_sonar, sn);
}

void run_timed_unless_obstacle_ramp(uint8_t *sn, uint8_t sn_sonar ,int speed ,int ramp_up, int ramp_down, int time){
  run_timed_ramp(sn, speed, ramp_up, ramp_down, time, 0);
  check_for_obstacle(sn_sonar, sn);
}

void run_forever(uint8_t *sn, int speed){
  run_forever_ramp(sn, speed, 1000, 1000);
}

void run_timed(uint8_t *sn, int speed, int time){
  run_timed_ramp(sn, speed, 1000, 1000, time, 1);
}

void run_forever_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed){
  run_forever_unless_obstacle_ramp(sn, sn_sonar, speed, 1000, 1000);
}

void run_timed_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed, int time){
  run_timed_unless_obstacle_ramp(sn, sn_sonar, speed, 1000, 1000, time);
}

void run_to_abs_pos(uint8_t *sn, int speed){
  run_to_abs_pos_ramp(sn, speed, 1000, 1000);
}
