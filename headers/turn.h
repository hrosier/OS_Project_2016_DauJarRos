void mono_tacho_settings(uint8_t sn, int speed, int ramp_up, int ramp_down, INX_T FLAGS);
void turn_forever_ramp(uint8_t sn, int speed, int ramp_up, int ramp_down);
void turn_timed_ramp(uint8_t sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, int time, int search_obstacle);
void turn_to_abs_pos_ramp(uint8_t sn, int speed, int ramp_up, int ramp_down);
void turn_to_rel_pos_ramp(uint8_t sn, int pos,int speed, int ramp_up, int ramp_down);
void mono_check_for_obstacle(uint8_t sn_sonar, uint8_t sn);
void bi_turn_pos_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int position, int ramp_up, int ramp_down, char search_obstacle);
void bi_turn_angle(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, char search_obstacle);
void bi_standard_turn_angle(uint8_t *sn, uint8_t sn_sonar, int angle, char search_obstacle);
void bi_turn_angle_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int ramp_up, int ramp_down, char search_obstacle);
void bi_turn_angle2(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, char search_obstacle);
void u_turn_right_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, char search_obstacle);
void u_turn_left_ramp(uint8_t *sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down, char search_obstacle);
void bi_turn_pos(uint8_t *sn,uint8_t sn_sonar, int speed, int position, char search_obstacle);
void u_turn_right(uint8_t *sn, uint8_t sn_sonar,int speed, char search_obstacle);
void u_turn_left(uint8_t *sn, uint8_t sn_sonar, int speed, char search_obstacle);
void turn_forever_unless_obstacle_ramp(uint8_t sn, uint8_t sn_sonar, int speed, int ramp_up, int ramp_down);
void turn_timed_unless_obstacle_ramp(uint8_t sn, uint8_t sn_sonar ,int speed ,int ramp_up, int ramp_down, int time);
void turn_forever(uint8_t sn, int speed);
void turn_timed(uint8_t sn, uint8_t sn_sonar, int speed, int time);
void turn_forever_unless_obstacle(uint8_t sn, uint8_t sn_sonar, int speed);
void turn_timed_unless_obstacle(uint8_t sn, uint8_t sn_sonar, int speed, int time);
void turn_to_abs_pos(uint8_t sn, int speed);
void turn_to_rel_pos(uint8_t sn, int pos, int speed);
void turn_right_foward(uint8_t *sn, int speed);
void turn_left_foward(uint8_t *sn, int speed);
void turn_right_backward(uint8_t *sn, int speed);
void turn_left_backward(uint8_t *sn, int speed);
void turn_to_angle(uint8_t *sn, uint8_t sn_sonar, int initial_speed, int angle, char rel, char search_obstacle);
