int main( int argc, char *argv[] );
void test_catapult(uint8_t sn, int *choice_parameters);
void test_color(uint8_t sn_color, int *choice_parameters);
void test_compass(uint8_t sn_compass, int *choice_parameters);
void test_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters);
void first_course(uint8_t *sn, uint8_t sn_sonar, int speed,int turn_speed, int distance);
void test_movement(uint8_t *sn, uint8_t sn_sonar, int *choice_parameters);
void test_sonar(uint8_t sn_sonar, int *choice_parameters);
void test_turn(uint8_t *sn, uint8_t sn_sonar, uint8_t sn_compass, int *choice_parameters);
void test_movement_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters);
void test_gyro(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, uint8_t sn_gyro, int *choice_parameters);
