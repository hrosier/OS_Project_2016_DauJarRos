#include "basic_include.h"
#include "movement.h"
#include "turn.h"
#include "grab.h"

#define DOOR_POS 100
#define DOOR_SPEED 550
#define RAMP_UP 500
#define RAMP_DOWN 500

void door_ramp(uint8_t sn3, int position, int speed, int ramp_up, int ramp_down) {
  set_tacho_position_sp( sn3, position );
  set_tacho_speed_sp( sn3, speed);
  set_tacho_ramp_up_sp( sn3, ramp_up );
  set_tacho_ramp_down_sp( sn3, ramp_down );
  set_tacho_stop_action_inx( sn3, TACHO_HOLD );
  set_tacho_command_inx( sn3, TACHO_RUN_TO_REL_POS );
  Sleep(2000);
  //Block the door in order to prevent it to move due to the ball
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

void door_up_down( uint8_t sn3, int speed ){
  door_up(sn3,speed);
  Sleep(1000);
  door_down(sn3,speed);
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

void catch_dist(uint8_t *sn, uint8_t sn_sonar, uint8_t sn3, int speed, int distance){
  //Open the door
  door_up_standard(sn3);
  Sleep(1000);
  // Go foward a little
  run_distance(sn,sn_sonar,speed,distance,0);
  // close the door 
  door_down_standard(sn3);
  Sleep(1000);
}

void catch_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar,int speed){
  float value=0;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  catch_dist(sn,sn_sonar,sn3,speed,value+30);
}

void catch_ball_after_check(uint8_t *sn, uint8_t sn_sonar, uint8_t sn3,int speed){
  run_distance(sn,sn_sonar,speed,100,0);
  door_mi_down_standard(sn3);
}

void release_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int speed, int distance, int front_or_back, int s, int dest){
  run_distance(sn,sn_sonar,speed/5,front_or_back*40,0);
  Sleep(2000);
  door_up_standard(sn3);
  send_message(s,7,dest,0);
  run_distance(sn,sn_sonar,speed,front_or_back*distance,0);
  door_down_standard(sn3);
}

void run_back_no_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int speed){
  run_distance(sn,sn_sonar,speed,-150,0);
  door_mi_down_standard(sn3);
}

int scan_angle_distance(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int distance){
  FLAGS_T state;
  float value;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  bi_turn_angle(sn,sn_sonar, speed, angle, 2);
  // The robot turns until it finds something within "distance"mm or it finishes turning "angle" degrees
  get_tacho_state_flags(sn[0],&state);
  while ((value > distance || value == 0) && state){
    get_sensor_value0(sn_sonar, &value);
    get_tacho_state_flags(sn[0],&state);
  }
  stop_running(sn);
  if (value>distance){
    printf("[I,scan1] There is not obstacle in the range %d \n",distance);
  }
  else {
    printf("[I,scan1] There is an obstacle in the range %d \n",distance);
    // Usually when the robot found the ball it is not precisly in front of it (it runs too fast or the sonar has some delay)
    // So we make it turn a little
    if(distance<300){
      bi_turn_angle(sn,sn_sonar,speed/6, 20-0.06*distance,0); // the angle was experimentaly estimated
    }
    if (distance>400){
      bi_turn_angle(sn,sn_sonar,speed/6, 10,0); // this angle was experimentaly estimated
    }
  }
  return value;
}

int scan_angle_distance2(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int distance){
  float value,value_min;
  FLAGS_T state;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  bi_turn_angle(sn,sn_sonar, speed, angle, 2);
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
    printf("[I,scan2] There is not obstacle in the range %d , but I think the nearest thing is in range %f mm \n",distance,value_min);
  }
  else {
    printf("[I,scan2] There is an obstacle in the range %d \n",distance);
    // Usually when the robot found the ball it is not precisly in front of it (it runs too fast or the sonar has some delay)
    // So we make it turn a little
    if(distance<300){
      bi_turn_angle(sn,sn_sonar,speed/8, 19-0.05*distance,1); // the angle was experimentaly estimated
    }
    if (distance>400){
      bi_turn_angle(sn,sn_sonar,speed/8, 10,1); // the angle was experimentaly estimated
    }
  }
  return value_min;
}

