#include "basic_include.h"
#include "mainTest.h"
#include "catapult.h"
#include "color.h"
#include "sonar.h"
#include <string.h>

#define DISTANCE_SQUARE 300
#define SLEEP_TIME 1800

int main( int argc, char *argv[] ){
  int error,i;
  char choice[20];
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color,sn_compass;
  uint8_t sn[2];

  if (argc<3){
    printf("[X] Wrong usage of the function ! use it like that : ./mainTest movement 1\n");
    return 0;
  }
  int choice_parameters[argc-2];

  init_all(&sn1,&sn2,&sn3,&sn4,&sn_sonar,&sn_color,&sn_compass,sn);
  error=1;
  strncpy(choice,argv[1],20);
  for(i=2;i<argc;i++){
    choice_parameters[i-2] = atoi(argv[i]);
  }
  if (!strcmp(choice,"stop")){
    uninit(&sn3,&sn4);
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
    test_turn(sn,sn_sonar,sn_compass,TURN_SPEED,choice_parameters);
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
      scan(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/4,SONAR_DISTANCE);  
    }
  } 
  if (choice_parameters[0]==2){
    if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
      scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    }
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
  int speed, turn_speed;
  speed = MAX_SPEED/3;
  turn_speed = MAX_SPEED/5;
  printf("[I] Turn speed : %d \n",turn_speed);
  if (choice_parameters[0]==1){
    first_course(sn,sn_sonar,speed,turn_speed,DISTANCE_SQUARE);
  }
  if (choice_parameters[0]==3){
    //run_distance(sn,sn_sonar,MAX_SPEED/3,-100,0);
    run_distance(sn,sn_sonar,MAX_SPEED/3,-20,0);
    Sleep(SLEEP_TIME);
    run_distance(sn,sn_sonar,-MAX_SPEED/3,10,0);
  }
  if (choice_parameters[0]==21){
    go_to_position1(sn,sn_sonar,200,200,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,0,400,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,200,200,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,0,0,MAX_SPEED/3,TURN_SPEED,0);
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
  if (choice_parameters[0]==22){
    go_to_position2(sn,sn_sonar,200,200,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,0,400,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,200,200,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,0,0,MAX_SPEED/3,TURN_SPEED,0);
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

void test_turn(uint8_t *sn, uint8_t sn_sonar, uint8_t sn_compass, int turn_speed, int *choice_parameters){
  if (choice_parameters[0]==1){
    for (int i=0; i<8; i++){
      Sleep(SLEEP_TIME);
      //print_robot_abs_angle();
      print_robot_rel_angle();
      Sleep(SLEEP_TIME);
      if (choice_parameters[0]==1){
        bi_turn_angle(sn,sn_sonar,turn_speed,90,0);
      }
      else {
        bi_turn_angle2(sn,sn_sonar,turn_speed,90,0);
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
    turn_speed=choice_parameters[2];
    while (turn_speed<= TURN_SPEED){
      printf("[I] turn speed: %d \n",turn_speed);
      bi_turn_pos_ramp(sn,sn_sonar,turn_speed,choice_parameters[1]*RIGHT_ANGLE/360,1500,1500,0);
      Sleep(SLEEP_TIME);
      turn_speed+=choice_parameters[3];
    }
  }
}

void test_movement_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters){
  if (choice_parameters[0]==1){
    go_to_position2(sn,sn_sonar,300,300,MAX_SPEED/2,TURN_SPEED,1);
    if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
      scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    }
  }
}
