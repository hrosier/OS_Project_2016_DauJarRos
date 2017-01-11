#include "basic_include.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
#include "init.h"
#include "position.h"

#define TIME_SLEEP 1800

void turn_compass_test(uint8_t *sn, int speed, int sleep_time, char choice){
  for (int i=0; i<8; i++){
    Sleep(sleep_time);
    //print_robot_abs_angle();
    print_robot_rel_angle();
    Sleep(sleep_time);
    if (choice==1){
      bi_turn_angle(sn,speed,90,0);
    }
    else {
      bi_turn_angle2(sn,speed,90,0);
    }
    Sleep(sleep_time);
  }
}

int main( int argc, char * argv[] )
{
  int max_speed, max_speed_door, turn_speed, position;
  uint8_t sn1,sn2,sn3, sn_sonar, sn_compass;
  uint8_t sn[2];

  init();
  init_wheels(&sn1,&sn2,sn,&max_speed);
  init_door(&sn3,&max_speed_door);
  init_sonar(&sn_sonar);
  init_compass(&sn_compass);
  create_thread_angle(&sn_compass);

  turn_speed = max_speed/8;
  int choice = atoi (argv[1]);
  turn_compass_test(sn,turn_speed,TIME_SLEEP,choice);

 // get_tacho_position(sn1,&position);
 // printf("begin turning 90 \n");
 // bi_standard_turn_angle(sn, 90, 0);
 // Sleep(TIME_SLEEP);
 // print_robot_abs_angle();
 // Sleep(TIME_SLEEP);

 // printf("begin turning -90 \n");
 // bi_standard_turn_angle(sn, -90, 0);
 // Sleep(TIME_SLEEP);
 // print_robot_abs_angle();
 // Sleep(TIME_SLEEP);

 // printf("begin turning 180\n");
 // bi_standard_turn_angle(sn, 180, 0);
 // Sleep(TIME_SLEEP);
 // print_robot_abs_angle();

 // printf("begin turning -180 \n");
 // bi_standard_turn_angle(sn, -180, 0);
 // Sleep(TIME_SLEEP);
 // print_robot_abs_angle();

 // printf("begin turning 360\n");
 // bi_standard_turn_angle(sn, 360, 0);
 // Sleep(TIME_SLEEP);
 // print_robot_abs_angle();

//  printf("begin turning to the angle 90\n");
//  turn_to_angle(sn,turn_speed,90,0);
//  Sleep(TIME_SLEEP);
//  print_robot_abs_angle();
//  print_robot_rel_angle();
//  printf("begin turning to the angle 90\n");
//  turn_to_angle(sn,turn_speed,90,0);
//  Sleep(TIME_SLEEP);
//  print_robot_abs_angle();
//  print_robot_rel_angle();
//  printf("begin turning to the angle 180\n");
//  turn_to_angle(sn,turn_speed,180,0);
//  Sleep(TIME_SLEEP);
//  print_robot_abs_angle();
//  print_robot_rel_angle();
  //          printf("I scan for the ball\n");
  //          scan_angle_distance(sn,sn_sonar,speed,45,300);
  //          Sleep(5000);
  //
  //          printf("I scan for the ball\n");
  //          scan_angle_distance(sn,sn_sonar,speed,-90,300);
  //          Sleep(5000);
  //
  //          printf("I try to catch it\n");
  //          catch_dist(sn,sn3,max_speed/2,3000);
  //          Sleep(3000);
  //
  //          // To keep the door close
  //          set_tacho_position(sn3,0);
  //          set_tacho_command_inx(sn3, TACHO_RUN_TO_ABS_POS);
  //
  //          printf(" I gonna do a U turn \n");
  //          u_turn_right(sn,max_speed/2,0);
  //          Sleep(1000);

  ev3_uninit();
}
