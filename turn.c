/* this file contains the functions used to deal with the rotation of the robot */
#include "basic_include.h"

#define RAMP_UP 1500
#define RAMP_DOWN 1500

// the position param correspond to the position_sp value of the motors
// (0 it doesn't do anything, 1 it stops, 2 the robot continue turning and the decision is decided after the call of the function)
void bi_turn_pos_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int position, int ramp_up, int ramp_down, char search_obstacle){
  // the max_speed the robot can turn depends of the distance it needs to run and the accelearation given.
  // We have experimentally found this max_speed for different distance  
  int angle = (int)( 360*position/RIGHT_ANGLE);
  int max_speed=MAX_SPEED ;
  if (abs(angle)<=25) max_speed = abs((int)(-0.4*angle*angle+22*abs(angle)+5));
  if (abs(angle)>25 && abs(angle)<120) max_speed = (int)(5*abs(angle)+150);
  if (max_speed>MAX_SPEED) max_speed=MAX_SPEED;
  speed=abs(speed);
  if (speed > max_speed) speed=max_speed;
  printf("[I] I gonna turn %d at speed : %d (max_speed:%d) \n",angle,speed,max_speed);

  tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_STOP);
  set_tacho_position_sp(sn[0], position);
  set_tacho_position_sp(sn[1], -position);
  multi_set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);

  if (search_obstacle==0) continue_until_stop_running(sn);
  if (search_obstacle==1) check_for_obstacle(sn,sn_sonar,MOVEMENT_DISTANCE_SONAR);
}  

void bi_turn_angle_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int ramp_up, int ramp_down, char search_obstacle){
  bi_turn_pos_ramp(sn,sn_sonar,speed,angle*RIGHT_ANGLE/360,ramp_up,ramp_down,search_obstacle);
}

void bi_turn_angle(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, char search_obstacle){
  bi_turn_angle_ramp(sn,sn_sonar,speed,angle,RAMP_UP,RAMP_DOWN,search_obstacle);
}

void bi_standard_turn_angle(uint8_t *sn, uint8_t sn_sonar, int angle, char search_obstacle){
  bi_turn_angle(sn,sn_sonar,TURN_SPEED,angle,search_obstacle);
  // We experimentaly find that the robot needs to sleep a little after turning if not it may not run straight
  int time_to_sleep = (int) abs(angle)*1.98+300;
  Sleep(time_to_sleep);
}

// This function compute the difference between 2 angles. It takes into account the fact that the angles are modulo 360. 
int angle_diff(int angle1, int angle2){
  if (angle1>angle2) {
    int tmp=angle2;
    angle2=angle1;
    angle1=tmp;
  }
  int diff1=angle2-angle1;
  int diff2=360+angle1-angle2;
  if (diff1>diff2) return diff2;
  return diff1;
}

// this function makes the robot turn to a specific absolute (rel=0) or relative (rel!=0) angle 
void turn_to_angle(uint8_t *sn, uint8_t sn_sonar, int initial_speed, int angle, char rel, char search_obstacle){
  int diff, speed;
  float robot_angle_tmp;
  speed=initial_speed;
  // the robot turns to the specific absolute (rel=0) or relative (rel!=0) angle 
  if (rel){
    robot_angle_tmp=get_robot_rel_angle();
    printf("[I,turn] I want to turn to the rel angle %d, and my rel angle is %f\n",angle,robot_angle_tmp);
  }
  else {
    robot_angle_tmp=get_robot_abs_angle();
  }

  diff=angle_diff(robot_angle_tmp,angle);
  while (diff>3){
    if (robot_angle_tmp>angle){
      if (diff<abs(angle+360-robot_angle_tmp)){
        //printf("[D,turn] 1: i am gonna turn for : %d \n", -diff);
        bi_turn_angle(sn,sn_sonar,speed,-diff,search_obstacle);
      }
      else {
        //printf("[D,turn] 2: i am gonna turn for : %d \n", (int)(360-robot_angle_tmp+angle));
        bi_turn_angle(sn,sn_sonar,speed,(int)(360-robot_angle_tmp+angle),search_obstacle);
      }
    }
    else {
      if (diff<abs(robot_angle_tmp+360-angle)){
        //printf("[D,turn] 3: i am gonna turn for : %d \n", diff);
        bi_turn_angle(sn,sn_sonar,speed,diff,search_obstacle);
      }
      else {
        //printf("[D,turn] 4: i am gonna turn for : %d \n", (int)(-360-robot_angle_tmp+angle));
        bi_turn_angle(sn,sn_sonar,speed,(int)(-robot_angle_tmp-(360-angle)),search_obstacle);
      }
    }

    Sleep(200);
    if (rel){
      robot_angle_tmp=get_robot_rel_angle();
      //printf("[D,turn] Inside while : rel_angle : %f , dest angle :%d \n",robot_angle_tmp,angle);
    }
    else {
      robot_angle_tmp=get_robot_abs_angle();
    }
    diff=angle_diff(robot_angle_tmp,angle);
    // Reduce the speed to improve the accuracy of the second turn
    if (speed>100){
      speed=speed/2;
    }
  }
}




