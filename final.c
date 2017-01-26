#include "basic_include.h"
#include "catapult.h"

void small_arena_beginner(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar,uint8_t sn_color, int s, int dest){
  //Go put the ball
  put_small_beg(sn,sn3,sn_sonar,s,dest);
  //Wait for the next signal
  char string[58];
  read_from_server(s,string,9);
  while (string[4]!=MSG_NEXT || string[3]!= TEAM_ID){
    // while the message was not a NEXT or a NEXT for us we continue to listen to the server
    read_from_server(s,string,9);
  }
  //go get the ball
  get_small_beg(sn,sn3,sn_sonar,sn_color,s,dest);
}

void put_small_beg(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int s, int dest){
  // recalibrate the robot to its original angle (useful if the robot run severals times)
  turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  // Go to the center of the small arena
  run_distance(sn,sn_sonar,MAX_SPEED,800,0);
  turn_to_angle(sn,sn_sonar,TURN_SPEED,270,1,0);
  run_distance(sn,sn_sonar,MAX_SPEED,400,0);
  //release the ball backward
  release_ball(sn,sn_sonar,sn3,MAX_SPEED/5,300,-1,s,dest);
  //we go to the beginner destination
  go_to_position1(sn,sn_sonar,1050,1800,MAX_SPEED/2,TURN_SPEED,2,0);
  //Send the next signal
  send_message(s,1,dest,1);
}

void get_small_beg(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest){
  // turn the robot to the right angle (180° from its original angle) 
  turn_to_angle(sn,sn_sonar,TURN_SPEED,180,1,0);
  // Go to a position near the center of the arena to start scanning
  go_to_position1(sn,sn_sonar,500,1250,MAX_SPEED/2,TURN_SPEED,2,1);
  // We look for the ball and if we find the ball we go to the beginner starting place
  if (get_ball(sn,sn3,sn_sonar,sn_color)==1) {
    // we send the ball message
    send_message(s,7,dest,1);
    go_to_position1(sn,sn_sonar,1100,300,MAX_SPEED/2,TURN_SPEED,2,1);
  }
}

void small_arena_finisher(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest){
  // Wait for the NEXT signal
  char string[58];
  read_from_server(s,string,9);
  while (string[4]!=MSG_NEXT || string[3]!= TEAM_ID){
    // while the message was not a NEXT or a NEXT for us we continue to listen to the server
    read_from_server(s,string,9);
  }
  //go get the ball and go to the destination
  get_small_fin(sn,sn3,sn_sonar,sn_color,s,dest);
  //Go put the ball and go to the starting place
  put_small_fin(sn,sn3,sn_sonar,s,dest);
}

void get_small_fin(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest){
  // recalibrate the robot angle  
  turn_to_angle(sn,sn_sonar,TURN_SPEED,180,1,0);
  // Go to a position near the center of the arena to start scanning
  go_to_position1(sn,sn_sonar,600,1250,MAX_SPEED/2,TURN_SPEED,2,1);
  // We look for the ball and if we find the ball we go to the beginner starting place
  if (get_ball(sn,sn3,sn_sonar,sn_color)==1) {
    // we send the ball message
    send_message(s,7,dest,1);
    go_to_position1(sn,sn_sonar,100,300,MAX_SPEED/2,TURN_SPEED,1,0);
  }
}

void put_small_fin(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int s, int dest){
  // recalibrate the robot angle  
  turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  // Go to the center of the small arena
  run_distance(sn,sn_sonar,MAX_SPEED,800,0);
  turn_to_angle(sn,sn_sonar,TURN_SPEED,90,1,0);
  run_distance(sn,sn_sonar,MAX_SPEED,500,0);
  //release the ball backward
  release_ball(sn,sn_sonar,sn3,MAX_SPEED/4,300,-1,s,dest);
  //we go to the finisher starting place 
  go_to_position1(sn,sn_sonar,100,1800,MAX_SPEED/2,TURN_SPEED,1,1);
  send_message(s,1,dest,1);
}

void big_arena_beginner(uint8_t *sn, uint8_t sn3,uint8_t sn4, uint8_t sn_sonar, int side, int s, int dest){
  // we set the original position and angle of the robot (the position correspondi to the front of the robot)
  set_position(side*100,300);
  set_side_angle(0);
  // go at the level of the first obstacle 
  go_to_position1(sn,sn_sonar,side*850,1600,MAX_SPEED,TURN_SPEED,2,0);
  // go to the black square where to put the ball (as the symmetry is not perfect there are some slight differences between the 2 sides)
  if (side==1) go_to_position1(sn,sn_sonar,side*500,2150,MAX_SPEED,TURN_SPEED,2,0);
  else go_to_position1(sn,sn_sonar,side*550,2150,MAX_SPEED,TURN_SPEED,2,0);
  // turn the robot in direction of the other side
  if (side==1) turn_to_angle(sn,sn_sonar,TURN_SPEED,270,1,0);
  else turn_to_angle(sn,sn_sonar,TURN_SPEED,90,1,0);
  //release the ball
  release_ball(sn,sn_sonar,sn3,MAX_SPEED/4,350,1,s,dest);
  // throw the projectiles and put back the catapult
  throw(sn4);
  throw_pos(sn4,1000,130);
  // go to the destination (as the symmetry is not perfect there are some slight differences between the 2 sides)
  if (side==1) go_to_position1(sn,sn_sonar,side*150,3900,MAX_SPEED,TURN_SPEED,2,0);
  else go_to_position1(sn,sn_sonar,side*250,3900,MAX_SPEED,TURN_SPEED,2,0);
  //Send the next message to the ally
  send_message(s,1,dest,1);
  // turn the robot in front of the arena (useless for the competition but it nicer)
  turn_to_angle(sn,sn_sonar,TURN_SPEED,180,1,0);
}

void big_arena_finisher(uint8_t *sn, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, int side, int s, int dest){
  // we set the original position and angle of the robot (the position correspondi to the front of the robot)
  set_position(side*1000,3700);
  set_side_angle(180);
  // Wait for the NEXT signal
  char string[58];
  read_from_server(s,string,9);
  while (string[4]!=MSG_NEXT || string[3]!= TEAM_ID){
    read_from_server(s,string,9);
  }
  // go at the level of the first obstacle 
  go_to_position1(sn,sn_sonar,side*300,2500,MAX_SPEED,TURN_SPEED,2,0);
  // Turn the robot in direction of the other team ball and throw the projectiles
  if (side==-1) turn_to_angle(sn,sn_sonar,TURN_SPEED,110,1,0);
  if (side==1) turn_to_angle(sn,sn_sonar,TURN_SPEED,250,1,0);
  throw(sn4); 
  throw_pos(sn4,1000,130); // put back the catapult in place
  // go near where should be the ball (It would be better if we used the BALL message of our ally but I don't trust him/her --')
  go_to_position1(sn,sn_sonar,side*300,2000,MAX_SPEED,TURN_SPEED,2,0);
  // We look for the ball and if we find the ball we go to the finisher destination
  if (get_ball(sn,sn3,sn_sonar,sn_color)==1){
    // we send the ball message
    send_message(s,7,dest,1);
    // go at the level of the first obstacle 
    go_to_position1(sn,sn_sonar,side*900,1700,MAX_SPEED/2,TURN_SPEED,1,0);
    // go to the finisher destination
    go_to_position1(sn,sn_sonar,side*900,250,MAX_SPEED,TURN_SPEED,2,0);
    //send the NEXT message
    send_message(s,1,dest,1);
    // turn the robot in front of the arena (useless for the competition but it nicer)
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
}
