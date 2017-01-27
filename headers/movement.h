/* this file contains functions'signature used to deal with the movement of the robot (except from its rotation -> cf turn.c) */


// If the robot is running, it stops
void stop_running(uint8_t *sn);

// Modified the settings of the motors
void tacho_settings(uint8_t *sn, int speed, int ramp_up, int ramp_down, INX_T FLAGS);

// the search_obstacle flag let us decide the robot's behaviour if it encounters an obstacle 
// the position param correspond to the position_sp value of the motors
// (0 it doesn't do anything, 1 it stops, 2 the robot continue running and the decision is decided after the call of the function) 
void run_to_rel_pos_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int position, int ramp_up, int ramp_down, int search_obstacle);

void continue_until_stop_running(uint8_t *sn);

// The robot continue moving until it finishes or reaches an obstacle
void check_for_obstacle(uint8_t *sn, uint8_t sn_sonar, int distance);

void run_distance(uint8_t *sn, uint8_t sn_sonar, int speed, int distance, int search_obstacle);

void run_distance_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed, int distance);

/** the robot goes diagonaly to the destination, the parameter numbber_try let us choose the precision. If it is set to 2 this function will be called 2 times recursivly.
 */
void go_to_position1(uint8_t *sn, uint8_t sn_sonar, int dest_pos_x, int dest_pos_y, int speed, int turn_speed, int number_try, char check_for_obstacle);

///////// Not used function ////////

void run_forever_ramp(uint8_t *sn, int speed, int ramp_up, int ramp_down);

void run_timed_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, int time, int search_obstacle);

void run_forever_unless_obstacle_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down);

void run_timed_unless_obstacle_ramp(uint8_t *sn, uint8_t sn_sonar ,int speed ,int ramp_up, int ramp_down, int time);

void run_forever(uint8_t *sn, int speed);

void run_timed(uint8_t *sn, uint8_t sn_sonar, int speed, int time, char check_for_obstacle);

void run_forever_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed);

void run_timed_unless_obstacle(uint8_t *sn, uint8_t sn_sonar, int speed, int time);

void run_to_abs_pos(uint8_t *sn, uint8_t sn_sonar, int speed, int search_obstacle);

void run_to_abs_pos_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, int search_obstacle);

void run_distance_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int distance, int ramp_up, int ramp_down, int search_obstacle);

void correct_position(uint8_t *sn, uint8_t sn_sonar, int speed,int dest_pos_x,int dest_pos_y, char check_for_obstacle);

void go_to_position2(uint8_t *sn, uint8_t sn_sonar, int dest_pos_x, int dest_pos_y, int speed, int turn_speed, char check_for_obstacle);
