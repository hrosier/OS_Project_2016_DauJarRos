/* this file contains the functions used to deal with the color sensor */


#include "basic_include.h"
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#ifndef COLOR_COUNT
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))
#endif

void print_RGB(uint8_t sn_color){
  float val0, val1, val2;
  // we change the mode of the sensor to RGB_RAW to get the trichromic values
  set_sensor_mode(sn_color, "RGB_RAW");
  get_sensor_value0(sn_color,&val0);
  get_sensor_value0(sn_color,&val1);
  get_sensor_value0(sn_color,&val2);
  printf("R : %f,  G: %f,   B:  %f \n",val0,val1,val2);
  Sleep(1000);
  fflush( stdout );
}

void print_color(uint8_t sn_color){
  int val;
  set_sensor_mode(sn_color, "COL-COLOR");
  if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
    val = 0;
  }
  printf( "\r(%s) \n", color[ val ]);
  Sleep(1000);
  fflush( stdout );
}
