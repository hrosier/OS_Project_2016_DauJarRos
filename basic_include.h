#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "common_variables.h"
#include "init.h"
#include "grab.h"
#include "movement.h"
#include "sonar.h"
#include "color.h"
#include "catapult.h"
#include "turn.h"
#include "localisation.h"
#include "bluetooth.h"
#include "testFunctions.h"
#include "final.h"
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
#include <windows.h>
// UNIX //////////////////////////////////////////
#else
#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
//////////////////////////////////////////////////
#endif
