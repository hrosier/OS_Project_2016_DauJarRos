#include "basic_include.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
#include "init.h"
#include "position.h"

#define DISTANCE_SQUARE 300

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

int main(int argc, char *argv[])
{
  if (argc != 2){
    printf("[X] wrong usage of the function ! Need 1 parameter\n");
    return 0;
  }

  int max_speed, max_speed_door, door_speed, speed, turn_speed, course_number;
  uint8_t sn1,sn2,sn3, sn_sonar, sn_compass;
  uint8_t sn[2];

  init();
  init_wheels(&sn1,&sn2,sn,&max_speed);
  init_door(&sn3,&max_speed_door);
  init_sonar(&sn_sonar);
  init_compass(&sn_compass);
  init_threads(sn,&sn_compass);
  door_speed = max_speed_door/2;
  speed = max_speed/3;
  turn_speed = max_speed/5;

  printf("[I] Value of max_speed : %d \n", max_speed);
  printf("[I] vitesse des roues : %d \n",turn_speed);
  
  course_number = atoi(argv[1]);
  //printf("[T] test");
  if (course_number==1){
    first_course(sn,sn_sonar,speed,turn_speed,DISTANCE_SQUARE);
  }
  ev3_uninit();
}
