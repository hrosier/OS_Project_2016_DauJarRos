#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
//WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

void doorUpDown( uint8_t sn3 )
{
  FLAGS_T state;
  int port=65;
  
  if ( ev3_search_tacho_plugged_in(port+3,0, &sn3, 0 )) {
    int max_speed;
    get_tacho_max_speed( sn3, &max_speed );
    set_tacho_position_sp( sn3, 100 );
    set_tacho_stop_action_inx( sn3, TACHO_BRAKE );
    set_tacho_speed_sp( sn3, max_speed / 20 );
    set_tacho_ramp_up_sp( sn3, 300 );
    set_tacho_ramp_down_sp( sn3, 300 );
    set_tacho_command_inx( sn3, TACHO_RUN_TO_REL_POS );
    Sleep( 100 );
    do {
      get_tacho_state_flags( sn3, &state );
    } while ( state );

    printf( "run to absolute position...\n" );
    set_tacho_position_sp( sn3, -90 );
    set_tacho_speed_sp( sn3, max_speed / 20 );
    set_tacho_ramp_up_sp( sn3, 300 );
    set_tacho_ramp_down_sp( sn3, 300 );
    set_tacho_command_inx( sn3, TACHO_RUN_TO_REL_POS );
    do {
      get_tacho_state_flags( sn3, &state );
    } while ( state );
  } else {
    printf( "Moteur 3 is NOT found\n" );
  }

  printf("End of function grab \n");
}


void doorUp( uint8_t sn3 ) {

  FLAGS_T state;
  int port=65;
  
  if ( ev3_search_tacho_plugged_in(port+3,0, &sn3, 0 )) {
    int max_speed;
    get_tacho_max_speed( sn3, &max_speed );
    set_tacho_position_sp( sn3, 100 );
    set_tacho_stop_action_inx( sn3, TACHO_BRAKE );
    set_tacho_speed_sp( sn3, max_speed / 20 );
    set_tacho_ramp_up_sp( sn3, 300 );
    set_tacho_ramp_down_sp( sn3, 300 );
    set_tacho_command_inx( sn3, TACHO_RUN_TO_REL_POS );
    Sleep( 100 );
    do {
      get_tacho_state_flags( sn3, &state );
    } while ( state );
  } else {
    printf( "Moteur 3 is NOT found\n" );
  }

  printf("End of doorUp \n");
}

void doorDown( uint8_t sn3 )
{
  FLAGS_T state;
  int port=65;
  
  if ( ev3_search_tacho_plugged_in(port+3,0, &sn3, 0 )) {
    int max_speed;
    set_tacho_stop_action_inx( sn3, TACHO_BRAKE );
    get_tacho_max_speed( sn3, &max_speed );
    set_tacho_position_sp( sn3, -100 );
    set_tacho_speed_sp( sn3, max_speed / 20 );
    set_tacho_ramp_up_sp( sn3, 300 );
    set_tacho_ramp_down_sp( sn3, 300 );
    set_tacho_command_inx( sn3, TACHO_RUN_TO_REL_POS );
    do {
      get_tacho_state_flags( sn3, &state );
    } while ( state );

  } else {
    printf( "Moteur 3 is NOT found\n" );
  }

  printf("End of function doorUp \n");
}
