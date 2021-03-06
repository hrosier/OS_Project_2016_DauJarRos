// Signatures of the different threads //
void * thread_position(void *input);
void * thread_compass (void *input);
void * thread_gyro (void *input);
void * thread_send_message (void *input);
void * thread_print_coordinates ();

// The functions that create the threads //
void create_thread_position(uint8_t *sn);
void create_thread_send_message(int *s);
void create_thread_compass(uint8_t *sn_compass);
void create_thread_gyro(uint8_t *sn_gyro);
void create_thread_print_coordinates();
void create_threads(uint8_t *sn, uint8_t *sn_compass, uint8_t *sn_gyro);

// the function that fetch/set some value used for localisation //
float get_robot_angle(int choice);
float get_robot_abs_angle();
float get_robot_rel_angle();
float get_robot_angle_gyro();
int get_x_position();
int get_y_position();
void set_x_position(int x);
void set_y_position(int y);
void set_position(int x, int y);
void set_side_angle(int side);
void print_robot_abs_angle();
void print_robot_rel_angle();
void print_robot_position();
void print_robot_coordinates();
