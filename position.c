#include "basic_include.h"
#include <math.h> 
#include "position.h"

int pos_x=0;
int pos_y=0;
float abs_angle_compass; //angle from the north
float rel_angle_compass; //relative angle from the start
float angle_gyro; 
pthread_t threadpos;
pthread_t threadcompass;
pthread_t threadgyro;
pthread_mutex_t mutex_position = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_gyro = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_compass = PTHREAD_MUTEX_INITIALIZER;

void * thread_position(void *input){
  uint8_t *sn=(uint8_t*)input;
  int position_R, position_L, position_R_prev, position_L_prev, distance;
  extern int pos_x;
  extern int pos_y;
  float angle; 
  extern pthread_mutex_t mutex_position;
  get_tacho_position(sn[0],&position_R);
  get_tacho_position(sn[1],&position_L);
  position_R_prev=position_R;
  position_L_prev=position_L;

  while(1){
    get_tacho_position(sn[0],&position_R);
    get_tacho_position(sn[1],&position_L);
    distance=POSITION_TO_DISTANCE*(position_R+position_L-position_L_prev-position_R_prev)/2;
    angle=get_robot_rel_angle();
    //Critical section
    pthread_mutex_lock(&mutex_position);
    pos_x+=(int)distance*sin((double)(angle*DEG_TO_RAD));
    pos_y+=(int)distance*cos((double)(angle*DEG_TO_RAD));
    //printf("[D] Inside the thread : \n\
     pos_x = %d\n\
     pos_y = %d\n",pos_x,pos_y);
    //printf("[D] Inside the thread : \n\
     pos_x = %d\n\
     pos_y = %d\n\
     distance : %d\n\
     angle : %f \n\
     position_R : %d\n\
     position_L : %d\n\
     position_R_prev : %d\n\
     position_L_prev : %d\n",pos_x,pos_y,distance,angle,position_R,position_L,position_R_prev,position_L_prev);
    //printf("[D] Test of sin : %f, test of cos : %f \n ",cos((double)(angle*DEG_TO_RAD)),sin((double)(angle*DEG_TO_RAD)));
    pthread_mutex_unlock(&mutex_position);
    position_R_prev=position_R;
    position_L_prev=position_L;
    Sleep(250);
  }
}

void create_thread_position(uint8_t *sn){
  extern pthread_t threadpos;
  if(pthread_create(&threadpos, NULL, thread_position,sn)==-1){
    perror("pthread_create");
  }
}


void * thread_compass (void *input){
  uint8_t *sn_compass=(uint8_t*)input;
  extern pthread_mutex_t mutex_compass;
  extern float abs_angle_compass, rel_angle_compass;
  float initial_angle_compass;
  //Initialisation 
  for (int i=0; i<3; i++){
    pthread_mutex_lock(&mutex_compass);
    if ( !get_sensor_value0(*sn_compass, &abs_angle_compass)) {
      abs_angle_compass=0;
    }
    pthread_mutex_unlock(&mutex_compass);
  }
  pthread_mutex_lock(&mutex_compass);
  initial_angle_compass=abs_angle_compass;
  pthread_mutex_unlock(&mutex_compass);
  while (1){
    pthread_mutex_lock(&mutex_compass);
    if ( !get_sensor_value0(*sn_compass, &abs_angle_compass)){
      abs_angle_compass = 0;
    }
    rel_angle_compass=abs_angle_compass-initial_angle_compass;
    if (rel_angle_compass<0) rel_angle_compass+=360;
    pthread_mutex_unlock(&mutex_compass);
    Sleep(250);
  }
}

void * thread_gyro (void *input){
  uint8_t *sn_gyro=(uint8_t*)input;
  extern pthread_mutex_t mutex_gyro;
  extern float angle_gyro;
  //Initialisation 
  angle_gyro=0;
  while (1){
    pthread_mutex_lock(&mutex_gyro);
    if ( !get_sensor_value0(*sn_gyro, &angle_gyro)){
      angle_gyro = 0;
    }
    pthread_mutex_unlock(&mutex_gyro);
    Sleep(250);
  }
}

void create_thread_compass(uint8_t *sn_compass){
  extern pthread_t threadcompass;
  if(pthread_create(&threadcompass, NULL, thread_compass,sn_compass)==-1){
    perror("pthread_create");
  }
}

void create_thread_gyro(uint8_t *sn_gyro){
  extern pthread_t threadgyro;
  if(pthread_create(&threadgyro, NULL, thread_gyro,sn_gyro)==-1){
    perror("pthread_create");
  }
}

void * thread_print_coordinates (){
  while(1){
    print_robot_coordinates();
    Sleep(750);
  }
}

void create_thread_print_coordinates(){
  pthread_t threadprint;
  if(pthread_create(&threadprint, NULL, thread_print_coordinates,NULL)==-1){
    perror("pthread_create");
  }
}

float get_robot_angle(int choice){
  extern pthread_mutex_t mutex_compass,mutex_gyro;
  extern float rel_angle_compass,angle_gyro;
  float return_value;
  if (choice==0){ 
    pthread_mutex_lock(&mutex_compass);
    return_value=abs_angle_compass;
    pthread_mutex_unlock(&mutex_compass);
  }
  if (choice==1) {
    pthread_mutex_lock(&mutex_compass);
    pthread_mutex_lock(&mutex_gyro);
    int diff=angle_diff(rel_angle_compass,angle_gyro);
    if (rel_angle_compass<angle_gyro) return_value=rel_angle_compass+0.9*diff;
    else return_value=angle_gyro+0.1*diff;
    pthread_mutex_unlock(&mutex_compass);
    pthread_mutex_unlock(&mutex_gyro);
  }
  if (choice==2){
    pthread_mutex_lock(&mutex_gyro);
    return_value=angle_gyro;
    pthread_mutex_unlock(&mutex_gyro);
  }
  if (return_value>360) return_value-=360;
  return return_value;
}

float get_robot_abs_angle(){
  return get_robot_angle(0);
}
float get_robot_rel_angle(){
  return get_robot_angle(1);
}
float get_robot_angle_gyro(){
  return get_robot_angle(2);
}

int get_x_position(){
  extern pthread_mutex_t mutex_position;
  int return_value;

  pthread_mutex_lock(&mutex_position);
  return_value=pos_x;
  pthread_mutex_unlock(&mutex_position);
  return return_value;
}

int get_y_position(){
  extern pthread_mutex_t mutex_position;
  int return_value;

  pthread_mutex_lock(&mutex_position);
  return_value=pos_y;
  pthread_mutex_unlock(&mutex_position);
  return return_value;
}

void print_robot_abs_angle(){
  printf("[I] The absolute angle of the robot is : %f \n", get_robot_abs_angle());
}

void print_robot_rel_angle(){
  printf("[I] The relative angle of the robot is : %f \n", get_robot_rel_angle());
}

void print_robot_position(){
  printf("[I] The position of the robot is on the X axis: %d  and on the Y axis : %d \n", get_x_position(), get_y_position());
}

void print_robot_coordinates(){
  printf("[I] The position of the robot is : \n\
    on the X axis: %d\n\
    on the Y axis: %d\n\
    angle: %f \n", get_x_position(), get_y_position(), get_robot_rel_angle());
}

void create_threads(uint8_t *sn, uint8_t *sn_compass, uint8_t *sn_gyro){
  create_thread_position(sn);
  create_thread_compass(sn_compass);
  create_thread_gyro(sn_gyro);
}
