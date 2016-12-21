#include <pthread.h>

#define TURN_SPEED 430 //half of the max speed
#define RIGHT_ANGLE 1015
int pos_x=0;
int pos_y=0;
float robot_angle; //angle from the north
pthread_mutex_t mutex_position = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_angle = PTHREAD_MUTEX_INITIALIZER;

