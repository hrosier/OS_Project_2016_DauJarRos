void debug (const char *fmt, ...) ;
/** 
* \brief this function to read a message from the server
* \param int sock : number corresponding to the socket
* \param[out] char * buffer : buffer where the message will be stored
* \param size_t maxSize : number of bytes that the buffer can contain
* \return int bytes_read : the number of bytes of the messages 
*/
int read_from_server (int sock, char *buffer, size_t maxSize) ;
/** 
* \brief the function init the BT connexion with the server
* \param int* s : the adress where to store the number corresponding to the BT connexion 
* \return int status : the status of the connexion (success or not) 
*/
int init_bluetooth(int *s) ;

/** 
* \brief This function is used to send messages to the server or the ally
* \param int s : number corresponding to the socket
* \param char type_of_message : number corresponding tp the type of message to send
* \param char dest : number of the ally 
* \param char pick_or_put : number that specify if the robot pick or put the ball
*/
void send_message(int s, char type_of_message, char dest, char pick_or_put);

