#include "basic_include.h"
#include <math.h>
#include "movement.h"

#define SLEEP_TIME 800

void stop_running(uint8_t *sn){
  multi_set_tacho_command_inx( sn , TACHO_STOP);
}

void tacho_settings(uint8_t *sn, int speed, int ramp_up, int ramp_down, INX_T FLAGS){
  int max_speed=0;
  // Check if the robot can run at this speed
  get_tacho_max_speed(sn[0], &max_speed);
  if (speed > max_speed ){
    printf("the robot can not run this fast (%d), its max speed is %d  \n", speed, max_speed );
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

void run_timed_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, int time, int search_obstacle){
  multi_set_tacho_time_sp( sn , time);
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TIMED);

  if (search_obstacle==0){
    // Wait until the robot finishes running
    continue_until_stop_running(sn);
  }
  else {
    check_for_obstacle(sn,sn_sonar,MOVEMENT_DISTANCE_SONAR);
  }
}

void run_to_abs_pos_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, int search_obstacle){
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TO_ABS_POS);
  if(search_obstacle==0){
    continue_until_stop_running(sn);
  }
  else {
    check_for_obstacle(sn,sn_sonar,MOVEMENT_DISTANCE_SONAR);
  }
}

void run_to_rel_pos_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int position, int ramp_up, int ramp_down, int search_obstacle){
  multi_set_tacho_position_sp(sn, position);
  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TO_REL_POS);
  if(search_obstacle==0){
    continue_until_stop_running(sn);
  } 
  else {
    check_for_obstacle(sn,sn_sonar,MOVEMENT_DISTANCE_SONAR);
  }
}

void check_for_obstacle(uint8_t *sn, uint8_t sn_sonar, int distance){
  float value=0;
  FLAGS_T state;
  get_tacho_state_flags(sn[0],&state);
  do {
    if ( !get_sensor_value0(sn_sonar, &value )) {
      value = 0;
    }
    //While no obstacle run tacho 
    get_sensor_value0(sn_sonar, &value);
    get_tacho_state_flags(sn[0],&state);
  } while ((value>distance  || value == 0 ) && state);
  multi_set_tacho_command_inx( sn, TACHO_STOP );
  if (value<=distance){
    printf("There is an obstacle at %f mm \n", value);
  }
  Sleep(SLEEP_TIME);
}

void run_forever_unless_obstacle_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down){
  run_forever_ramp(sn, speed, ramp_up, ramp_down);
  check_for_obstacle(sn, sn_sonar, MOVEMENT_DISTANCE_SONAR);
}

void run_timed_unless_obstacle_ramp(uint8_t *sn, uint8_t sn_sonar ,int speed ,int ramp_up, int ramp_down, int time){
  run_timed_ramp(sn,sn_sonar,speed, ramp_up, ramp_down, time, 1);
}

void run_forever(uint8_t *sn, int speed){
  run_forever_ramp(sn, speed, MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN);
}

void run_timed(uint8_t *sn, uint8_t sn_sonar, int speed, int time, char check_for_obstacle){
  run_timed_ramp(sn,sn_sonar, speed, MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN, time, check_for_obstacle);
}

void run_forever_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed){
  run_forever_unless_obstacle_ramp(sn, sn_sonar, speed, MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN);
}

void run_timed_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed, int time){
  run_timed_unless_obstacle_ramp(sn, sn_sonar, speed, MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN, time);
}

void run_to_abs_pos(uint8_t *sn, uint8_t sn_sonar, int speed, int search_obstacle){
  run_to_abs_pos_ramp(sn, sn_sonar, speed, MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN, search_obstacle);
}

void run_to_rel_pos(uint8_t *sn, uint8_t sn_sonar, int speed, int position, int search_obstacle){
  run_to_rel_pos_ramp(sn,sn_sonar,speed,position,MOVEMENT_RAMP_UP,MOVEMENT_RAMP_DOWN,search_obstacle);
}

