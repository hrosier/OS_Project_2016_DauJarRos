/* this file contains the functions used to deal with the bluetooth connexion */

#include "basic_include.h"
#include <stdarg.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

unsigned char rank = 0;
unsigned char length = 0;
unsigned char previous = 0xFF;
unsigned char next = 0xFF;
unsigned char side=0;
uint16_t msgId = 0;
pthread_mutex_t mutex_msgId = PTHREAD_MUTEX_INITIALIZER;

void debug (const char *fmt, ...) {
  va_list argp;
  va_start (argp, fmt);
  vprintf (fmt, argp);
  va_end (argp);
}

int read_from_server (int sock, char *buffer, size_t maxSize) {
  int bytes_read = read (sock, buffer, maxSize);
  if (bytes_read <= 0) {
    fprintf (stderr, "Server unexpectedly closed connection...\n");
    close (sock);
    exit (EXIT_FAILURE);
  }
  printf ("[DEBUG] received %d bytes\n", bytes_read);
  return bytes_read;
}

int init_bluetooth(int *s) {
  struct sockaddr_rc addr = { 0 };
  int status;
  /* allocate a socket */
  *s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
  /* set the connection parameters (who to connect to) */
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba (SERV_ADDR, &addr.rc_bdaddr);
  /* connect to server */
  status = connect(*s, (struct sockaddr *)&addr, sizeof(addr));
  return status;
}

void send_message(int s, char type_of_message, char dest, char pick_or_put){
  int tmp_pos_x, tmp_pos_y;
  char string[48];
  extern uint16_t msgId;
  extern pthread_mutex_t mutex_msgId;

  // We use a mutex to protect the value of msgId that can be access by several threads
  pthread_mutex_lock(&mutex_msgId);
  *((uint16_t *)string)=msgId++;
  pthread_mutex_unlock(&mutex_msgId);

  // Read the BT protocol to fully understand this part
  // sender
  string[2] = (uint8_t) TEAM_ID;
  // recipient
  string[3] = (uint8_t) dest;
  // Type of message (NEXT,START,BALL,etc)
  string[4] = (uint8_t) type_of_message;

  if (type_of_message==MSG_NEXT) write(s, string, 5);
  if (type_of_message==MSG_POSITION){
    // the recipient is the server
    string[3] = 0xFF;
    // we store the position on the bytes 5-8 of the message
    tmp_pos_x=(int) get_x_position()/10;
    tmp_pos_y=(int) get_y_position()/10;
    string[5] = tmp_pos_x & 0xFF;
    string[6] = (tmp_pos_x >> 8) & 0xFF; 
    string[7] = tmp_pos_y & 0xFF;
    string[8] = (tmp_pos_y >> 8) & 0xFF;
    //We write the string on the socket
    write(s, string, 9);
  }
  if (type_of_message==MSG_BALL){
    // We specify if we pick or put the ball 
    string[5] = pick_or_put;
    // we store the position on the bytes 6-9 of the message
    tmp_pos_x=(int) get_x_position()/10;
    tmp_pos_y=(int) get_y_position()/10;
    string[6] = tmp_pos_x & 0xFF;
    string[7] = (tmp_pos_x >> 8) & 0xFF; 
    string[8] = tmp_pos_y & 0xFF;
    string[9] = (tmp_pos_y >> 8) & 0xFF;
    //We write the string on the socket
    write(s, string, 10);
  }
}
