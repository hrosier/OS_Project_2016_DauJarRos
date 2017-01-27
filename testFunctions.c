/* this file contains the functions used to test the most of functions */


#include "basic_include.h"

#define DISTANCE_SQUARE 400
#define SLEEP_TIME 1500

/* The functions below are called by mainTest to test the different important functions used for the competition*/

// fonction called by mainTest to test the several functions of the catapult
void test_catapult(uint8_t sn, int *choice_parameters){
  if (choice_parameters[0]==1){
    throw(sn);
    throw_pos(sn,1000,130);
  }
}

// fonction called by mainTest to test the several functions of the color sensor
void test_color(uint8_t sn_color, int *choice_parameters){
  for ( ; ; ){
    if (choice_parameters[0]==1){
      print_RGB(sn_color);
    }
    else
      print_color(sn_color);
  }
}

// fonction called by mainTest to test the several grab function
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
  if (choice_parameters[0]==3){
    release_ball(sn,sn_sonar,sn3,MAX_SPEED/4,choice_parameters[1],choice_parameters[2],12,12);
  }
  if (choice_parameters[0]==4){
    get_ball(sn,sn3,sn_sonar,sn_color);
  }
}

// fonction called by mainTest to test the movement of the robot
void test_movement(uint8_t *sn, uint8_t sn_sonar, int *choice_parameters){
  if (choice_parameters[0]==1){
    first_course(sn,sn_sonar,choice_parameters[1],TURN_SPEED,DISTANCE_SQUARE);
  }
  if (choice_parameters[0]==3){
    int speed=choice_parameters[2];
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

// fonction called by mainTest to make the robot make a small circuit (run around a 50cm width square). Called by test_movement
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

// fonction called by mainTest to test the several sonar functions
void test_sonar(uint8_t sn_sonar, int *choice_parameters){
  if (choice_parameters[0]==1){
    while(true){
      print_sonar(sn_sonar);
      Sleep(1000);
    }
  }
}

// fonction called by mainTest to test the several turn functions
void test_turn(uint8_t *sn, uint8_t sn_sonar, int *choice_parameters){
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
    while (turn_speed<= MAX_SPEED){
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

// fonction called by mainTest to test the several compass functions
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

// fonction called by mainTest to test the several gyroscope functions
void test_gyro(uint8_t sn_gyro, int *choice_parameters){
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

// fonction called by mainTest to test the grab and movement functions at the same time
void test_movement_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters){
  if (choice_parameters[0]==1){
    go_to_position1(sn,sn_sonar,choice_parameters[1],choice_parameters[2],MAX_SPEED/2,TURN_SPEED,choice_parameters[3],1);
    if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
      scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
    }
  }
}

// fonction called by mainTest to test the BT functions
void test_bluetooth(int *s, int *choice_parameters){
  extern unsigned char rank,side;
  unsigned char dest=0xFF;
  if( init_bluetooth(s) == 0 ) {
    printf("[S] Init bluetooth is a success !! \n");
    char string[58];
    // Wait for START message 
    read_from_server (*s, string, 9);
    if (string[4] == MSG_START) {
      printf ("Received start message!\n");
      rank = (unsigned char) string[5];
      side = (unsigned char) string[6];
      dest = (unsigned char) string[7];
    }
    if (side==0 && rank==0 && choice_parameters[0]==1){
      printf("I Big arena beg right \n");
      sleep(5);
      send_message(*s,7,dest,0);
    }
    if (side==1 && rank==0 && choice_parameters[0]==1){
      printf("I Big arena beg left \n");
      sleep(5);
      send_message(*s,7,dest,0);
    }
    if (side==0 && rank==1 && choice_parameters[0]==1){
      printf("I Big arena fin right \n");
      sleep(5);
      send_message(*s,7,dest,1);
    }
    if (side==1 && rank==1 && choice_parameters[0]==1){
      printf("I Big arena fin left \n");
      sleep(5);
      send_message(*s,7,dest,1);
    }
    if (side==0 && rank==0 && choice_parameters[0]==2){
      printf("I small arena beg left \n");
      sleep(5);
      send_message(*s,7,dest,0);
    }
    if (side==0 && rank==1 && choice_parameters[0]==2){
      printf("I small arena fin \n");
      sleep(5);
      send_message(*s,7,dest,1);
    }
    sleep(5);
    send_message(*s,1,dest,1);
    close (*s);
    sleep (5);
  } else {
    fprintf (stderr, "Failed to connect to server...\n");
    sleep (2);
    exit (EXIT_FAILURE);
  }
  close(*s);
}
