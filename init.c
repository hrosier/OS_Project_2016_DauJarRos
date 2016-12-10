#include "basic_include.h"
#include "catapult.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"

void init(uint8_t sn1, uint8_t sn2, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, uint8_t *sn, int *max_speed, int *max_speed_door, int *max_speed_cata){
  if ( ev3_init() == -1 ) return ;
  while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
  ev3_sensor_init();

  int port=65;
  if ( ev3_search_tacho_plugged_in(port,0, &sn1, 0 )) {
    if ( ev3_search_tacho_plugged_in(port+1,0, &sn2, 0 )) { 
      if ( ev3_search_tacho_plugged_in(port+3,0, &sn3, 0 )) { 
        if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
          if (ev3_search_sensor(LEGO_EV3_COLOR, &sn_color,0)){
            sn[0]=sn1;
            sn[1]=sn2;
            multi_set_tacho_position_sp(sn, 0);
            multi_set_tacho_position(sn, 0);
            set_tacho_position(sn3, 0);
            set_tacho_position(sn4, 0);
            set_tacho_stop_action_inx( sn3, TACHO_HOLD );
            set_tacho_stop_action_inx( sn4, TACHO_HOLD );
            get_tacho_max_speed(sn[0], max_speed);
            get_tacho_max_speed(sn3, max_speed_door);
            get_tacho_max_speed(sn4, max_speed_cata);
          }
          else {
            printf("Color sensor not found\n");
          }
        }
        else {
          printf( "Sonar is NOT found\n" );
        }
      }
      else {
        printf( "Door motor is NOT found\n" );
      } 
    }
    else {
      printf( "Moteur 2 is NOT found\n" );
    }
  }
  else {
    printf( "Moteur 1 is NOT found\n" );
  }
}
