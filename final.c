#include "basic_include.h"

void small_arena_beginner(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar){
  run_distance(sn,sn_sonar,MAX_SPEED,800,0);
  turn_to_angle(sn,sn_sonar,TURN_SPEED,270,1,0);
  run_distance(sn,sn_sonar,MAX_SPEED,500,0);
  release_ball(sn,sn_sonar,sn3,MAX_SPEED/4,300,-1);
  go_to_position1(sn,sn_sonar,0,1800,MAX_SPEED/2,TURN_SPEED,1,0);
}

void small_arena_finisher(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color){
  go_to_position1(sn,sn_sonar,-600,600,MAX_SPEED/2,TURN_SPEED,1,0);
  int found=scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE);
  if (found != 1){
    bi_turn_angle2(sn,sn_sonar,MAX_SPEED/4,20,1);
    found=scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
  }
  else go_to_position1(sn,sn_sonar,0,1800,MAX_SPEED/2,TURN_SPEED,1,0);
}

void big_arena_beginner(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int side){
  go_to_position1(sn,sn_sonar,side*1050,1500,MAX_SPEED,TURN_SPEED,1,0);
  go_to_position1(sn,sn_sonar,side*600,2000,MAX_SPEED,TURN_SPEED,1,0);
  release_ball(sn,sn_sonar,sn3,MAX_SPEED/4,300,1);
  run_distance(sn,sn_sonar,MAX_SPEED,350,1);
  go_to_position1(sn,sn_sonar,0,3900,MAX_SPEED,TURN_SPEED,1,1);
}

void big_arena_finisher(uint8_t *sn, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, int side){
  go_to_position1(sn,sn_sonar,side*1050,1500,MAX_SPEED,TURN_SPEED,1,0);
  //throw(); 
  go_to_position1(sn,sn_sonar,side*1050,1900,MAX_SPEED,TURN_SPEED,1,0);
  int found=scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE);
  if (found == 2){
    bi_turn_angle2(sn,sn_sonar,MAX_SPEED/4,60,1);
    found=scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
  }
  if (found==1){
    go_to_position1(sn,sn_sonar,0,1800,MAX_SPEED/2,TURN_SPEED,1,0);
    go_to_position1(sn,sn_sonar,0,3900,MAX_SPEED,TURN_SPEED,1,1);
  }
}
