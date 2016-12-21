#include "basic_include.h"
#include "catapult.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
#include "init.h"

#define PORT_WHEEL1 65
#define PORT_WHEEL2 66
#define PORT_CATAPULT 67
#define PORT_DOOR 68

void init(){
  if ( ev3_init() == -1 ){
    perror("Failed to init");
    return ;
  }
  while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
  ev3_sensor_init();
}

void uninit (uint8_t *sn3, uint8_t *sn4){
  ev3_uninit();
  set_tacho_stop_action_inx( *sn3, TACHO_COAST );
}

void init_all(uint8_t *sn1, uint8_t *sn2, uint8_t *sn3, uint8_t *sn4, uint8_t *sn_sonar, uint8_t *sn_color, uint8_t *sn_compass, uint8_t *sn, int *max_speed, int *max_speed_door, int *max_speed_cata){
  init();
  init_wheels(sn1,sn2,sn,max_speed);
  init_door(sn3,max_speed_door);
  init_catapult(sn4,max_speed_cata);
  init_color(sn_color);
  init_sonar(sn_sonar);
  init_compass(sn_compass);
}

void init_wheels(uint8_t *sn1, uint8_t *sn2, uint8_t *sn, int *max_speed){
  if ( ev3_search_tacho_plugged_in(PORT_WHEEL1,0, sn1, 0 )) {
    if ( ev3_search_tacho_plugged_in(PORT_WHEEL2,0, sn2, 0 )) {
      sn[0]=*sn1;
      sn[1]=*sn2;
      multi_set_tacho_position_sp(sn, 0);
      get_tacho_max_speed(sn[0], max_speed);
      multi_set_tacho_position(sn, 0);
    }
    else {
      printf( "Moteur 2 is NOT found\n" );
    }
  }
  else {
    printf( "Moteur 1 is NOT found\n" );
  }
}

void init_door_or_catapult(uint8_t *sn3, int *max_speed,int port){
  if ( ev3_search_tacho_plugged_in(port,0, sn3, 0 )) {
    set_tacho_position(*sn3, 0);
    get_tacho_max_speed(*sn3, max_speed);
    //if (port==PORT_CATAPULT){
    set_tacho_stop_action_inx( *sn3, TACHO_HOLD );
    //}
  }
  else {
    if (port==PORT_DOOR){
    printf( "Door motor is NOT found\n" );
    }
    else {
    printf( "Catapult motor is NOT found\n" );
    }
  }
}

void init_catapult(uint8_t *sn4, int *max_speed_cata){
  init_door_or_catapult(sn4,max_speed_cata,PORT_CATAPULT);
}

void init_door(uint8_t *sn3, int *max_speed_door){
  init_door_or_catapult(sn3,max_speed_door,PORT_DOOR);
}

void init_sonar(uint8_t *sn_sonar ){
  if (ev3_search_sensor(LEGO_EV3_US, sn_sonar,0)){
  }
  else {
    printf( "Sonar is NOT found\n" );
  }
}

void init_color(uint8_t *sn_color){
    if (ev3_search_sensor(LEGO_EV3_COLOR, sn_color,0)){
        set_sensor_mode(*sn_color, "COL-COLOR");
    }
    else {
      printf("Color sensor not found\n");
    }
}

void init_compass(uint8_t *sn_compass){
  if (ev3_search_sensor(HT_NXT_COMPASS, sn_compass,0)){
      set_sensor_mode(*sn_compass, "COMPASS");
  }
  else {
    printf("Compass sensor not found\n");
  }
}
