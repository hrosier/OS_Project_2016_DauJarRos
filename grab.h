void door_ramp(uint8_t sn3, int position, int speed, int ramp_up, int ramp_down) ;
void door_up_ramp( uint8_t sn3, int speed, int ramp_up, int ramp_down) ;
void door_down_ramp( uint8_t sn3, int speed, int ramp_up, int ramp_down) ;
void door_up( uint8_t sn3, int speed) ;
void door_down( uint8_t sn3, int speed) ;
void catch_dist(uint8_t *sn, uint8_t sn3, int speed, int position);
void scan_angle_distance(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int distance);
void door_up_down( uint8_t sn3, int speed );
