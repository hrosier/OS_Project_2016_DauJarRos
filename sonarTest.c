#include "basic_include.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"

int main( void )
{
  uint8_t sn_sonar;
  int val;
  uint32_t n, ii;
  float value;

  init_sonar(sn_sonar);
  while(true){
    value = get_sonar(sn_sonar);
    Sleep(1000);
  }
  ev3_uninit();
  return ( 0 );
}
