#include "basic_include.h"
#include "movement.h"
#include "turn.h"
#include "grab.h"

#define DOOR_POS 100
#define DOOR_SPEED 550
#define RAMP_UP 500
#define RAMP_DOWN 500

void door_ramp(uint8_t sn3, int position, int speed, int ramp_up, int ramp_down) {
  //FLAGS_T state ;
  set_tacho_position_sp( sn3, position );
  set_tacho_speed_sp( sn3, speed);
  set_tacho_ramp_up_sp( sn3, ramp_up );
  set_tacho_ramp_down_sp( sn3, ramp_down );
  set_tacho_stop_action_inx( sn3, TACHO_HOLD );
  set_tacho_command_inx( sn3, TACHO_RUN_TO_REL_POS );
  // do {
  //   get_tacho_state_flags( sn3, &state );
  // } while ( state );
  //The door will be prevented to move du to the ball
  Sleep(2000);
  set_tacho_stop_action_inx( sn3, TACHO_HOLD );
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

void door_up_standard( uint8_t sn3) {
  door_up_ramp(sn3,DOOR_SPEED,RAMP_UP,RAMP_DOWN);
  Sleep(200);
}

void door_down_standard( uint8_t sn3){
  door_down_ramp(sn3,DOOR_SPEED,RAMP_UP,RAMP_DOWN);
  Sleep(200);
}

void door_mi_up( uint8_t sn3, int speed) {
  door_ramp(sn3,-DOOR_POS*3/4,speed,RAMP_UP,RAMP_DOWN);
}

void door_mi_down( uint8_t sn3, int speed) {
  door_ramp(sn3,DOOR_POS*3/4,speed,RAMP_UP,RAMP_DOWN);
}

void door_mi_up_standard( uint8_t sn3) {
  door_ramp(sn3,-DOOR_POS*3/4,DOOR_SPEED,RAMP_UP,RAMP_DOWN);
}

void door_mi_down_standard( uint8_t sn3) {
  door_ramp(sn3,DOOR_POS*3/4,DOOR_SPEED,RAMP_UP,RAMP_DOWN);
}

void catch_dist(uint8_t *sn, uint8_t sn3, int speed, int distance){
  //Open the door
  door_up_standard(sn3);
  Sleep(1000);
  // Go foward a little
  run_distance(sn,speed,distance,0);

  // close the door 
  door_down_standard(sn3);
  Sleep(1000);
}

void catch_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar,int speed){
  float value=0;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  catch_dist(sn,sn3,speed,value+30);
}

void catch_ball_after_check(uint8_t *sn, uint8_t sn3,int speed){
  run_distance(sn,speed,100,0);
  door_mi_down_standard(sn3);
}

int scan_angle_distance(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int distance){
  float value;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  bi_turn_angle(sn, speed, angle, 1);
  FLAGS_T state;
  get_tacho_state_flags(sn[0],&state);
  while ((value > distance || value == 0) && state){
    get_sensor_value0(sn_sonar, &value);
    get_tacho_state_flags(sn[0],&state);
  }
  stop_running(sn);
  if (value>distance){
    printf("There is not obstacle in the range %d \n",distance);
  }
  else {
    printf("There is an obstacle in the range %d \n",distance);
    if(distance<300){
      bi_turn_angle(sn,speed/6, 20-0.06*distance,1);
    }
    if (distance>400){
      bi_turn_angle(sn,speed/6, 10,1);
    }
  }
  return value;
}

int scan_angle_distance2(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int distance){
  float value,value_min;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  bi_turn_angle(sn, speed, angle, 1);
  FLAGS_T state;
  get_tacho_state_flags(sn[0],&state);
  value_min=3000;
  while ((value > distance || value == 0) && state){
    get_sensor_value0(sn_sonar, &value);
    get_tacho_state_flags(sn[0],&state);
    if (value<value_min && value!=0){
      value_min=value;
    }
  }
  stop_running(sn);
  if (value<value_min && value!=0){
    value_min=value;
  }
  if (value_min>distance){
    printf("There is not obstacle in the range %d , but I think the nearest thing is in range %f mm \n",distance,value_min);
  }
  else {
    printf("There is an obstacle in the range %d \n",distance);
    //Decalage pour etre en face de la balle 
    if(distance<300){
      bi_turn_angle(sn,speed/8, 19-0.05*distance,1);
    }
    if (distance>400){
      bi_turn_angle(sn,speed/8, 10,1);
    }
  }
  return value_min;
}

int is_it_the_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int speed, int distance){
  int val;
  while (distance>200){
    run_distance(sn,speed*3/4,150,0);
    bi_turn_angle(sn,speed/2,-40,0);
    if (scan_angle_distance2(sn,sn_sonar,speed/3,80,distance-140)>distance-150){
      bi_turn_angle(sn,speed/2,-40,0);
    }
    distance-=150;
  }
  door_mi_up_standard(sn3);
  run_distance(sn,speed,distance-5,0);
  if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
    val = 0;
  }
  bi_turn_angle(sn,speed/7,-60,1);
  // val_moy=val;
  for (int i=0; i<60; i++){
    if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
      val = 0;
    }
    //printf("color found : %s \n", color[val]);
    //val_moy+=val;
    Sleep(100);
    if (val==5){
      break;
    }
  }
  stop_running(sn);
  // val_moy=val_moy/21;
  if (val==5){
    printf("It is the ball !!! \n");
    return 1;
  }
  return 0;
}

void run_back_no_ball(uint8_t *sn, uint8_t sn3, int speed){
  run_distance(sn,speed,-150,0);
  door_mi_down_standard(sn3);
}

void door_up_down( uint8_t sn3, int speed ){
  door_up(sn3,speed);
  Sleep(1000);
  door_down(sn3,speed);
}

void release_ball(uint8_t *sn, uint8_t sn3, int speed, int distance){
  run_distance(sn,speed/5,40,0);
  Sleep(2000);
  door_up_standard(sn3);
  run_distance(sn,speed,distance,0);
  door_down_standard(sn3);
}

int scan (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color,int speed_scan, int speed_catch, int limit_distance){
  int val=scan_angle_distance(sn, sn_sonar, speed_scan, 410, limit_distance/3);
  if (val>limit_distance/3){
    val=scan_angle_distance(sn, sn_sonar, speed_scan, 410, limit_distance*2/3);
  }
  if (val>limit_distance*2/3){
    val=scan_angle_distance(sn, sn_sonar, speed_scan, 410, limit_distance);
  }
  return catch_if_ball(sn,sn3,sn_sonar,sn_color,speed_catch,val,limit_distance);
}

int scan2 (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color,int speed_scan, int speed_catch, int limit_distance){
  int val=scan_angle_distance2(sn, sn_sonar, speed_scan, 410, limit_distance/2);
  if (val < limit_distance){
    val=scan_angle_distance2(sn, sn_sonar, speed_scan, 410, limit_distance+50);
  }
  return catch_if_ball(sn,sn3,sn_sonar,sn_color,speed_catch,val,limit_distance);
}

int catch_if_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int speed_catch, int distance_to_object, int limit_distance){
  if (distance_to_object<limit_distance){
    if (is_it_the_ball(sn,sn3,sn_sonar,sn_color,speed_catch,distance_to_object)){
      printf("I think the ball is here !! \n ");
      catch_ball_after_check(sn,sn3,speed_catch);
      return 1;
    }
    else {
      printf("It is not the ball --' \n");
      run_back_no_ball(sn,sn3,speed_catch);
      return 2;
    }
  }
  printf("I don't see anything %d mm in front of me \n", limit_distance);
  return 0;
}
