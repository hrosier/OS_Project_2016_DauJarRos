void * thread_position(void *input);
void create_thread_position(pthread_t *threadpos,uint8_t *sn);
void * thread_angle(void *input);
void create_thread_angle(pthread_t *threadangle, uint8_t *sn_compass);
float get_robot_angle();
void print_robot_angle();
