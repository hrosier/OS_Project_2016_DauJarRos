#include "basic_include.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
#include "init.h"
#include "position.h"

int main( void )
{
  int i, max_speed, max_speed_door, door_speed, speed, turn_speed,  position;
  uint8_t sn1,sn2,sn3, sn_sonar;
  uint8_t sn[2];
  char s[ 256 ];
  uint32_t n, ii;

  pthread_t threadpos;
  extern int pos_x;
  extern int pos_y;
  extern int direction; //North,East,south,West
  extern pthread_mutex_t mutex ;

  init();
  init_wheels(&sn1,&sn2,sn,&max_speed);
  printf("value of max_speed : %d \n ", max_speed);
  init_door(&sn3,&max_speed_door);
  init_sonar(&sn_sonar);
  door_speed = max_speed_door/2;
  speed = max_speed*4/5;
  turn_speed = max_speed/2;  

  printf("vitesse des roues : %d \n",turn_speed);
  //get_tacho_position(sn1,&position);
  //printf("position du moteur : %d\n",position);

  if(pthread_create(&threadpos, NULL, thread_position,sn)==-1){
    perror("pthread_create");
  }
  printf("I am running for 500 mm  \n");
  run_distance_ramp(sn, speed, 500, 1000, 1000, 0);
  Sleep(3000);

  printf("I am gonna turn left \n");
  bi_turn_angle_ramp(sn, turn_speed, -90,500,500, 0);
  printf("test");
  pthread_mutex_lock(&mutex);
  direction=3;
  pthread_mutex_unlock(&mutex);

  printf("I am running for 500 mm  \n");
  run_distance_ramp(sn, speed, 500, 2000, 1000, 0);
  Sleep(3000);

  printf("I am gonna turn left \n");
  bi_turn_angle_ramp(sn, turn_speed, -90,1000,1000, 0);
  pthread_mutex_lock(&mutex);
  direction=2;
  pthread_mutex_unlock(&mutex);

  printf("I am running for 500 mm  \n");
  run_distance(sn,speed,500,0);
  Sleep(3000);

  printf("I am gonna turn left \n");
  bi_turn_angle(sn, turn_speed, -90, 0);
  pthread_mutex_lock(&mutex);
  direction=1;
  pthread_mutex_unlock(&mutex);

  printf("I am running for 500 mm  \n");
  run_distance(sn,speed,500,0);
  Sleep(3000);

  printf("I am gonna turn left \n");
  bi_turn_angle(sn, speed, -90, 0);
  pthread_mutex_lock(&mutex);
  direction=0;
  pthread_mutex_unlock(&mutex);

  //get_tacho_position(sn1,&position);
  //printf("position du moteur : %d\n",position);
  //printf("I am running for 1000 mm \n");
  //run_distance_unless_obstacle(sn,sn_sonar,speed,1000);
  //Sleep(3000);
  //get_tacho_position(sn1,&position);
  //printf("position du moteur : %d\n",position);

  //          printf("I scan for the ball\n");
  //          scan_angle_distance(sn,sn_sonar,speed,45,300);
  //          Sleep(3000);
  //
  //          printf("I scan for the ball\n");
  //          scan_angle_distance(sn,sn_sonar,speed,--90,300);
  //          Sleep(3000);
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
