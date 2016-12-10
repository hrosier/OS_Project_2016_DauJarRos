#include "basic_include.h"
#include "catapult.h"
#include "grab.h"
#include "movement.h"
#include "init.h"
#include "turn.h"

int main( void ){
  int i, max_speed, max_speed_door, max_speed_cata, val, door_speed, port;
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color;
  uint8_t sn[2];
  char s[ 256 ];
  uint32_t n, ii;

  init(sn1, sn2, sn3, sn4, sn_sonar, sn_color, sn, &max_speed, &max_speed_door, &max_speed_cata);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/4,200);
  printf("ZERsdf");
  u_turn_right(sn,max_speed/4,0);
  ev3_uninit();
  return 1;
}
