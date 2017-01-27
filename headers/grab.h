/** 
* \brief this function makes the motor, in charge of the doors, go to at a certain position at a certain speed where the accelerations are specified 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the motor will turn
* \param int ramp_up: the time the motor will take to reach the required speed
* \param int ramp_down : the time the motor will stop
*/
void door_ramp(uint8_t sn3, int position, int speed, int ramp_up, int ramp_down) ;


/** 
* \brief this function open the doors at a certain speed where the accelerations are specified (used at the beginning to test some values)
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the motor will turn
* \param int ramp_up: the time the motor will take to reach the required speed
* \param int ramp_down : the time the motor will stop
*/
void door_up_ramp( uint8_t sn3, int speed, int ramp_up, int ramp_down) ;


/** 
* \brief this function closes the doors at a certain speed where the accelerations are specified (used at the beginning to test some values)
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the motor will turn
* \param int ramp_up: the time the motor will take to reach the required speed
* \param int ramp_down : the time the motor will stop
*/
void door_down_ramp( uint8_t sn3, int speed, int ramp_up, int ramp_down) ;


/** 
* \brief this function completly opens the doors at a certain speed 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the motor will turn
*/
void door_up( uint8_t sn3, int speed) ;


/** 
* \brief this function completly close the doors at a certain speed 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the motor will turn
*/
void door_down( uint8_t sn3, int speed) ;

/** 
* \brief this function opens the doors, waits and closes the doors at a certain speed (completly useless but funny at the beginning)
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the motor will turn
*/
void door_up_down( uint8_t sn3, int speed );

/** 
* \brief this function completly opens the door at the standard speed 
* \param uint8_t sn3 : the sequence number of the door's motor 
*/
void door_up_standard( uint8_t sn3) ;


/** 
* \brief this function completly closes the door at the standard speed 
* \param uint8_t sn3 : the sequence number of the door's motor 
*/
void door_down_standard( uint8_t sn3);


/** 
* \brief this function opens the doors just enought to make the ball pass below the color sensor at a certain speed 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the motor will turn
*/
void door_mi_up( uint8_t sn3, int speed) ;


/** 
* \brief this function closes the doors after openning them a little at a certain speed 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the motor will turn
*/
void door_mi_down( uint8_t sn3, int speed) ;


/** 
* \brief this function opens the doors just enought to make the ball pass below the color sensor at the standard speed 
* \param uint8_t sn3 : the sequence number of the door's motor
*/
void door_mi_up_standard( uint8_t sn3) ;


/** 
* \brief this function closes the doors after openning them a little at the standard speed 
* \param uint8_t sn3 : the sequence number of the door's motor 
*/
void door_mi_down_standard( uint8_t sn3);


//TODO: Improve this function by using the sonar sensor to check if the bal is too close to open the door (I've just realize that it can be really useful :( )
/** 
* \brief this function makes the robot opens its doors, runs for a certain distance at a certain speed and then closes the door 
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param int speed : the speed at which the robot will move
* \param int : the distance that the robot will run to catch the ball 
*/
void catch_dist(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int speed, int distance);

/** 
* \brief this function makes the robot opens its doors, runs at the position of the ball at a certain speed and then closes the door 
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param int speed : the speed at which the robot will move
*/
void catch_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar,int speed);

/** 
* \brief this function makes the robot catches the ball when the ball is under the color sensor
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the robot will move
*/
void catch_ball_after_check(uint8_t *sn, uint8_t sn_sonar, uint8_t sn3,int speed);

/** 
* \brief this function makes the robot runs back and closes its doors when the ball is under the color sensor
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param int speed : the speed at which the robot will move
*/
void run_back_no_ball(uint8_t *sn, uint8_t sn_sonar, uint8_t sn3, int speed);

