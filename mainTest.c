#include "basic_include.h"
#include "catapult.h"

#define LIM_DIST 500

void test3 (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int max_speed, int val){
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,1200);
  bi_standard_turn_angle(sn, -val,0);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,850);
  bi_standard_turn_angle(sn, val,0);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,800);
  bi_standard_turn_angle(sn, val,0);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,450);
  //release_ball(sn,sn3,max_speed/4,300);
  //run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,150);
  bi_standard_turn_angle(sn, -val,0);
  run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,1950);
}

int main( int argc, char *argv[] )
{
  int max_speed,max_speed_door,max_speed_catapult,speed,door_speed,catapult_speed,test_number;
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color,sn_compass;
  uint8_t sn[2];

  init_all(&sn1,&sn2,&sn3,&sn4,&sn_sonar,&sn_color,&sn_compass,sn,&max_speed,&max_speed_door,&max_speed_catapult);
  door_speed=max_speed_door/3;

  test_number = atoi(argv[1]);
  if (test_number==10){
    uninit(&sn3,&sn4);
    return 1;
  }
  if (test_number==1){
    run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,1650);
  }
  if (test_number==2){
    run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,800);
    bi_standard_turn_angle(sn, -90,0);
    run_distance_unless_obstacle(sn,sn_sonar,max_speed/2,450);
    Sleep(4000);
    release_ball(sn,sn3,max_speed/4,350);
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
    if (scan(sn,sn3,sn_sonar,sn_color,max_speed/8,max_speed/4,LIM_DIST )== 2){
        scan(sn,sn3,sn_sonar,sn_color,max_speed/9,max_speed/4,LIM_DIST);  
    }
  }
  if (test_number==7){
    if (scan2(sn,sn3,sn_sonar,sn_color,max_speed/9,max_speed/6,LIM_DIST)== 2){
        scan2(sn,sn3,sn_sonar,sn_color,max_speed/10,max_speed/6,LIM_DIST);  
    }
  }
  uninit(&sn3,&sn4);
}
