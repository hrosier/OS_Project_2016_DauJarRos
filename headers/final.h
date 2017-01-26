/** 
\brief : function used to make the robot run the small arena as the beginner
* \param uint8_t* sn : the list of the sequence number of the tacho motor used to move 
* \param uint8_t sn3 : the sequence number of the tacho motor used to open/close the doors 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor 
* \param uint8_t sn_color : the sequence number of the color sensor
* \param int* s : the adress where is stored the number corresponding to the BT connexion  
* \param int dest : the ID of the ally 
*/
void small_arena_beginner(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar,uint8_t sn_color, int s, int dest);

/** \brief : function used to make the robot put the ball in the middle of the small arena as the beginner
* \param uint8_t* sn : the list of the sequence number of the tacho motor used to move 
* \param uint8_t sn3 : the sequence number of the tacho motor used to open/close the doors 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor 
* \param int* s : the adress where is stored the number corresponding to the BT connexion (used to send messages)
* \param int dest : the ID of the ally (used to send messages)
*/
void put_small_beg(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int s, int dest);

/**
* \brief : function used to make the robot get the ball in the middle of the small arena as the beginner
* \param uint8_t* sn : the list of the sequence number of the tacho motor used to move 
* \param uint8_t sn3 : the sequence number of the tacho motor used to open/close the doors 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn_color : the sequence number of the color sensor
* \param int* s : the adress where is stored the number corresponding to the BT connexion (used to send messages)
* \param int dest : the ID of the ally (used to send messages)
*/
void get_small_beg(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest);

/**
* \brief : function used to make the robot run the small arena as the finisher
* \param uint8_t* sn : the list of the sequence number of the tacho motor used to move 
* \param uint8_t sn3 : the sequence number of the tacho motor used to open/close the doors 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor 
* \param uint8_t sn_color : the sequence number of the color sensor
* \param int* s : the adress where is stored the number corresponding to the BT connexion  
* \param int dest : the ID of the ally 
*/
void small_arena_finisher(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest);

/**
* \brief : function used to make the robot get the ball in the middle of the small arena as the finisher
* \param uint8_t* sn : the list of the sequence number of the tacho motor used to move 
* \param uint8_t sn3 : the sequence number of the tacho motor used to open/close the doors 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor
* \param uint8_t sn_color : the sequence number of the color sensor
* \param int* s : the adress where is stored the number corresponding to the BT connexion (used to send messages)
* \param int dest : the ID of the ally (used to send messages)
*/
void get_small_fin(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int dest);

/** \brief : function used to make the robot put the ball in the middle of the small arena as the beginner
* \param uint8_t* sn : the list of the sequence number of the tacho motor used to move 
* \param uint8_t sn3 : the sequence number of the tacho motor used to open/close the doors 
* \param uint8_t sn_sonar : the sequence number of the sonar sensor 
* \param int* s : the adress where is stored the number corresponding to the BT connexion (used to send messages)
* \param int dest : the ID of the ally (used to send messages)
*/
void put_small_fin(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, int s, int dest);

/**
* \brief : function used to make the robot run the big arena as the beginner
* \param uint8_t* sn : the list of the sequence number of the tacho motor used to move 
* \param uint8_t sn3 : the sequence number of the tacho motor used to open/close the doors 
* \param uint8_t sn4 : the sequence number of the tacho motor used by the catapult  
* \param uint8_t sn_sonar : the sequence number of the sonar sensor 
* \param uint8_t sn_colot : the sequence number of the color sensor
* \param int* s : the adress where is stored the number corresponding to the BT connexion  
* \param int dest : the ID of the ally 
*/
void big_arena_beginner(uint8_t *sn, uint8_t sn3,uint8_t sn4, uint8_t sn_sonar, int side, int s, int dest);

/**
* \brief : function used to make the robot run the big arena as the finisher
* \param uint8_t* sn : the list of the sequence number of the tacho motor used to move 
* \param uint8_t sn3 : the sequence number of the tacho motor used to open/close the doors 
* \param uint8_t sn4 : the sequence number of the tacho motor used by the catapult  
* \param uint8_t sn_sonar : the sequence number of the sonar sensor 
* \param uint8_t sn_colot : the sequence number of the color sensor
* \param int* s : the adress where is stored the number corresponding to the BT connexion  
* \param int dest : the ID of the ally 
*/
void big_arena_finisher(uint8_t *sn, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, int side, int s, int dest);
