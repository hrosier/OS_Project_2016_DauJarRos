#include "basic_include.h"
#include "catapult.h"

void small_arena_beginner(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar,uint8_t sn_color, int s, int dest){
  //Go put the ball
  put_small_beg(sn,sn3,sn_sonar,s,dest);
  //TODO: wait for the next signal
  char string[58];
  read_from_server(s,string,9);
  while (string[4]!=MSG_NEXT || string[3]!= TEAM_ID){
    read_from_server(s,string,9);
  }
  //go get the ball
  get_small_beg(sn,sn3,sn_sonar,sn_color,s,dest);
}

void put_small_beg(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int s, int dest){
  turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  run_distance(sn,sn_sonar,MAX_SPEED,800,0);
  turn_to_angle(sn,sn_sonar,TURN_SPEED,270,1,0);
  run_distance(sn,sn_sonar,MAX_SPEED,400,0);
  release_ball(sn,sn_sonar,sn3,MAX_SPEED/5,300,-1,s,dest);
  go_to_position1(sn,sn_sonar,1050,1800,MAX_SPEED/2,TURN_SPEED,2,0);
  //Send the next signal
  send_message(s,1,dest,1);
  turn_to_angle(sn,sn_sonar,TURN_SPEED,180,1,0);
}

void get_small_beg(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest){
  go_to_position1(sn,sn_sonar,500,1250,MAX_SPEED/2,TURN_SPEED,2,1);
  if (get_ball(sn,sn3,sn_sonar,sn_color)==1) {
    send_message(s,7,dest,1);
    go_to_position1(sn,sn_sonar,1100,300,MAX_SPEED/2,TURN_SPEED,2,1);
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
}

void small_arena_finisher(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest){
  //TODO : Wait for the next signal
  char string[58];
  read_from_server(s,string,9);
  while (string[4]!=MSG_NEXT || string[3]!= TEAM_ID){
    read_from_server(s,string,9);
  }
  //go get the ball
  get_small_fin(sn,sn3,sn_sonar,sn_color,s,dest);
  //Go put the ball
  put_small_fin(sn,sn3,sn_sonar,s,dest);
}

void get_small_fin(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest){
  go_to_position1(sn,sn_sonar,600,1250,MAX_SPEED/2,TURN_SPEED,2,1);
  if (get_ball(sn,sn3,sn_sonar,sn_color)==1) {
    send_message(s,7,dest,1);
    go_to_position1(sn,sn_sonar,100,300,MAX_SPEED/2,TURN_SPEED,1,0);
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
}

void put_small_fin(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int s, int dest){
  turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  run_distance(sn,sn_sonar,MAX_SPEED,800,0);
  turn_to_angle(sn,sn_sonar,TURN_SPEED,90,1,0);
  run_distance(sn,sn_sonar,MAX_SPEED,500,0);
  release_ball(sn,sn_sonar,sn3,MAX_SPEED/4,300,-1,s,dest);
  go_to_position1(sn,sn_sonar,100,1800,MAX_SPEED/2,TURN_SPEED,1,1);
  send_message(s,1,dest,1);
  turn_to_angle(sn,sn_sonar,TURN_SPEED,180,1,0);
}

void big_arena_beginner(uint8_t *sn, uint8_t sn3,uint8_t sn4, uint8_t sn_sonar, int side, int s, int dest){
  set_position(side*100,300);
  set_side_angle(0);
  go_to_position1(sn,sn_sonar,side*850,1600,MAX_SPEED,TURN_SPEED,2,0);
  if (side==1) go_to_position1(sn,sn_sonar,side*500,2150,MAX_SPEED,TURN_SPEED,2,0);
  else go_to_position1(sn,sn_sonar,side*550,2150,MAX_SPEED,TURN_SPEED,2,0);
  
  if (side==1) turn_to_angle(sn,sn_sonar,TURN_SPEED,270,1,0);
  else turn_to_angle(sn,sn_sonar,TURN_SPEED,90,1,0);
  release_ball(sn,sn_sonar,sn3,MAX_SPEED/4,350,1,s,dest);
  throw(sn4);
  throw_pos(sn4,1000,130);
  //go_to_position1(sn,sn_sonar,side*100,2500,MAX_SPEED,TURN_SPEED,1,0);
  if (side==1) go_to_position1(sn,sn_sonar,side*150,3900,MAX_SPEED,TURN_SPEED,2,0);
  else go_to_position1(sn,sn_sonar,side*250,3900,MAX_SPEED,TURN_SPEED,2,0);
  send_message(s,1,dest,1);
  turn_to_angle(sn,sn_sonar,TURN_SPEED,180,1,0);
}

void big_arena_finisher(uint8_t *sn, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, int side, int s, int dest){
  set_position(side*1000,3700);
  set_side_angle(180);
  //TODO : wait for the NEXT signal
  char string[58];
  read_from_server(s,string,9);
  while (string[4]!=MSG_NEXT || string[3]!= TEAM_ID){
    read_from_server(s,string,9);
  }
  go_to_position1(sn,sn_sonar,side*300,2500,MAX_SPEED,TURN_SPEED,2,0);
  if (side==-1) turn_to_angle(sn,sn_sonar,TURN_SPEED,110,1,0);
  if (side==1) turn_to_angle(sn,sn_sonar,TURN_SPEED,250,1,0);
  throw(sn4); 
  throw_pos(sn4,1000,130);
  go_to_position1(sn,sn_sonar,side*300,2000,MAX_SPEED,TURN_SPEED,2,0);
  if (get_ball(sn,sn3,sn_sonar,sn_color)==1){
    send_message(s,7,dest,1);
    go_to_position1(sn,sn_sonar,side*900,1700,MAX_SPEED/2,TURN_SPEED,1,0);
    go_to_position1(sn,sn_sonar,side*900,250,MAX_SPEED,TURN_SPEED,2,0);
    send_message(s,1,dest,1);
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
}

int get_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color){
  int count=0;
  int found=scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE);
  while (found != 1){
    bi_turn_angle2(sn,sn_sonar,MAX_SPEED/4,20,0);
    run_distance(sn,sn_sonar,MAX_SPEED,150,1);
    found=scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    if (count==5) break;
    count++;
  }
  if (found==1) return 1;
  else return 0;
}
