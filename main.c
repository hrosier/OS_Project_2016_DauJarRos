#include "basic_include.h"
#include "catapult.h"

#define LIM_DIST 500

void test3 (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int val){
  run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,1200);
  bi_standard_turn_angle(sn,sn_sonar, -val,0);
  run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,850);
  bi_standard_turn_angle(sn,sn_sonar, val,0);
  run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,800);
  bi_standard_turn_angle(sn,sn_sonar, val,0);
  run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,450);
  //release_ball(sn,sn3,MAX_SPEED/4,300);
  //run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,150);
  bi_standard_turn_angle(sn,sn_sonar, -val,0);
  run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,1950);
}

//first competition 
void first_competition(uint8_t *sn, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters){
  if (choice_parameters[0]==10){
    uninit(&sn3,&sn4);
    return;
  }
  if (choice_parameters[0]==1){
    run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,1650);
  }
  if (choice_parameters[0]==2){
    run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,800);
    bi_standard_turn_angle(sn,sn_sonar, -90,0);
    run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,450);
    Sleep(4000);
    //release_ball(sn,sn3,MAX_SPEED/4,350); // must add the other params
  }
  if (choice_parameters[0]==31){
    test3(sn,sn3,sn_sonar,90);
  }
  if (choice_parameters[0]==32){
    test3(sn,sn3,sn_sonar,-90);
  }
  if (choice_parameters[0]==5){
    run_distance_unless_obstacle(sn,sn_sonar,MAX_SPEED/2,1000);  
    catch_ball(sn,sn3,sn_sonar,MAX_SPEED/4);
  }
  if (choice_parameters[0]==6){
    if (scan(sn,sn3,sn_sonar,sn_color,MAX_SPEED/8,MAX_SPEED/4,LIM_DIST)== 2){
        scan(sn,sn3,sn_sonar,sn_color,MAX_SPEED/9,MAX_SPEED/4,LIM_DIST);  
    }
  }
  if (choice_parameters[0]==7){
    if (scan2(sn,sn3,sn_sonar,sn_color,MAX_SPEED/9,MAX_SPEED/6,LIM_DIST)== 2){
        scan2(sn,sn3,sn_sonar,sn_color,MAX_SPEED/10,MAX_SPEED/6,LIM_DIST);  
    }
  }
}

// fonction used for the competition
void final_competition(uint8_t *sn, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, int *s, int *choice_parameters){
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
    create_thread_print_coordinates();
    if (side==0 && rank==0 && choice_parameters[0]==1){
    create_thread_send_message(s);
      printf("I Big arena beg right \n");
      big_arena_beginner(sn,sn3,sn4,sn_sonar,1,*s,dest);
    }
    if (side==1 && rank==0 && choice_parameters[0]==1){
    create_thread_send_message(s);
      printf("I Big arena beg left \n");
      big_arena_beginner(sn,sn3,sn4,sn_sonar,-1,*s,dest);
    }
    if (side==0 && rank==1 && choice_parameters[0]==1){
      printf("I Big arena fin right \n");
      big_arena_finisher(sn,sn3,sn4,sn_sonar,sn_color,1,*s,dest);
    }
    if (side==1 && rank==1 && choice_parameters[0]==1){
    create_thread_send_message(s);
      printf("I Big arena beg left \n");
      big_arena_finisher(sn,sn3,sn4,sn_sonar,sn_color,-1,*s,dest);
    }
    if (side==0 && rank==0 && choice_parameters[0]==2){
      printf("I small arena beg left \n");
      set_position(1100,300);
      set_side_angle(0);
      while (1){
        small_arena_beginner(sn,sn3,sn_sonar,sn_color,*s,dest);
      }
    }
    if (side==0 && rank==1 && choice_parameters[0]==2){
      printf("I small arena fin \n");
      set_position(100,1700);
      set_side_angle(180);
      while (1){
        small_arena_finisher(sn,sn3,sn_sonar,sn_color,*s,dest);
      }
    }
    close (*s);
    sleep (5);
  } else {
    fprintf (stderr, "Failed to connect to server...\n");
    sleep (2);
    exit (EXIT_FAILURE);
  }
  close(*s);
}

int main( int argc, char *argv[] )
{
  int error,i,s;
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
  if (!strcmp(choice,"first")) {
    first_competition(sn,sn3,sn4,sn_sonar,sn_color,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"final")) {
    final_competition(sn,sn3,sn4,sn_sonar,sn_color,&s,choice_parameters);
    error=0;
  }
  if (error) printf("[X] the option %s doesn't exist",choice);
  uninit(&sn3,&sn4);
}
