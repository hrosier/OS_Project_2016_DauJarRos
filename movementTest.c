#include "basic_include.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"

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

  for ( i = 0; i < DESC_LIMIT; i++ ) {
    if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
      printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
      printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
      printf("  port = %d %d\n", ev3_tacho_desc_port(i), ev3_tacho_desc_extport(i));
    }
  }

  //Run all sensors
  ev3_sensor_init();
  int port=65;
  //for (port=65; port<69; port++){
  if ( ev3_search_tacho_plugged_in(port,0, &sn1, 0 )) {
    int max_speed;
    int max_speed_door;
    if ( ev3_search_tacho_plugged_in(port+1,0, &sn2, 0 )) { 
      if ( ev3_search_tacho_plugged_in(port+3,0, &sn3, 0 )) { 
        if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
          sn[0]=sn1;
          sn[1]=sn2;
          multi_set_tacho_position_sp(sn, 0);
          get_tacho_max_speed(sn[0], &max_speed);
          get_tacho_max_speed(sn3, &max_speed_door);
          int door_speed=max_speed_door/2;
          int speed=max_speed/2;
          int position;
          printf("vitesse des roues : %d \n",speed);

          get_tacho_position(sn1,&position);
          printf("position du moteur : %d\n",position);
          printf("I am running for a certain amount of time \n");
          run_distance(sn,speed,500,0);
          Sleep(5000);
          run_distance(sn,speed,-500,0);
          Sleep(5000);

          u_turn_right(sn,speed,0);
          get_tacho_position(sn1,&position);
          printf("position du moteur : %d\n",position);
          printf("I am running for a certain amount of time \n");
          run_distance_unless_obstacle(sn,sn_sonar,speed,1000);
          Sleep(5000);
          get_tacho_position(sn1,&position);
          printf("position du moteur : %d\n",position);


//          printf("I scan for the ball\n");
//          scan_angle_distance(sn,sn_sonar,speed,45,300);
//          Sleep(5000);
//
//          printf("I scan for the ball\n");
//          scan_angle_distance(sn,sn_sonar,speed,-90,300);
//          Sleep(5000);
//
//          printf("I try to catch it\n");
//          catch_dist(sn,sn3,max_speed/2,3000);
//          Sleep(3000);
//
//          // To keep the door close
//          set_tacho_position(sn3,0);
//          set_tacho_command_inx(sn3, TACHO_RUN_TO_ABS_POS);
//
//          printf(" I gonna do a U turn \n");
//          u_turn_right(sn,max_speed/2,0);
//          Sleep(1000);
//
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
}
