int main( int argc, char *argv[] );
void test_catapult(uint8_t sn, int choice_parameter);
void test_color(uint8_t sn_color, char choice_parameter);
void test_compass(uint8_t sn_compass, char choice_parameter);
void test_grab(uint8_t *sn, uint8_t sn3, int choice_parameter);
void first_course(uint8_t *sn, uint8_t sn_sonar, int speed,int turn_speed, int distance);
void test_movement(uint8_t *sn, uint8_t sn_sonar, int choice_parameter);
void test_sonar(uint8_t sn_sonar, int choice_parameter);
void test_turn(uint8_t *sn, uint8_t sn_sonar, uint8_t sn_compass, int turn_speed, char choice_parameter);