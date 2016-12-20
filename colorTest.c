#include "basic_include.h"
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

void printRGB(uint8_t sn_color){
  float val0, val1, val2;
  set_sensor_mode(sn_color, "RGB_RAW");
  get_sensor_value0(sn_color,&val0);
  get_sensor_value0(sn_color,&val1);
  get_sensor_value0(sn_color,&val2);
  printf("R : %d,  G: %d,   B:  %d \n",val0,val1,val2);
  Sleep(1000);
  fflush( stdout );
}

void printColor(uint8_t sn_color){
  int val;
  set_sensor_mode(sn_color, "COL-COLOR");
  if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
    val = 0;
  }
  printf( "\r(%s) \n", color[ val ]);
  Sleep(1000);
  fflush( stdout );
}

void main(){
  uint8_t sn_color;
  init_color(sn_color);
  for ( ; ; ){
    //printRGB(sn_color);
    printColor(sn_color);
  }
}
