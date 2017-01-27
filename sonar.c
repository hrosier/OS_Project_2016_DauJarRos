/* this file contains the functions used to deal with the sonar sensor */

#include "basic_include.h"

float get_sonar(uint8_t sn_sonar){
  float value;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  fflush( stdout );
  return value;
}

void print_sonar(uint8_t sn_sonar){
  printf("[I] The value of the sonar sensor : %f\n", get_sonar(sn_sonar));
}
