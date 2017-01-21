#include "basic_include.h"
#include "mainTest.h"
#include "catapult.h"
#include "color.h"
#include "sonar.h"
#include "bluetooth.h"
#include <string.h>

#define DISTANCE_SQUARE 300
#define SLEEP_TIME 1800

int main( int argc, char *argv[] ){
  int error,i;
  char choice[20];
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color,sn_compass,sn_gyro;
  uint8_t sn[2];

  if (argc<3){
    printf("[X] Wrong usage of the function ! use it like that : ./mainTest movement 1\n");
    return 0;
  }
  int choice_parameters[argc-2];

  init_all(&sn1,&sn2,&sn3,&sn4,&sn_sonar,&sn_color,&sn_compass,&sn_gyro,sn);
  error=1;
  strncpy(choice,argv[1],20);
  for(i=2;i<argc;i++){
    choice_parameters[i-2] = atoi(argv[i]);
  }
  if (!strcmp(choice,"stop")){
    set_tacho_stop_action_inx(sn3,TACHO_COAST);
    //uninit(&sn3,&sn4);
    stop_running(sn);
    error=0;
  }
  if (!strcmp(choice,"catapult")){
    test_catapult(sn4,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"color")){
    test_color(sn_color,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"sonar")){
    test_sonar(sn_sonar,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"turn")){
    test_turn(sn,sn_sonar,sn_compass,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"compass")){
    test_compass(sn_compass,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"grab")){
    test_grab(sn,sn3,sn_sonar,sn_color,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"movement")){
    test_movement(sn,sn_sonar,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"movementgrab")){
    test_movement_grab(sn,sn3,sn_sonar,sn_color,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"bluetooth")){
    test_bluetooth(sn,sn3,sn_sonar,sn_color,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"gyro")){
    test_gyro(sn,sn3,sn_sonar,sn_color,sn_gyro,choice_parameters);
    error=0;
  }
  if (error) printf("[X] error %s is not a right command :/ \n",choice);
  uninit(&sn3,&sn4);
}

void test_catapult(uint8_t sn, int *choice_parameters){
  if (choice_parameters[0]==1){
    throw(sn);
    throw_pos(sn,1000,130);
  }
}

void test_color(uint8_t sn_color, int *choice_parameters){
  for ( ; ; ){
    if (choice_parameters[0]==1){
      print_RGB(sn_color);
    }
    else
      print_color(sn_color);
  }
}

void test_compass(uint8_t sn_compass, int *choice_parameters){
  float value;
  while (1)  {
    //printf("Robot angle is : %f \n",robot_angle);
    if (choice_parameters[0]==1){
      print_robot_rel_angle();
      print_robot_abs_angle();
      Sleep(2000);
    }
    if (choice_parameters[0]==2){
      print_robot_abs_angle();
      Sleep(2000);
    }
    if (choice_parameters[0]==3){
      if ( !get_sensor_value0(sn_compass, &value)) {
        value = 0;
      } 
      printf("robot angle from north : %f \n ", value);
      Sleep(2000);
    }
  }
}

void test_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters){
  if (choice_parameters[0]==1){
    if (scan(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/4,SONAR_DISTANCE )== 2){
      bi_turn_angle2(sn,sn_sonar,MAX_SPEED/4,40,1);
      scan(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/4,SONAR_DISTANCE);  
    }
  } 
  if (choice_parameters[0]==2){
    if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
      bi_turn_angle2(sn,sn_sonar,MAX_SPEED/4,40,1);
      scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    }
  }
}

void first_course(uint8_t *sn, uint8_t sn_sonar, int speed,int turn_speed, int distance){
  create_thread_print_coordinates();
  for (int i=0;i<4;i++){
    printf("[A] I am running for %d mm  \n", distance);
    run_distance_unless_obstacle(sn, sn_sonar, speed, distance);

    printf("[A] I am gonna turn left \n");
    bi_turn_angle_ramp(sn,sn_sonar, turn_speed, -90,distance,500, 0);
    Sleep(1000);
  }
}

