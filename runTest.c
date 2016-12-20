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
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

static bool _check_pressed( uint8_t sn )
{
  int val;

  if ( sn == SENSOR__NONE_ ) {
    return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
  }
  return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}


int main( void )
{
  int i;
  uint8_t sn1,sn2,sn3;
  uint8_t sn[2];
  FLAGS_T state;
  uint8_t sn_touch;
  uint8_t sn_color;
  uint8_t sn_compass;
  uint8_t sn_sonar;
  uint8_t sn_mag;
  char s[ 256 ];
  int val;
  float value;
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
          printf( "LEGO_EV3_M_MOTOR 1 is found, run for 2 sec...\n" );
          get_tacho_max_speed( sn1, &max_speed );
          printf("  max speed = %d\n", max_speed );
          multi_set_tacho_position_sp( sn, 0 );
          multi_set_tacho_stop_action_inx( sn, TACHO_COAST );
          multi_set_tacho_speed_sp( sn, max_speed / 3 );
          multi_set_tacho_ramp_up_sp( sn, 2000 );
          multi_set_tacho_ramp_down_sp( sn, 2000 );
          multi_set_tacho_command_inx( sn, TACHO_RUN_FOREVER );
          /* Wait tacho stop */
          printf("SONAR found, reading sonar...\n");
          if ( !get_sensor_value0(sn_sonar, &value )) {
            value = 0;
          }
          //While no obstacle run tacho 
          while (value>200 || value == 0){
            get_sensor_value0(sn_sonar, &value);
          }
          multi_set_tacho_command_inx( sn, TACHO_STOP );
          Sleep( 100 );

          //Open the door
          doorUp(sn3);

          // Go foward a little
          multi_set_tacho_position_sp( sn, 1000 );
          multi_set_tacho_stop_action_inx( sn, TACHO_COAST );
          multi_set_tacho_speed_sp( sn, max_speed / 3 );
          multi_set_tacho_ramp_up_sp( sn, 2000 );
          multi_set_tacho_ramp_down_sp( sn, 2000 );
          multi_set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );

          // Wait until he finishs running
          do {
            get_tacho_state_flags( sn1, &state );
          } while ( state );
          Sleep(500);

          // close the door 
          doorDown(sn3);

          // To keep the door close
          set_tacho_position_sp(sn3,0);
          set_tacho_command_inx(sn3, TACHO_RUN_TO_ABS_POS);
          
          //go back
          multi_set_tacho_position_sp(sn,0);
          multi_set_tacho_speed_sp( sn, max_speed / 4 );
          multi_set_tacho_ramp_up_sp( sn, 200 );
          multi_set_tacho_ramp_down_sp( sn, 200 );
          multi_set_tacho_command_inx( sn, TACHO_RUN_TO_ABS_POS );
          do {
            get_tacho_state_flags( sn1, &state );
          } while ( state );
          for ( i = 0; i < 2; i++ ) {
            multi_set_tacho_command_inx( sn, TACHO_RUN_TO_ABS_POS );
            Sleep( 500 );
          }       
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
