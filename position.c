#include "basic_include.h"
#include "shared.h"
#include <pthread.h> 
#include "position.h"

void * thread_position(void *input){
  uint8_t *sn=(uint8_t*)input;
  int position_R, position_L, position_R_prev, position_L_prev, distance;
  extern int pos_x;
  extern int pos_y;
  extern int direction; //North,East,south,West 
  extern pthread_mutex_t mutex ;
  get_tacho_position(sn[0],&position_R);
  get_tacho_position(sn[1],&position_L);
  position_R_prev=position_R;
  position_L_prev=position_L;

  while(1){
    get_tacho_position(sn[0],&position_R);
    get_tacho_position(sn[1],&position_L);
    distance=(position_R+position_L-position_L_prev-position_R_prev)/2;
    distance=distance*480/1000;
    position_R_prev=position_R;
    position_L_prev=position_L;

    //Critical section
    pthread_mutex_lock(&mutex);
    //When we will have the compass we will be able to get a better position : 
    //pos_x+=distance*cos(angle);
    //pos_y+=distance*sin(angle);
    if(direction==0){
      pos_x+=distance; 
    }
    else {
      if (direction==1){
        pos_y+=distance;
      }
      else{ 
        if (direction==2){
          pos_x-=distance;
        }
        else {
          pos_y-=distance;
        }
      }
    }
    printf("pos_x = %d ,  pos_y = %d \n",pos_x,pos_y);
    pthread_mutex_unlock(&mutex);
    Sleep(500);
  }
}