void test_movement(uint8_t *sn, uint8_t sn_sonar, int *choice_parameters){
  int speed, turn_speed;
  printf("[I] Turn speed : %d \n",turn_speed);
  if (choice_parameters[0]==1){
    first_course(sn,sn_sonar,speed,turn_speed,DISTANCE_SQUARE);
  }
  if (choice_parameters[0]==3){
    speed=choice_parameters[2];
    while (speed<MAX_SPEED){
      run_distance(sn,sn_sonar,speed,choice_parameters[1],0);
      Sleep(SLEEP_TIME);
      speed+=20;
    }
  }
  if (choice_parameters[0]==21){
    go_to_position1(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,choice_parameters[3],0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,0,2*choice_parameters[2],MAX_SPEED/2,TURN_SPEED,choice_parameters[3],0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,choice_parameters[3],0);
    Sleep(3000);
    go_to_position1(sn,sn_sonar,0,0,MAX_SPEED/2,TURN_SPEED,choice_parameters[3],0);
    Sleep(3000);
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
  if (choice_parameters[0]==22){
    go_to_position2(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,0,2*choice_parameters[2],MAX_SPEED/2,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,0);
    Sleep(3000);
    go_to_position2(sn,sn_sonar,0,0,MAX_SPEED/2,TURN_SPEED,0);
    Sleep(3000);
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
  }
}

void test_sonar(uint8_t sn_sonar, int *choice_parameters){
  if (choice_parameters[0]==1){
    while(true){
      print_sonar(sn_sonar);
      Sleep(1000);
    }
  }
}

void test_turn(uint8_t *sn, uint8_t sn_sonar, uint8_t sn_compass, int *choice_parameters){
  if (choice_parameters[0]==1){
    for (int i=0; i<8; i++){
      Sleep(SLEEP_TIME);
      //print_robot_abs_angle();
      print_robot_rel_angle();
      Sleep(SLEEP_TIME);
      if (choice_parameters[1]==1){
        bi_turn_angle(sn,sn_sonar,TURN_SPEED,90,0);
      }
      else {
        bi_turn_angle2(sn,sn_sonar,TURN_SPEED,90,0);
      }
      Sleep(SLEEP_TIME);
    }
  }
  if (choice_parameters[0]==2){
    turn_to_angle(sn,sn_sonar,TURN_SPEED,90,1,0);
    Sleep(SLEEP_TIME);
    print_robot_rel_angle();
    turn_to_angle(sn,sn_sonar,TURN_SPEED,180,1,0);
    Sleep(SLEEP_TIME);
    print_robot_rel_angle();
    turn_to_angle(sn,sn_sonar,TURN_SPEED,270,1,0);
    Sleep(SLEEP_TIME);
    print_robot_rel_angle();
    turn_to_angle(sn,sn_sonar,TURN_SPEED,0,1,0);
    Sleep(SLEEP_TIME);
    print_robot_rel_angle();
  }
  if (choice_parameters[0]==3){
    int turn_speed;
    turn_speed=choice_parameters[2];
    while (turn_speed<= TURN_SPEED){
      printf("[I] turn speed: %d \n",turn_speed);
      bi_turn_pos_ramp(sn,sn_sonar,turn_speed,choice_parameters[1]*RIGHT_ANGLE/360,1500,1500,0);
      Sleep(SLEEP_TIME);
      turn_speed+=choice_parameters[3];
    }
  }
  if (choice_parameters[0]==4){
    turn_to_angle(sn,sn_sonar,choice_parameters[2],choice_parameters[1],1,0);
  }
}

void test_movement_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters){
  if (choice_parameters[0]==1){
    go_to_position2(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,1);
    if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
      scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    }
  }
}
void test_gyro(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, uint8_t sn_gyro, int *choice_parameters){
  float value0;
  if (choice_parameters[0]==1){
    while (1){
      if (!get_sensor_value0(sn_gyro,&value0)){
        value0=0;
      }
      if (value0<0) value0+=360;
      printf("[I] angle read : %f \n",value0);
      print_robot_rel_angle();
      printf("\n");
      Sleep(2000);
    }
  }
}

void test_bluetooth(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters){
  extern uint16_t msgId;
  extern char rank,length,previous,next,side;
  int s;
  if( init_bluetooth(&s) == 0 ) {
    char string[58];
    // Wait for START message 
    read_from_server (s, string, 9);
    if (string[4] == MSG_START) {
      printf ("Received start message!\n");
      rank = (unsigned char) string[5];
      side = (unsigned char) string[6];
      next = (unsigned char) string[7];
    }
    if (side==0){
      printf("I am on the right side\n");
    }
    else {
      printf("I am on the left side\n");
    }
    if (rank == 0)
      beginner (sn,sn3,sn_sonar,sn_color,s,side);
    else
      finisher (sn,sn3,sn_sonar,sn_color,s,side);
    close (s);
    sleep (5);

  } else {
    fprintf (stderr, "Failed to connect to server...\n");
    sleep (2);
    exit (EXIT_FAILURE);
  }

  close(s);
}