void run_distance(uint8_t *sn, uint8_t sn_sonar, int speed, int distance, int search_obstacle){
  int max_speed=MAX_SPEED;
  //the robot can't run too fast if the distance is small
  if (abs(distance)<100) max_speed=-0.026*distance*distance+6.67*abs(distance)+80;
  if (abs(distance)>=100 && distance<300) max_speed=-0.0071*distance*distance+4.63*abs(distance)+104;
  if (max_speed>MAX_SPEED) max_speed=MAX_SPEED;
  if (speed>max_speed) speed=max_speed;
  printf("[I,movement] I am going to run %dmm at %d (max_speed:%d)\n",distance,speed,max_speed);
  run_to_rel_pos_ramp(sn,sn_sonar, speed, distance*DISTANCE_TO_POSITION, MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN, search_obstacle);
}

void run_distance_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int distance, int ramp_up, int ramp_down, int search_obstacle){
  run_to_rel_pos_ramp(sn,sn_sonar, speed, distance*DISTANCE_TO_POSITION, ramp_up, ramp_down, search_obstacle);
}

void run_distance_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed, int distance){
  run_to_rel_pos_ramp(sn,sn_sonar, speed, distance*DISTANCE_TO_POSITION, MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN, 1);
  check_for_obstacle(sn, sn_sonar, MOVEMENT_DISTANCE_SONAR);
}

void continue_until_stop_running(uint8_t *sn){
  FLAGS_T state;
  do {
    get_tacho_state_flags( sn[0], &state );
  } while ( state );
}

/** the robot go diagonaly to the destination 
 */
void go_to_position1(uint8_t *sn, uint8_t sn_sonar, int dest_pos_x, int dest_pos_y, int speed, int turn_speed, int number_try, char check_for_obstacle){
  if (number_try>0){
    int prev_pos_x, prev_pos_y, distance, dest_angle;
    prev_pos_x=get_x_position();
    prev_pos_y=get_y_position();
    distance=(int)sqrt(pow((dest_pos_x-prev_pos_x),2)+pow(dest_pos_y-prev_pos_y,2));
    // Not optimal but I forget a little how arctan works and I don't want to search ...
    dest_angle=(int)RAD_TO_DEG*atan((float)abs(dest_pos_x-prev_pos_x)/(float)abs(dest_pos_y-prev_pos_y));
    //printf("[D] Avant corection prev_x : %d, prev_y : %d, dest_x : %d dest_y : %d, distance : %d, angle : %d \n",prev_pos_x,prev_pos_y,dest_pos_x,dest_pos_y,distance,dest_angle);
    if (dest_pos_x<prev_pos_x && dest_pos_y<prev_pos_y) dest_angle+=180;
    if (dest_pos_x>prev_pos_x && dest_pos_y<prev_pos_y) dest_angle+=90;
    if (dest_pos_x<prev_pos_x && dest_pos_y>prev_pos_y) dest_angle+=270;

    printf("[I,goto2] I am at (%d,%d) and I go to (%d,%d) by running %dmm with an angle of %d \n",prev_pos_x,prev_pos_y,dest_pos_x,dest_pos_y,distance,dest_angle);
    //TODO: know if we use turn1 or turn2
    turn_to_angle(sn,sn_sonar,turn_speed,dest_angle,1,check_for_obstacle);
    //bi_turn_angle2(sn,sn_sonar,turn_speed,dest_angle,check_for_obstacle);
    run_distance(sn,sn_sonar,speed,distance,check_for_obstacle);
    //correct_position(sn,sn_sonar,speed,dest_pos_x,dest_pos_y,check_for_obstacle);
    printf("[I,goto2] I arrive at position (%d,%d) \n",get_x_position(),get_y_position());
    if (number_try >1 && (abs(get_x_position()-dest_pos_x)>POSITION_PRECISION || abs(get_y_position()-dest_pos_y)>POSITION_PRECISION) )
      go_to_position1(sn,sn_sonar,dest_pos_x,dest_pos_y,speed/2,turn_speed*3/4,number_try-1,check_for_obstacle);
  }
}

