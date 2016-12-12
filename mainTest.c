#include "basic_include.h"
#include "catapult.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
#include "init.h"

void test3 (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int max_speed, int val){
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,1200);
  bi_standard_turn_angle(sn, -val,0);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,700);
  bi_standard_turn_angle(sn, val,0);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,700);
  bi_standard_turn_angle(sn, val,0);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,350);
  release_ball(sn,sn3,max_speed/4);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,350);
  bi_standard_turn_angle(sn, -val,0);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,1700);
}

int main( int argc, char *argv[] )
{
  int i,val,max_speed,max_speed_door,max_speed_catapult,speed,door_speed,catapult_speed,test_number;
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color;
  uint8_t sn[2];
  char s[ 256 ];
  uint32_t n, ii;

  init_all(&sn1,&sn2,&sn3,&sn4,&sn_sonar,&sn_color,sn,&max_speed,&max_speed_door,&max_speed_catapult);
  door_speed=max_speed_door/3;

  test_number = atoi(argv[1]);
  if (test_number==1){
    run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,1650);
  }
  if (test_number==2){
    run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,800);
    bi_standard_turn_angle(sn, -90,0);
    run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,600);
    release_ball(sn,sn3,max_speed/4);
  }
  if (test_number==31){
    test3(sn,sn3,sn_sonar,max_speed,90);
  }
  if (test_number==32){
    test3(sn,sn3,sn_sonar,max_speed,-90);
  }
  if (test_number==5){
    run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,1000);  
    catch_ball(sn,sn3,sn_sonar,max_speed/4);
  }
  if (test_number==6){
    if (!scan(sn,sn3,sn_sonar,sn_color,max_speed)){
      scan(sn,sn3,sn_sonar,sn_color,max_speed);
    }
  }
  uninit(&sn3,&sn4);
}
