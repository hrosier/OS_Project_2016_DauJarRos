#include "basic_include.h"
#include "color.h"

int main(){
  uint8_t sn_color;
  init_color(&sn_color);
  for ( ; ; ){
    //printRGB(sn_color);
    print_color(sn_color);
  }
  return 0;
}
