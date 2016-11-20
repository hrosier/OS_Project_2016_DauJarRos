#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "grab.h"
#include "movement.h"
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
  int i;
  uint8_t sn1,sn2,sn3;
  uint8_t sn[2];
  uint8_t sn_sonar;
  char s[ 256 ];
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
  while ( ev3_tacho_init() < 1 ) Sleep( 1000 );

  printf( "*** ( EV3 ) Hello! ***\n" );
  printf( "Found tacho motors:\n" );
  for ( i = 0; i < DESC_LIMIT; i++ ) {
    if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
      printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
      printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
      printf("  port = %d %d\n", ev3_tacho_desc_port(i), ev3_tacho_desc_extport(i));
    }
  }

  //Run all sensors
  ev3_sensor_init();

  printf( "Found sensors:\n" );
  for ( i = 0; i < DESC_LIMIT; i++ ) {
    if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
      printf( "  type = %s\n", ev3_sensor_type( ev3_sensor[ i ].type_inx ));
      printf( "  port = %s\n", ev3_sensor_port_name( i, s ));
      if ( get_sensor_mode( i, s, sizeof( s ))) {
        printf( "  mode = %s\n", s );
      }
      if ( get_sensor_num_values( i, &n )) {
        for ( ii = 0; ii < n; ii++ ) {
          if ( get_sensor_value( ii, i, &val )) {
            printf( "  value%d = %d\n", ii, val );
          }
        }
      }
    }
  }


  int port=65;
  //for (port=65; port<69; port++){
  if ( ev3_search_tacho_plugged_in(port,0, &sn1, 0 )) {
    int max_speed;
    if ( ev3_search_tacho_plugged_in(port+1,0, &sn2, 0 )) { 
      if ( ev3_search_tacho_plugged_in(port+3,0, &sn3, 0 )) { 
        if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
          sn[1]=sn2;
          sn[0]=sn1;
          multi_set_tacho_position_sp(sn, 0);
          get_tacho_max_speed(sn[0], &max_speed);

          run_forever_unless_obstacle(sn,sn_sonar,max_speed/3);
          //Open the door
          doorUp(sn3);

          // Go foward a little
          run_timed(sn,max_speed/5,2000);

          // close the door 
          doorDown(sn3);

          // To keep the door close
          set_tacho_position_sp(sn3,0);
          set_tacho_command_inx(sn3, TACHO_RUN_TO_ABS_POS);
          
          //go back
          run_to_abs_pos(sn, max_speed/3);
        } else {
          printf( "Sonar is NOT found\n" );
        }
      } else {
        printf( "Moteur 3 is NOT found\n" );
      } 
    } else {
      printf( "Moteur 2 is NOT found\n" );
    } 
  } 
  else {
    printf( "Moteur 1 is NOT found\n" );
  }


  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );

  return ( 0 );
}
