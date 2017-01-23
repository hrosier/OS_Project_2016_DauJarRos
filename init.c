#include "basic_include.h"
#include "catapult.h"
#include "grab.h"
#include "movement.h"
#include "turn.h"
#include "init.h"
#include "position.h"

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
  set_tacho_stop_action_inx( *sn3, TACHO_COAST );
  ev3_uninit();
}

void init_all(uint8_t *sn1, uint8_t *sn2, uint8_t *sn3, uint8_t *sn4, uint8_t *sn_sonar, uint8_t *sn_color, uint8_t *sn_compass, uint8_t *sn_gyro, uint8_t *sn, int *s){
  init();
  init_wheels(sn1,sn2,sn);
  init_door(sn3);
  init_catapult(sn4);
  init_color(sn_color);
  init_sonar(sn_sonar);
  init_gyro(sn_gyro);
  init_compass(sn_compass);
  init_threads(sn,sn_compass,sn_gyro,s);
}

void init_wheels(uint8_t *sn1, uint8_t *sn2, uint8_t *sn){
  if ( ev3_search_tacho_plugged_in(PORT_WHEEL1,0, sn1, 0 )) {
    if ( ev3_search_tacho_plugged_in(PORT_WHEEL2,0, sn2, 0 )) {
      set_tacho_stop_action_inx( *sn1, TACHO_RESET );
      set_tacho_stop_action_inx( *sn2, TACHO_RESET );
      sn[0]=*sn1;
      sn[1]=*sn2;
      multi_set_tacho_position_sp(sn, 0);
      multi_set_tacho_position(sn, 0);
    }
    else {
      printf("[X] Moteur 2 is NOT found\n" );
    }
  }
  else {
    printf("[X] Moteur 1 is NOT found\n" );
  }
}

void init_door_or_catapult(uint8_t *sn3,int port){
  if ( ev3_search_tacho_plugged_in(port,0, sn3, 0 )) {
    set_tacho_stop_action_inx( *sn3, TACHO_RESET);
    set_tacho_position(*sn3, 0);
    //if (port==PORT_CATAPULT){
    set_tacho_stop_action_inx( *sn3, TACHO_HOLD );
    //}
  }
  else {
    if (port==PORT_DOOR){
    printf("[X] Door motor is NOT found\n" );
    }
    else {
    printf("[X] Catapult motor is NOT found\n" );
    }
  }
}

void init_catapult(uint8_t *sn4){
  init_door_or_catapult(sn4,PORT_CATAPULT);
}

void init_door(uint8_t *sn3){
  init_door_or_catapult(sn3,PORT_DOOR);
}

void init_sonar(uint8_t *sn_sonar ){
  if (ev3_search_sensor(LEGO_EV3_US, sn_sonar,0)){
    set_sensor_mode(*sn_sonar,"US-DIST-CM");
  }
  else {
    printf("[X] Sonar is NOT found\n" );
  }
}

void init_gyro (uint8_t *sn_gyro ){
  if (ev3_search_sensor(LEGO_EV3_GYRO, sn_gyro,0)){
        set_sensor_mode(*sn_gyro, "GYRO-RATE");
        set_sensor_mode(*sn_gyro, "GYRO-ANG");
        //The calibration takes time 
        Sleep(500);
  }
  else {
    printf("[X] Gyroscope  is NOT found\n" );
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

void init_threads(uint8_t *sn, uint8_t *sn_compass, uint8_t *sn_gyro, int *s){
  create_threads(sn,sn_compass,sn_gyro,s);
}
 
