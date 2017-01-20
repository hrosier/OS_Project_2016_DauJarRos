//turn//
#define TURN_SPEED 430 //half of the max speed
#define RIGHT_ANGLE 1030
#define DEG_TO_RAD 3.14159/180.0
#define RAD_TO_DEG 180.0/3.14159

//Movement//
#define POSITION_TO_DISTANCE 495.0/1000.0 
#define DISTANCE_TO_POSITION 1000.0/495.0
#define DISTANCE_LIMIT 20
#define MAX_SPEED 860
#define MAX_SPEED_DOOR 860
#define MAX_SPEED_CATAPULT 860
#define MOVEMENT_RAMP_UP 2200
#define MOVEMENT_RAMP_DOWN 2200
#define MOVEMENT_DISTANCE_SONAR 200
//For the goto function
#define POSITION_PRECISION 20

//sonar//
#define SONAR_DISTANCE 500

//Bluetooth//
#define SERV_ADDR   "dc:53:60:ad:61:90"     /* Whatever the address of the server is */
#define TEAM_ID     6                       /* Your team ID */

#define MSG_ACK     0
#define MSG_NEXT    1
#define MSG_START   2
#define MSG_STOP    3
#define MSG_CUSTOM  4
#define MSG_KICK    5
#define MSG_POSITION 6
#define MSG_BALL 	7

//color//
#ifndef COLOR_COUNT
#define COLOR_COUNT 8
#endif
