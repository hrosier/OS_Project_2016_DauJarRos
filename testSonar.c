#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
#include <windows.h>
// UNIX //////////////////////////////////////////
#else
#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
//////////////////////////////////////////////////
#endif
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

int main( void )
{
  uint8_t sn_sonar;
  int val;
  uint32_t n, ii;
#ifndef __ARM_ARCH_4T__
  /* Disable auto-detection of the brick (you have to set the correct address below) */
  ev3_brick_addr = "192.168.2.3";
#endif
  if ( ev3_init() == -1 ) return ( 1 );
#ifndef __ARM_ARCH_4T__
  printf( "The EV3 brick auto-detection is DISABLED,\nwaiting %s online with plugged tacho...\n", ev3_brick_addr );
#else
  printf( "Waiting tacho is plugged...\n" );
#endif

  //Run all sensors
  ev3_sensor_init();
  if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
    float value;
    while(true){
    value = get_sonar(sn_sonar);
    Sleep(1000);
    }
  } else {
    printf( "Sonar is NOT found\n" );
  }

  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );

  return ( 0 );
}
