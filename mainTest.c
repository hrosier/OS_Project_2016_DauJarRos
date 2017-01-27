#include "basic_include.h"
#include "testFunctions.h"

#define DISTANCE_SQUARE 300
#define SLEEP_TIME 1800

int main( int argc, char *argv[] ){
  //Print a error if the executable is wrongly used
  if (argc<3){
    printf("[X] Wrong usage of the function ! use it like that : ./mainTest movement 1\n");
    return 0;
  }

  // Declaration of used variables
  int error,i,s;
  char choice[20];
  uint8_t sn1,sn2,sn3,sn4,sn_sonar,sn_color,sn_compass,sn_gyro;
  uint8_t sn[2];
  int choice_parameters[argc-2];

  // Initilisation of the variables
  init_all(&sn1,&sn2,&sn3,&sn4,&sn_sonar,&sn_color,&sn_compass,&sn_gyro,sn);
  error=1;
  // The first argument must be a string
  strncpy(choice,argv[1],20);
  // The others are integers
  for(i=2;i<argc;i++){
    choice_parameters[i-2] = atoi(argv[i]);
  }

  if (!strcmp(choice,"stop")){
    set_tacho_stop_action_inx(sn3,TACHO_COAST);
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
    test_turn(sn,sn_sonar,choice_parameters);
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
    test_bluetooth(&s,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"gyro")){
    test_gyro(sn_gyro,choice_parameters);
    error=0;
  }
  if (!strcmp(choice,"smallbeg")){
    create_thread_print_coordinates();
    if (choice_parameters[0]==1){
      set_position(1100,300);
      set_side_angle(0);
      while (1){
        small_arena_beginner(sn,sn3,sn_sonar,sn_color,s,choice_parameters[1]);
      }
    }
    if (choice_parameters[0]==2){
      set_position(1100,300);
      set_side_angle(0);
      put_small_beg(sn,sn3,sn_sonar,s,choice_parameters[1]);
    }
    if (choice_parameters[0]==3){
      set_position(1100,1900);
      set_side_angle(180);
      get_small_beg(sn,sn3,sn_sonar,sn_color,s,choice_parameters[1]);
    }
    error=0;
  }
  if (!strcmp(choice,"smallfin")){
    create_thread_print_coordinates();
    if (choice_parameters[0]==1){
      set_position(100,1700);
      set_side_angle(180);
      while(1){
        small_arena_finisher(sn,sn3,sn_sonar,sn_color,s,choice_parameters[1]);
      }
    }
    if (choice_parameters[0]==2){
      set_position(100,1700);
      set_side_angle(180);
      get_small_fin(sn,sn3,sn_sonar,sn_color,s,choice_parameters[1]);
    }
    if (choice_parameters[0]==3){
      set_position(100,300);
      set_side_angle(0);
      put_small_fin(sn,sn3,sn_sonar,s,choice_parameters[1]);
    }
    error=0;
  }
  if (!strcmp(choice,"bigbeg")){
    create_thread_print_coordinates();
    big_arena_beginner(sn,sn3,sn4,sn_sonar,choice_parameters[0],s,choice_parameters[1]);
    error=0;
  }
  if (!strcmp(choice,"bigfin")){
    create_thread_print_coordinates();
    big_arena_finisher(sn,sn3,sn4,sn_sonar,sn_color,choice_parameters[0],s,choice_parameters[1]);
    error=0;
  }
  if (error) printf("[X] error : %s is not a right command :/ \n",choice);
  uninit(&sn3,&sn4);
}
