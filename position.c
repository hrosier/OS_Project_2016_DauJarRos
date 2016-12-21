#include "basic_include.h"
#include <math.h> 
#include "shared.h"
#include "position.h"

void * thread_position(void *input){
  uint8_t *sn=(uint8_t*)input;
  int position_R, position_L, position_R_prev, position_L_prev, distance;
  extern int pos_x;
  extern int pos_y;
  extern float robot_angle; //North,East,south,West 
  extern pthread_mutex_t mutex_position;
  get_tacho_position(sn[0],&position_R);
  get_tacho_position(sn[1],&position_L);
  position_R_prev=position_R;
  position_L_prev=position_L;

  while(1){
    get_tacho_position(sn[0],&position_R);
    get_tacho_position(sn[1],&position_L);
    distance=POSITION_TO_DISTANCE*(position_R+position_L-position_L_prev-position_R_prev)/2;
    position_R_prev=position_R;
    position_L_prev=position_L;
    //Critical section
    pthread_mutex_lock(&mutex_position);
    pthread_mutex_lock(&mutex_angle);
    //When we will have the compass we will be able to get a better position : 
    pos_x+=distance*cos(robot_angle);
    pos_y+=distance*sin(robot_angle);
    pthread_mutex_unlock(&mutex_angle);
    printf("pos_x = %d ,  pos_y = %d \n",pos_x,pos_y);
    pthread_mutex_unlock(&mutex_position);
    Sleep(500);
  }
}

void create_thread_position(pthread_t *threadpos,uint8_t *sn){
  if(pthread_create(threadpos, NULL, thread_position,sn)==-1){
    perror("pthread_create");
  }
}

void * thread_angle(void *input){
  uint8_t *sn_compass=(uint8_t*)input;
  extern pthread_mutex_t mutex_angle;
  extern float robot_angle;

  while (1){
    pthread_mutex_lock(&mutex_angle);
    if ( !get_sensor_value0(*sn_compass, &robot_angle)) {
      robot_angle = 0;
    }
    pthread_mutex_unlock(&mutex_angle);
    Sleep(500);
  }
}

void create_thread_angle(pthread_t *threadangle, uint8_t *sn_compass){
  if(pthread_create(threadangle, NULL, thread_angle,sn_compass)==-1){
    perror("pthread_create");
  }
}

float get_robot_angle(){
  extern pthread_mutex_t mutex_angle;
  extern float robot_angle;
  float return_value;

  pthread_mutex_lock(&mutex_angle);
  return_value=robot_angle;
  pthread_mutex_unlock(&mutex_angle);
  return return_value;
}

void print_robot_angle(){
  printf("The angle of the robot is : %f \n", get_robot_angle());
}
