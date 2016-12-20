#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

float get_sonar(uint8_t sn_sonar){
  float value;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  printf( "\r(%f) \n", value);
  fflush( stdout );
  return value;
}