int is_it_the_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int speed, int distance){
  int val;
  printf("[I,checkBall] I check if it is the ball at %dmm\n",distance);
  /////// The robot gets near the ball ////////
  while (distance>300){
    // the robot run a little
    run_distance(sn,sn_sonar,speed*3/4,150,0);
    distance-=150;
    // Do another scan to be in font of the ball
    bi_turn_angle(sn,sn_sonar,speed/2,-50,0);
    if (scan_angle_distance(sn,sn_sonar,speed/3,80,distance+10)>distance){
      // If the robot don't find the ball, he returns to its previous position, turn 30° and re-do a scan
      bi_turn_angle(sn,sn_sonar,speed/2,-30,0);
      run_distance(sn,sn_sonar,speed*3/4,-100,0);
      distance+=100;
      bi_turn_angle(sn,sn_sonar,speed/2,30,0);
    }
  }
  ////// The robot is now in front of the obstacle, it checks if it is the ball //////
  // It opens it doors a little
  door_mi_up_standard(sn3);
  // It places the color sensor above the ball
  run_distance(sn,sn_sonar,speed,distance,0);
  if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
    val = 0;
  }
  // it scans in front of him until it turns 60° or he finds the ball
  bi_turn_angle(sn,sn_sonar,speed/7,-60,2);
  for (int i=0; i<60; i++){
    if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
      val = 0;
    }
    Sleep(100);
    if (val==5){
      break;
    }
  }
  stop_running(sn);
   if (val==5){
    printf("It is the ball !!! \n");
    return 1;
  }
  return 0;
}

int scan (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color,int speed_scan, int speed_catch, int limit_distance){
  // The robot scan for near objects
  int val=scan_angle_distance(sn, sn_sonar, speed_scan, 410, limit_distance/3);
  if (val>limit_distance/3){
    // The robot scan for middle range object
    val=scan_angle_distance(sn, sn_sonar, speed_scan, 410, limit_distance*2/3);
  }
  if (val>limit_distance*2/3){
    // The robot scan for far object
    val=scan_angle_distance(sn, sn_sonar, speed_scan, 410, limit_distance);
  }
  if (val<limit_distance) return catch_if_ball(sn,sn3,sn_sonar,sn_color,speed_catch,val,limit_distance);
  printf("[I,scan1] I didn't find anything\n");
  return 0;
}

int scan2 (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color,int speed_scan, int speed_catch, int limit_distance){
  // the robot scans to find the nearest object
  int val=scan_angle_distance2(sn, sn_sonar, speed_scan, 410, limit_distance/3);
  if (val > limit_distance/3 && val < limit_distance){
    // The robot turn to be in front the nearest object
    val=scan_angle_distance2(sn, sn_sonar, speed_scan, 410, val+50);
  }
  if (val<limit_distance) return catch_if_ball(sn,sn3,sn_sonar,sn_color,speed_catch,val,limit_distance);
  printf("[I,scan2] I didn't find anything\n");
  return 0;
}

int catch_if_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int speed_catch, int distance_to_object, int limit_distance){
  if (distance_to_object<limit_distance){
    if (is_it_the_ball(sn,sn3,sn_sonar,sn_color,speed_catch,distance_to_object)){
      printf("[I,catch] I think the ball is here !! \n ");
      catch_ball_after_check(sn,sn_sonar,sn3,speed_catch);
      return 1;
    }
    else {
      printf("[I,catch] It is not the ball --' \n");
      run_back_no_ball(sn,sn_sonar,sn3,speed_catch);
      return 2;
    }
  }
  printf("[I,catch] don't see anything %d mm in front of me \n", limit_distance);
  return 0;
}

int get_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color){
  int count=0;
  // it seaches for the ball a first time
  int found=scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE);
  while (found != 1){
    // while the robot doesn't find the ball, he try an other place to scan and do another scan (if after the 6th scan we stop it..)
    bi_turn_angle2(sn,sn_sonar,MAX_SPEED/4,20,0);
    run_distance(sn,sn_sonar,MAX_SPEED,150,1);
    found=scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    if (count==5) break;
    count++;
  }
  if (found==1) return 1;
  else return 0;
}