void correct_position(uint8_t *sn, uint8_t sn_sonar, int speed,int dest_pos_x,int dest_pos_y, char check_for_obstacle){
  //Correction to improve accuracy
  int diff_x = get_x_position()- dest_pos_x;
  int tmp_angle = (double)get_robot_angle(1);
  int distance_x, distance_y;
  distance_x = (int)(abs(sin(tmp_angle))*diff_x);
  printf("[D] 0\n");
  if (distance_x>DISTANCE_LIMIT){
    printf("[D] 1\n");
    if (diff_x>POSITION_PRECISION){
      printf("[D] 21\n");
      if (tmp_angle>180) {
        printf("[D] 31\n");
        run_distance(sn,sn_sonar,speed/3,-distance_x,check_for_obstacle);
      }
      else {
        printf("[D] 31\n");
        run_distance(sn,sn_sonar,speed/3,distance_x,check_for_obstacle);
      }
    }
    if (diff_x<-POSITION_PRECISION){
      printf("[D] 21\n");
      if (tmp_angle>180){
      printf("[D] 31\n");
        run_distance(sn,sn_sonar,speed/3,-distance_x,check_for_obstacle);
      }
      else {
      printf("[D] 31\n");
        run_distance(sn,sn_sonar,speed/3,distance_x,check_for_obstacle);
      }
    }
  }
  printf("[D] diff_x : %d, diff now : %d\n", diff_x, get_x_position()-dest_pos_x);
  int diff_y = get_y_position()- dest_pos_y;
  distance_y = (int)(abs(cos(tmp_angle))*diff_y);
  if (distance_y>DISTANCE_LIMIT){
    if (diff_y>POSITION_PRECISION){
      if (tmp_angle>270 || tmp_angle<90){
        run_distance(sn,sn_sonar,speed/3,-distance_y,check_for_obstacle);
      }
      else {
        run_distance(sn,sn_sonar,speed/3,distance_y,check_for_obstacle);
      }
      if (diff_y<-POSITION_PRECISION){
        if (tmp_angle>270 || tmp_angle<90) {
          run_distance(sn,sn_sonar,speed/3,-distance_y,check_for_obstacle);
        }
        else{ 
          run_distance(sn,sn_sonar,speed/3,distance_y,check_for_obstacle);
        }
      }
    }
  }
  printf("[D] diff_y : %d, diff now : %d\n", diff_y, get_y_position()-dest_pos_y);
}

/** the robot go only horizontaly to the destination 
 *
 */
void go_to_position2(uint8_t *sn, uint8_t sn_sonar, int dest_pos_x, int dest_pos_y, int speed, int turn_speed, char check_for_obstacle){
  int prev_pos_x, prev_pos_y;
  prev_pos_x=get_x_position();
  prev_pos_y=get_y_position();
  printf("[D] I am at (%d,%d) and I am going to (%d, %d)\n",prev_pos_x,prev_pos_y,dest_pos_x,dest_pos_y);
  if (dest_pos_x!=prev_pos_x){
    if (dest_pos_x>prev_pos_x){
      turn_to_angle(sn,sn_sonar,turn_speed,90,1,check_for_obstacle);
      run_distance(sn,sn_sonar,speed,(dest_pos_x-prev_pos_x),check_for_obstacle);
    }
    else {
      turn_to_angle(sn,sn_sonar,turn_speed,270,1,check_for_obstacle);
      run_distance(sn,sn_sonar,speed,-(dest_pos_x-prev_pos_x),check_for_obstacle);
    }
  }
  if (dest_pos_y!=prev_pos_y){
    if (dest_pos_y>prev_pos_y){
      turn_to_angle(sn,sn_sonar,turn_speed,0,1,check_for_obstacle);
      run_distance(sn,sn_sonar,speed,(dest_pos_y-prev_pos_y),check_for_obstacle);
    }
    else {
      turn_to_angle(sn,sn_sonar,turn_speed,180,1,check_for_obstacle);
      run_distance(sn,sn_sonar,speed,-(dest_pos_y-prev_pos_y),check_for_obstacle);
    }
  }
  correct_position(sn,sn_sonar,speed,dest_pos_x,dest_pos_y,check_for_obstacle);
  printf("[D] I arrive at position (%d,%d) \n",get_x_position(),get_y_position());
}