/** 
* \brief this function makes the robot scan its surrounding : it turns "angle" degrees at the speed "speed " and stops if there is something nearer than "distance"mm or if it finishes turning
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param int speed : the speed at which the robot will turn
* \param int angle : the angle the robot will turn if it doesn't see anything
* \param int distance : the maximum distance from an obstacle that the robot can see (for this scan) 
* \return the final value read by the sonar (the distance from the object found if the robot found one within "distance"mm)
*/
int scan_angle_distance(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int distance);

// This is basically the same function as above but the diffence is that this one returns the distance to the nearest object 
/**
* \brief this function makes the robot scan its surrounding : it turns "angle" degrees at the speed "speed " and stops if there is something nearer than "distance"mm or if it finishes turning
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param int speed : the speed at which the robot will turn
* \param int angle : the angle the robot will turn if it doesn't see anything
* \param int distance : the maximum distance from an obstacle that the robot can see (for this scan) 
* \return the distance to the nearest object 
*/
int scan_angle_distance2(uint8_t *sn, uint8_t sn_sonar, int speed, int angle, int distance);

/**
* \brief this function checks it the object in front of the robot is the ball 
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn_color : the sequence number of the color sensor
* \param int speed : the speed at which the robot will run
* \param int distance : the distance from the obstacle 
* \return 1 if the object is the ball, 0 if not
*/
int is_it_the_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int speed, int distance);

/**
* \brief this function release the ball by running a little forward (or backward), openning the doors, sending the BALL meassage and then running "distance"mm forward (or backward) 
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param int speed : the speed at which the robot will run
* \param int distance : the distance that the robot will run after openning the doors
* \param int front_or_back : 1 the robot will go forward, -1 the robot will go barkward
* \param int s : the number corresponding to the BT connexion  
* \param char dest : ID number of the ally 
*/
void release_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int speed, int distance, int front_or_back, int s, int dest);

/**
* \brief this function do at most 3 different scans : one to look for near objects, one for middle range objects and one for far ones (near:=distance/3,middle:=distance*2/3,far:=distance).
* If the robot find a object, it checks if it is the ball and don't do the following scans 
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn_color : the sequence number of the color sensor
* \param int speed_scan : the speed at which the robot will turn
* \param int speed_catch : the speed at which the robot will run to catch the ball
* \param int limit_distance : the biggest distance that the robot will look for an object 
* \return 0 if the robot doesn't find a object within the limit_distance, 1 if it finds the ball and 2 if the object is not the ball
*/
int scan (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color,int speed_scan, int speed_catch, int limit_distance);

/**
* \brief this function do at most 2 different scans : one to look for the nearest objects, one to position the robot to the right direction
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn_color : the sequence number of the color sensor
* \param int speed_scan : the speed at which the robot will turn
* \param int speed_catch : the speed at which the robot will run to catch the ball
* \param int limit_distance : the biggest distance that the robot will look for an object 
* \return 0 if the robot doesn't find a object within the limit_distance, 1 if it finds the ball and 2 if the object is not the ball
*/
int scan2 (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color,int speed_scan, int speed_catch, int limit_distance);

/**
* \brief this function check if the obstacle at distance_to_object is the ball and if it is, the robot catches it and if not the robot run back. This function uses is_it_the_ball, catch_if_ball and run_back_no_ball.
* \param uint8_t* sn : the list of the sequence numbers the motor used to move 
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn_color : the sequence number of the color sensor
* \param int speed_catch : the speed at which the robot will run to catch the ball
* \param int distance_to_object : the distance between the object and the robot
* \param int limit_distance : the biggest distance that the robot will go and check the object 
* \return 0 if the object is too far, 1 if it finds the ball and 2 if the object is not the ball
*/
int catch_if_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int speed_catch, int distance_to_object, int limit_distance);

/**
* \brief this function implements the reseach algorithm. Need to be called when the robot is near the ball. This is where we handle the case when the robot doesn't find the ball.
* \param uint8_t sn3 : the sequence number of the door's motor 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn_color : the sequence number of the color sensor
* \return 0 if it doesn't find the ball, 1 if it finds the ball
*/
int get_ball(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color);
