#include "basic_include.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
#include "init.h"

int main( void )
{
  int i, max_speed, max_speed_door, turn_speed, position;
  uint8_t sn1,sn2,sn3, sn_sonar;
  uint8_t sn[2];
  char s[ 256 ];
  uint32_t n, ii;

  init();
  init_wheels(&sn1,&sn2,sn,&max_speed);
  init_door(&sn3,&max_speed_door);
  init_sonar(&sn_sonar);
  turn_speed = max_speed/2;

  printf("vitesse des roues : %d \n",turn_speed);

  get_tacho_position(sn1,&position);
  printf("position du moteur : %d\n",position);
  printf("begin turning\n");
  bi_standard_turn_angle(sn, 90, 0);

  printf("begin turning\n");
  bi_standard_turn_angle(sn, -90, 0);

  printf("begin turning\n");
  bi_standard_turn_angle(sn, 180, 0);

  printf("begin turning\n");
  bi_standard_turn_angle(sn, -180, 0);

  printf("begin turning\n");
  bi_standard_turn_angle(sn, 360, 0);
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
