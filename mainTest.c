#include "basic_include.h"
#include "catapult.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
#include "init.h"

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

int main( void )
{
  int i,val,max_speed,max_speed_door,max_speed_catapult,speed,door_speed,catapult_speed;
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color;
  uint8_t sn[2];
  char s[ 256 ];
  uint32_t n, ii;

  init_all(sn1,sn2,sn3,sn4,sn_sonar,sn_color,sn,&max_speed,&max_speed_door,&max_speed_catapult);
  door_speed=max_speed_door/2;

  printf("I am opening the door \n");
  door_up(sn3,door_speed);
  Sleep(2000);

  //printf("I am running for a certain amount of time \n");
  //run_timed(sn,max_speed/4,1000);
  //Sleep(1000);

  printf("I am closing the door \n");
  door_down(sn3,door_speed);
  Sleep(2000);

  // printf("I am running until i found an obstacle\n");
  // run_forever_unless_obstacle(sn,sn_sonar,max_speed/3);
  // Sleep(1000);

  printf("I run foward for x sec \n");
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/4,500);
  Sleep(3000);

  throw(sn4);

  printf(" I gonna do a U turn \n");
  u_turn_right(sn,max_speed/2,0);
  Sleep(1000);

  //go back
  run_to_abs_pos(sn, max_speed/3,0);
  ev3_uninit();
}
