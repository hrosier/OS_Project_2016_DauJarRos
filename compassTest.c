#include "basic_include.h"
#include "init.h"
#include "position.h"
#include "turn.h"

int main( void )
{
  uint8_t sn_compass;
  int val;
  float value;
  pthread_t threadangle;
  extern float robot_angle; //North,East,south,West
  extern pthread_mutex_t mutex_angle ;

  init();
  init_compass(&sn_compass);
  if(pthread_create(&threadangle, NULL, thread_angle, &sn_compass)==-1){
    perror("pthread_create");
  }
  while (1)  {
    pthread_mutex_lock(&mutex_angle);
    printf("Robot angle is : %f \n",robot_angle);
    pthread_mutex_unlock(&mutex_angle);
    Sleep(1000);
  } 
  ev3_uninit();
  return ( 0 );
}
