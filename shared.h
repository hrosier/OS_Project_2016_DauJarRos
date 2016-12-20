#include <pthread.h>

int pos_x=0;
int pos_y=0;
int direction=0; //North,south, etc
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

