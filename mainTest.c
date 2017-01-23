#include "basic_include.h"
#include "final.h"
#include "mainTest.h"
#include "catapult.h"
#include "color.h"
#include "sonar.h"
#include "bluetooth.h"
#include <string.h>

#define DISTANCE_SQUARE 300
#define SLEEP_TIME 1800

int main( int argc, char *argv[] ){
  int error,i,s,dest;
  char choice[20];
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color,sn_compass,sn_gyro;
  uint8_t sn[2];
  if (argc<3){
    printf("[X] Wrong usage of the function ! use it like that : ./mainTest movement 1\n");
    return 0;
  }
  int choice_parameters[argc-2];
  init_all(&sn1,&sn2,&sn3,&sn4,&sn_sonar,&sn_color,&sn_compass,&sn_gyro,sn,&s);
  error=1;
  strncpy(choice,argv[1],20);
  dest=1;
  for(i=2;i<argc;i++){
    choice_parameters[i-2] = atoi(argv[i]);
  }
  if (!strcmp(choice,"stop")){
    set_tacho_stop_action_inx(sn3,TACHO_COAST);
    //uninit(&sn3,&sn4);
    stop_running(sn);
    error=0;
  }
  if (!strcmp(choice,"catapult")){
    test_catapult(sn4,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"color")){
    test_color(sn_color,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"sonar")){
    test_sonar(sn_sonar,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"turn")){
    test_turn(sn,sn_sonar,sn_compass,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"compass")){
    test_compass(sn_compass,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"grab")){
    test_grab(sn,sn3,sn_sonar,sn_color,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"movement")){
    test_movement(sn,sn_sonar,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"movementgrab")){
    test_movement_grab(sn,sn3,sn_sonar,sn_color,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"bluetooth")){
    test_bluetooth(sn,sn3,sn_sonar,sn_color,&s,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"gyro")){
    test_gyro(sn,sn3,sn_sonar,sn_color,sn_gyro,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"smallbeg")){
    create_thread_print_coordinates();
    if (choice_parameters[0]==1){
      set_position(1100,300);
      set_side_angle(0);
      while (1){
        small_arena_beginner(sn,sn3,sn_sonar,sn_color,s,dest);
      }
    }
    if (choice_parameters[0]==2){
      set_position(1100,300);
      set_side_angle(0);
      put_small_beg(sn,sn3,sn_sonar,s,dest);
    }
    if (choice_parameters[0]==3){
      set_position(1100,1900);
      set_side_angle(180);
      get_small_beg(sn,sn3,sn_sonar,sn_color,s,dest);
    }
    error=0;
  }
  if (!strcmp(choice,"smallfin")){
    create_thread_print_coordinates();
    if (choice_parameters[0]==1){
      set_position(100,1700);
      set_side_angle(180);
      while(1){
        small_arena_finisher(sn,sn3,sn_sonar,sn_color,s,dest);
      }
    }
    if (choice_parameters[0]==2){
      set_position(100,1700);
      set_side_angle(180);
      get_small_fin(sn,sn3,sn_sonar,sn_color,s,dest);
    }
    if (choice_parameters[0]==3){
      set_position(100,300);
      set_side_angle(0);
      put_small_fin(sn,sn3,sn_sonar,s,dest);
    }
    error=0;
  }
  if (!strcmp(choice,"bigbeg")){
    create_thread_print_coordinates();
    big_arena_beginner(sn,sn3,sn_sonar,choice_parameters[0],s,dest);
    error=0;
  }
  if (!strcmp(choice,"bigfin")){
    create_thread_print_coordinates();
    big_arena_finisher(sn,sn3,sn4,sn_sonar,sn_color,choice_parameters[0],s,dest);
    error=0;
  }
  if (error) printf("[X] error %s is not a right command :/ \n",choice);
  uninit(&sn3,&sn4);
}

void test_catapult(uint8_t sn, int *choice_parameters){
  if (choice_parameters[0]==1){
    throw(sn);
    throw_pos(sn,1000,130);
  }
}

void test_color(uint8_t sn_color, int *choice_parameters){
  for ( ; ; ){
    if (choice_parameters[0]==1){
      print_RGB(sn_color);
    }
    else
      print_color(sn_color);
  }
}

void test_compass(uint8_t sn_compass, int *choice_parameters){
  float value;
  while (1)  {
    //printf("Robot angle is : %f \n",robot_angle);
    if (choice_parameters[0]==1){
      print_robot_rel_angle();
      print_robot_abs_angle();
      Sleep(2000);
    }
    if (choice_parameters[0]==2){
      print_robot_abs_angle();
      Sleep(2000);
    }
    if (choice_parameters[0]==3){
      if ( !get_sensor_value0(sn_compass, &value)) {
        value = 0;
      } 
      printf("robot angle from north : %f \n ", value);
      Sleep(2000);
    }
  }
}

