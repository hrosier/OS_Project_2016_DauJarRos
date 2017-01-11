#include "basic_include.h"
#include "sonar.h"

int main( void )
{
  uint8_t sn_sonar;
  init();
  init_sonar(&sn_sonar);
  while(true){
    print_sonar(sn_sonar);
    Sleep(1000);
  }
  ev3_uninit();
  return ( 0 );
}
