#include "basic_include.h"
#include "catapult.h"

int main( void ){
  int max_speed, max_speed_door, max_speed_cata, door_speed;
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color,sn_compass;
  uint8_t sn[2];

  init_all(&sn1, &sn2, &sn3, &sn4, &sn_sonar, &sn_color, &sn_compass, sn, &max_speed, &max_speed_door, &max_speed_cata);
  door_speed=max_speed_door/4;
  
  release_ball(sn,sn3,door_speed,200);

//  val=scan_angle_distance(sn, sn_sonar, max_speed, 410, 100);
//  if (val>100){
//    val=scan_angle_distance(sn, sn_sonar, max_speed, 410, 200);
//  }
//  if (val>200){
//    val=scan_angle_distance(sn, sn_sonar, max_speed, 410, 300);
//  }
//  i = is_it_the_ball(sn,sn3,sn_color,max_speed/4,val);


  //door_mi_down(sn3,door_speed);
  //run_to_abs_pos(sn,max_speed/4,0);
  ev3_uninit();
  return 1;
}