////////////////////////////////////    Unused functions  ///////////////////////////



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

void turn_timed_ramp(uint8_t sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, int time, int search_obstacle){
  set_tacho_time_sp( sn , time);
  mono_tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TIMED);
  if (search_obstacle==0) continue_until_stop_running(&sn);
  if (search_obstacle==1) check_for_obstacle(&sn,sn_sonar,MOVEMENT_DISTANCE_SONAR);
}

void turn_to_abs_pos_ramp(uint8_t sn, int speed, int ramp_up, int ramp_down){
  mono_tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TO_ABS_POS );
  continue_until_stop_running(&sn);

  //To be more accurate on the absolute position 
  for ( int i = 0; i < 2; i++ ) {
    set_tacho_command_inx( sn, TACHO_RUN_TO_ABS_POS );
    Sleep( 500 );
  }       
}

void turn_to_rel_pos_ramp(uint8_t sn, int pos,int speed, int ramp_up, int ramp_down){
  set_tacho_position_sp(sn, pos);
  mono_tacho_settings(sn, speed, ramp_up, ramp_down, TACHO_RUN_TO_REL_POS );
  //wait until the tacho finishes turning
  continue_until_stop_running(&sn);
}

void mono_check_for_obstacle(uint8_t sn_sonar, uint8_t sn){
  float value=0;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  //While no obstacle turn tacho 
  while (value>200 || value == 0){
    get_sensor_value0(sn_sonar, &value);
  }
  set_tacho_command_inx( sn, TACHO_STOP );
}


void bi_turn_angle2(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, char search_obstacle){
  int tmp_angle = get_robot_rel_angle();
  if (tmp_angle+angle>360){
    turn_to_angle(sn,sn_sonar,speed,tmp_angle+angle-360,1,search_obstacle);
  } else {
    turn_to_angle(sn,sn_sonar,speed,tmp_angle+angle,1,search_obstacle);
  }
}

void u_turn_right_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, char search_obstacle){
  bi_turn_pos_ramp(sn,sn_sonar, speed, RIGHT_ANGLE/2, ramp_up, ramp_down,search_obstacle);
}

void u_turn_left_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, char search_obstacle){
  bi_turn_pos_ramp(sn, sn_sonar, speed, -RIGHT_ANGLE/2, ramp_up, ramp_down,search_obstacle);
}

void bi_turn_pos(uint8_t *sn,uint8_t sn_sonar, int speed, int position, char search_obstacle){
  bi_turn_pos_ramp(sn, sn_sonar,speed, position, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void u_turn_right(uint8_t *sn, uint8_t sn_sonar,int speed, char search_obstacle){
  u_turn_right_ramp(sn,sn_sonar, speed, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void u_turn_left(uint8_t *sn, uint8_t sn_sonar, int speed, char search_obstacle){
  u_turn_left_ramp(sn,sn_sonar, speed, RAMP_UP, RAMP_DOWN, search_obstacle);
}

void turn_forever_unless_obstacle_ramp(uint8_t sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down){
  turn_forever_ramp(sn, speed, ramp_up, ramp_down);
  mono_check_for_obstacle(sn_sonar, sn);
}

void turn_timed_unless_obstacle_ramp(uint8_t sn, uint8_t sn_sonar ,int speed ,int ramp_up, int ramp_down, int time){
  turn_timed_ramp(sn,sn, speed, ramp_up, ramp_down, time, 0); // the second sn is useless but doesnt create bug 
  mono_check_for_obstacle(sn_sonar, sn);
}

void turn_forever(uint8_t sn, int speed){
  turn_forever_ramp(sn, speed, RAMP_UP, RAMP_DOWN);
}

void turn_timed(uint8_t sn, uint8_t sn_sonar, int speed, int time){
  turn_timed_ramp(sn,sn_sonar, speed, RAMP_UP, RAMP_UP, time, 1);
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
