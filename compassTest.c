#include "basic_include.h"
#include "init.h"
#include "position.h"
#include "turn.h"

int main( int argc, char * argv[] )
{
  uint8_t sn_compass;
  int val;
  float value;

  init();
  init_compass(&sn_compass);
  create_thread_angle(&sn_compass);
  while (1)  {
    //printf("Robot angle is : %f \n",robot_angle);
    if (atoi(argv[1])==1){
      print_robot_rel_angle();
      print_robot_abs_angle();
      Sleep(2000);
    }
    if (atoi(argv[1])==2){
      print_robot_abs_angle();
      Sleep(2000);
    }
    if (atoi(argv[1])==3){
      if ( !get_sensor_value0(sn_compass, &value)) {
        value = 0;
      } 
      printf("robot angle from north : %f \n ", value);
      Sleep(2000);
    }
  }
  ev3_uninit();
  return ( 0 );
}
