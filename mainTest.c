#include "basic_include.h"
#include "mainTest.h"
#include "catapult.h"
#include "color.h"
#include "sonar.h"
#include <string.h>

#define DISTANCE_SQUARE 300
#define SLEEP_TIME 1800
#define LIM_DIST 500

int main( int argc, char *argv[] ){
  int choice_parameter, turn_speed;
  char choice[20];
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color,sn_compass;
  uint8_t sn[2];

  turn_speed=TURN_SPEED;

  if (argc!=3){
    printf("[X] Wrong usage of the function ! use it like that : ./mainTest movement 1\n");
    return 0;
  }

  init_all(&sn1,&sn2,&sn3,&sn4,&sn_sonar,&sn_color,&sn_compass,sn);

  strncpy(choice,argv[1],20);
  choice_parameter = atoi(argv[2]);
  if (!strcmp(choice,"stop")){
    stop_running(sn);
    uninit(&sn3,&sn4);
    return 1;
  }
  if (!strcmp(choice,"catapult")){
    test_catapult(sn4,choice_parameter);
    return 1;
  }
  if (!strcmp(choice,"color")){
    test_color(sn_color,choice_parameter);
    return 1;
  }
  if (!strcmp(choice,"sonar")){
    test_sonar(sn_sonar,choice_parameter);
    return 1;
  }
  if (!strcmp(choice,"turn")){
    test_turn(sn,sn_sonar,sn_compass,turn_speed,choice_parameter);
    return 1;
  }
  if (!strcmp(choice,"compass")){
    test_compass(sn_compass,choice_parameter);
    return 1;
  }
  if (!strcmp(choice,"grab")){
    test_grab(sn,sn3,choice_parameter);
    return 1;
  }
  if (!strcmp(choice,"movement")){
    test_movement(sn,sn_sonar,choice_parameter);
    return 1;
  }
  uninit(&sn3,&sn4);
}

void test_catapult(uint8_t sn, int choice_parameter){
  if (choice_parameter==1){
    throw(sn);
    throw_pos(sn,1000,130);
  }
}

void test_color(uint8_t sn_color, char choice_parameter){
  for ( ; ; ){
    if (choice_parameter==1){
      print_RGB(sn_color);
    }
    else
      print_color(sn_color);
  }
}

void test_compass(uint8_t sn_compass, char choice_parameter){
  float value;
  while (1)  {
    //printf("Robot angle is : %f \n",robot_angle);
    if (choice_parameter==1){
      print_robot_rel_angle();
      print_robot_abs_angle();
      Sleep(2000);
    }
    if (choice_parameter==2){
      print_robot_abs_angle();
      Sleep(2000);
    }
    if (choice_parameter==3){
      if ( !get_sensor_value0(sn_compass, &value)) {
        value = 0;
      } 
      printf("robot angle from north : %f \n ", value);
      Sleep(2000);
    }
  }
}

void test_grab(uint8_t *sn, uint8_t sn3, int choice_parameter){
  int door_speed;
  door_speed=MAX_SPEED_DOOR/4;
  if (choice_parameter==1){
    release_ball(sn,sn3,door_speed,200);
  }
  //  val=scan_angle_distance(sn, sn_sonar, MAX_SPEED, 410, 100);
  //  if (val>100){
  //    val=scan_angle_distance(sn, sn_sonar, MAX_SPEED, 410, 200);
  //  }
  //  if (val>200){
  //    val=scan_angle_distance(sn, sn_sonar, MAX_SPEED, 410, 300);
  //  }
  //  i = is_it_the_ball(sn,sn3,sn_color,MAX_SPEED/4,val);
  //door_mi_down(sn3,door_speed);
  //run_to_abs_pos(sn,MAX_SPEED/4,0);
}

void first_course(uint8_t *sn, uint8_t sn_sonar, int speed,int turn_speed, int distance){
  create_thread_print_coordinates();
  for (int i=0;i<4;i++){
    printf("[A] I am running for %d mm  \n", distance);
    run_distance_unless_obstacle(sn, sn_sonar, speed, distance);

    printf("[A] I am gonna turn left \n");
    bi_turn_angle_ramp(sn, turn_speed, -90,distance,500, 0);
    Sleep(1000);
  }
}

void test_movement(uint8_t *sn, uint8_t sn_sonar, int choice_parameter){
  int speed, turn_speed;
  speed = MAX_SPEED/3;
  turn_speed = MAX_SPEED/5;
  printf("[I] Turn speed : %d \n",turn_speed);
  if (choice_parameter==1){
    first_course(sn,sn_sonar,speed,turn_speed,DISTANCE_SQUARE);
  }
  if (choice_parameter==3){
    //run_distance(sn,MAX_SPEED/3,-100,0);
    run_distance(sn,MAX_SPEED/3,-20,0);
    Sleep(SLEEP_TIME);
    run_distance(sn,-MAX_SPEED/3,10,0);
  }
  if (choice_parameter==21){
    go_to_position1(sn,200,200,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position1(sn,0,400,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position1(sn,200,200,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position1(sn,0,0,MAX_SPEED/3,TURN_SPEED,0);
    turn_to_angle(sn,TURN_SPEED,0,"rel",0);
  }
  if (choice_parameter==22){
    go_to_position2(sn,200,200,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,0,400,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,200,200,MAX_SPEED/3,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,0,0,MAX_SPEED/3,TURN_SPEED,0);
    turn_to_angle(sn,TURN_SPEED,0,"rel",0);
  }

}

void test_sonar(uint8_t sn_sonar, int choice_parameter){
  if (choice_parameter==1){
    while(true){
      print_sonar(sn_sonar);
      Sleep(1000);
    }
  }
}

void test_turn(uint8_t *sn, uint8_t sn_sonar, uint8_t sn_compass, int turn_speed, char choice_parameter){
  if (choice_parameter==1){
    for (int i=0; i<8; i++){
      Sleep(SLEEP_TIME);
      //print_robot_abs_angle();
      print_robot_rel_angle();
      Sleep(SLEEP_TIME);
      if (choice_parameter==1){
        bi_turn_angle(sn,turn_speed,90,0);
      }
      else {
        bi_turn_angle2(sn,turn_speed,90,0);
      }
      Sleep(SLEEP_TIME);
    }
    }
    if (choice_parameter==2){
      turn_to_angle(sn,TURN_SPEED,90,"rel",0);
      Sleep(SLEEP_TIME);
      print_robot_rel_angle();
      turn_to_angle(sn,TURN_SPEED,180,"rel",0);
      Sleep(SLEEP_TIME);
      print_robot_rel_angle();
      turn_to_angle(sn,TURN_SPEED,270,"rel",0);
      Sleep(SLEEP_TIME);
      print_robot_rel_angle();
      turn_to_angle(sn,TURN_SPEED,0,"rel",0);
      Sleep(SLEEP_TIME);
      print_robot_rel_angle();
  }
}
