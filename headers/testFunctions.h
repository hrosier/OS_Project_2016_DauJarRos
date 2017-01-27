/* The functions below are called by mainTest to test the different important functions used for the competition*/

// fonction called by mainTest to test the several functions of the catapult
void test_catapult(uint8_t sn, int *choice_parameters);

// fonction called by mainTest to test the several functions of the color sensor
void test_color(uint8_t sn_color, int *choice_parameters);

// fonction called by mainTest to test the several grab function
void test_compass(uint8_t sn_compass, int *choice_parameters);

// fonction called by mainTest to test the several grab function
void test_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters);

// fonction called by mainTest to test the movement of the robot
void test_movement(uint8_t *sn, uint8_t sn_sonar, int *choice_parameters);

// fonction called by mainTest to make the robot make a small circuit (run around a 50cm width square). Called by test_movement
void first_course(uint8_t *sn, uint8_t sn_sonar, int speed,int turn_speed, int distance);

// fonction called by mainTest to test the several sonar functions
void test_sonar(uint8_t sn_sonar, int *choice_parameters);

// fonction called by mainTest to test the several turn functions
void test_turn(uint8_t *sn, uint8_t sn_sonar, int *choice_parameters);

// fonction called by mainTest to test the several gyroscope functions
void test_gyro(uint8_t sn_gyro, int *choice_parameters);

// fonction called by mainTest to test the grab and movement functions at the same time
void test_movement_grab(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *choice_parameters);

/** 
* \brief this function is called by the main of mainTest.c to test/debug the BT features of the robot
* \param int* s : the adress where is stored the number corresponding to the BT connexion  
* \return int *choice_parameters : the list of parameter we can pass to the executable :
    1
    2
    3 
*/
void test_bluetooth(int *s, int *choice_parameters);