void test_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters){
  if (choice_parameters[0]==1){
    if (scan(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/4,SONAR_DISTANCE )== 2){
      bi_turn_angle2(sn,sn_sonar,MAX_SPEED/4,40,1);
      scan(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/4,SONAR_DISTANCE);  
    }
  } 
  if (choice_parameters[0]==2){
    if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
      bi_turn_angle2(sn,sn_sonar,MAX_SPEED/4,40,1);
      scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    }
  }
  if (choice_parameters[0]==3){
    release_ball(sn,sn_sonar,sn3,MAX_SPEED/4,choice_parameters[1],choice_parameters[2],12,12);
  }
  if (choice_parameters[0]==4){
    get_ball(sn,sn3,sn_sonar,sn_color);
  }
}

void first_course(uint8_t *sn, uint8_t sn_sonar, int speed,int turn_speed, int distance){
  create_thread_print_coordinates();
  for (int i=0;i<4;i++){
    printf("[A] I am running for %d mm  \n", distance);
    run_distance_unless_obstacle(sn, sn_sonar, speed, distance);

    printf("[A] I am gonna turn left \n");
    bi_turn_angle_ramp(sn,sn_sonar, turn_speed, -90,distance,500, 0);
    Sleep(1000);
  }
}

void test_movement(uint8_t *sn, uint8_t sn_sonar, int *choice_parameters){
  if (choice_parameters[0]==1){
    first_course(sn,sn_sonar,choice_parameters[1],TURN_SPEED,DISTANCE_SQUARE);
  }
  if (choice_parameters[0]==3){
    int speed=choice_parameters[2];
    while (speed<MAX_SPEED){
      run_distance(sn,sn_sonar,speed,choice_parameters[1],0);
      Sleep(SLEEP_TIME);
      speed+=20;
    }
  }
  if (choice_parameters[0]==21){
    go_to_position1(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,choice_parameters[3],0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,0,2*choice_parameters[2],MAX_SPEED/2,TURN_SPEED,choice_parameters[3],0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,choice_parameters[3],0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,0,0,MAX_SPEED/2,TURN_SPEED,choice_parameters[3],0);
    Sleep(3000);
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
  if (choice_parameters[0]==22){
    go_to_position2(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,0,2*choice_parameters[2],MAX_SPEED/2,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,0,0,MAX_SPEED/2,TURN_SPEED,0);
    Sleep(3000);
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
}

void test_sonar(uint8_t sn_sonar, int *choice_parameters){
  if (choice_parameters[0]==1){
    while(true){
      print_sonar(sn_sonar);
      Sleep(1000);
    }
  }
}

void test_turn(uint8_t *sn, uint8_t sn_sonar, uint8_t sn_compass, int *choice_parameters){
  if (choice_parameters[0]==1){
    for (int i=0; i<8; i++){
      Sleep(SLEEP_TIME);
      //print_robot_abs_angle();
      print_robot_rel_angle();
      Sleep(SLEEP_TIME);
      if (choice_parameters[1]==1){
        bi_turn_angle(sn,sn_sonar,TURN_SPEED,90,0);
      }
      else {
        bi_turn_angle2(sn,sn_sonar,TURN_SPEED,90,0);
      }
      Sleep(SLEEP_TIME);
    }
  }
  if (choice_parameters[0]==2){
    turn_to_angle(sn,sn_sonar,TURN_SPEED,90,1,0);
    Sleep(SLEEP_TIME);
    print_robot_rel_angle();
    turn_to_angle(sn,sn_sonar,TURN_SPEED,180,1,0);
    Sleep(SLEEP_TIME);
    print_robot_rel_angle();
    turn_to_angle(sn,sn_sonar,TURN_SPEED,270,1,0);
    Sleep(SLEEP_TIME);
    print_robot_rel_angle();
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
    Sleep(SLEEP_TIME);
    print_robot_rel_angle();
  }
  if (choice_parameters[0]==3){
    int turn_speed;
    turn_speed=choice_parameters[2];
    while (turn_speed<= MAX_SPEED){
      printf("[I] turn speed: %d \n",turn_speed);
      bi_turn_pos_ramp(sn,sn_sonar,turn_speed,choice_parameters[1]*RIGHT_ANGLE/360,1500,1500,0);
      Sleep(SLEEP_TIME);
      turn_speed+=choice_parameters[3];
    }
  }
  if (choice_parameters[0]==4){
    turn_to_angle(sn,sn_sonar,choice_parameters[2],choice_parameters[1],1,0);
  }
}

void test_movement_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters){
  if (choice_parameters[0]==1){
    go_to_position1(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,choice_parameters[3],1);
    if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
      scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    }
  }
}

void test_gyro(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, uint8_t sn_gyro, int *choice_parameters){
  float value0;
  if (choice_parameters[0]==1){
    while (1){
      if (!get_sensor_value0(sn_gyro,&value0)){
        value0=0;
      }
      if (value0<0) value0+=360;
      printf("[I] angle read : %f \n",value0);
      print_robot_rel_angle();
      printf("\n");
      Sleep(2000);
    }
  }
}