void beginner (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int side) {
  char string[58];
  extern uint16_t msgId;
  extern char rank,length,previous,next;
  printf ("I'm the beginner...\n");

  /* Send 3 POSITION messages, a BALL message, 1 position message, then a NEXT message */
  int i;
  for (i=0; i<3; i++){
    *((uint16_t *) string) = msgId++;
    string[2] = TEAM_ID;
    string[3] = 0xFF;
    string[4] = MSG_POSITION;
    string[5] = get_x_position();          /* x */
    string[6] = 0x00;
    string[7] = get_y_position();   /* y */
    string[8]= 0x00;
    write(s, string, 9);
    if (side==0) go_to_position2(sn,sn_sonar,get_x_position()+200,get_y_position()+200,MAX_SPEED/3,TURN_SPEED,0);
    if (side==1) go_to_position2(sn,sn_sonar,get_x_position()-200,get_y_position()-200,MAX_SPEED/3,TURN_SPEED,0);

  }

  //BALL drop message
  *((uint16_t *) string) = msgId++;
  string[2] = TEAM_ID;
  string[3] = next;
  string[4] = MSG_BALL;
  string[5] = 0x0;
  string[6] = get_x_position();          /* x */
  string[7] = 0x00;
  string[8] = get_y_position();
  //string[8] = 0x4;    /* y */
  string[9]= 0x00;
  write(s, string, 10);
  release_ball(sn,sn3,sn_sonar,MAX_SPEED/3,350);


  //last position message
  *((uint16_t *) string) = msgId++;
  string[2] = TEAM_ID;
  string[3] = 0xFF;
  string[4] = MSG_POSITION;
  string[5] = get_x_position();          /* x */
  string[6] = 0x00;
  string[7] = get_y_position();   /* y */
  string[8]= 0x00;
  write(s, string, 9);

  //Next message

  *((uint16_t *) string) = msgId++;
  string[2] = TEAM_ID;
  string[3] = next;
  string[4] = MSG_NEXT;
  write(s, string, 5);

  while(1){
    //Wait for other robot to finish
  }
}

void finisher (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int side) {
  char string[58];
  extern uint16_t msgId;
  extern char rank,length,previous,next;
  char type;

  printf ("I'm the finisher...\n");
  /* Get message */
  while (1){
    read_from_server (s, string, 58);
    type = string[4];

    switch (type) {
      case MSG_STOP:
        return;
      case MSG_NEXT:
        //send a position
        *((uint16_t *) string) = msgId++;
        string[2] = TEAM_ID;
        string[3] = 0xFF;
        string[4] = MSG_POSITION;
        string[5] = get_x_position();          /* x */
        string[6]= 0x00;
        string[7] = get_y_position();     /* y */
        string[8] = 0x00;
        write(s, string, 9);

        if (side==0) go_to_position2(sn,sn_sonar,200,200,MAX_SPEED/3,TURN_SPEED,0);
        if (side==1) go_to_position2(sn,sn_sonar,-200,200,MAX_SPEED/3,TURN_SPEED,0);
        if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
          scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
        }
        //pick up a ball
        *((uint16_t *) string) = msgId++;
        string[2] = TEAM_ID;
        string[3] = next;
        string[4] = MSG_BALL;
        string[5] = 0x1;
        string[6] = get_x_position();          /* x */
        string[7] = 0x00;
        string[8] = get_y_position();    /* y */
        string[9]= 0x00;
        write(s, string, 10);       

        if (side==0) go_to_position2(sn,sn_sonar,400,400,MAX_SPEED/3,TURN_SPEED,0);
        if (side==1) go_to_position2(sn,sn_sonar,400,400,MAX_SPEED/3,TURN_SPEED,0);

        //send a position
        string[2] = TEAM_ID;
        string[3] = 0xFF;
        string[4] = MSG_POSITION;
        string[5] = get_x_position();          /* x */
        string[6]= 0x00;
        string[7] = get_y_position();     /* y */
        string[8] = 0x00;
        write(s, string, 9);
        //Game over
        return;
      case MSG_BALL:
        //I know where the ball is
        printf("Ball dropped at %02X%02X,%02X%02X \n",string[7], string[6], string[9], string[8]);
        break;        
      default:
        printf ("Ignoring message %d\n", type);
    }
  }
}
