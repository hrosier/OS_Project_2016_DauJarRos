#include "basic_include.h"
#include <stdarg.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <pthread.h>

pthread_mutex_t mutex_msgId = PTHREAD_MUTEX_INITIALIZER;

void debug (const char *fmt, ...) {
  va_list argp;
  va_start (argp, fmt);
  vprintf (fmt, argp);
  va_end (argp);
}

unsigned char rank = 0;
unsigned char length = 0;
unsigned char previous = 0xFF;
unsigned char next = 0xFF;
unsigned char side=0;
uint16_t msgId = 0;

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

void test_bluetooth(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *s, int *choice_parameters){
  extern uint16_t msgId;
  extern unsigned char rank,length,previous,next,side;
  if( init_bluetooth(s) == 0 ) {
    printf("[S] Init bluetooth is a success !! \n");
    char string[58];
    // Wait for START message 
    read_from_server (*s, string, 9);
    if (string[4] == MSG_START) {
      printf ("Received start message!\n");
      rank = (unsigned char) string[5];
      side = (unsigned char) string[6];
      next = (unsigned char) string[7];
    }
    if (side==0){
      printf("I am on the right side\n");
    }
    else {
      printf("I am on the left side\n");
    }
    if (rank == 0)
      printf("I am the beginner from side : %d\n",side);
    //beginner (sn,sn3,sn_sonar,sn_color,s,side);
    else
      //finisher (sn,sn3,sn_sonar,sn_color,s,side);
      printf("I am the finisher from side : %d\n",side);
    close (*s);
    sleep (5);
  } else {
    fprintf (stderr, "Failed to connect to server...\n");
    sleep (2);
    exit (EXIT_FAILURE);
  }
  close(*s);
}


void beginner (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int side) {
  char string[58];
  extern uint16_t msgId;
  extern unsigned char rank,length,previous,next;
  printf ("I'm the beginner...\n");
  /* Send 3 POSITION messages, a BALL message, 1 position message, then a NEXT message */
  int i;
  for (i=0; i<3; i++){
    *((uint16_t *) string) = msgId++;
    string[2] = TEAM_ID;
    string[3] = 0xFF;
    string[4] = MSG_POSITION;
    string[5] = get_x_position();          /* x */
    string[6] = 0x00;
    string[7] = get_y_position();   /* y */
    string[8]= 0x00;
    write(s, string, 9);
    if (side==0) go_to_position2(sn,sn_sonar,get_x_position()+200,get_y_position()+200,MAX_SPEED/3,TURN_SPEED,0);
    if (side==1) go_to_position2(sn,sn_sonar,get_x_position()-200,get_y_position()-200,MAX_SPEED/3,TURN_SPEED,0);
  }
  //BALL drop message
  *((uint16_t *) string) = msgId++;
  string[2] = TEAM_ID;
  string[3] = next;
  string[4] = MSG_BALL;
  string[5] = 0x0;
  string[6] = get_x_position();          /* x */
  string[7] = 0x00;
  string[8] = get_y_position();
  //string[8] = 0x4;    /* y */
  string[9]= 0x00;
  write(s, string, 10);
  //last position message
  *((uint16_t *) string) = msgId++;
  string[2] = TEAM_ID;
  string[3] = 0xFF;
  string[4] = MSG_POSITION;
  string[5] = get_x_position();          /* x */
  string[6] = 0x00;
  string[7] = get_y_position();   /* y */
  string[8]= 0x00;
  write(s, string, 9);
  //Next message
  *((uint16_t *) string) = msgId++;
  string[2] = TEAM_ID;
  string[3] = next;
  string[4] = MSG_NEXT;
  write(s, string, 5);
  while(1){
    //Wait for other robot to finish
  }
}

void finisher (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int side) {
  char string[58];
  extern uint16_t msgId;
  extern unsigned char rank,length,previous,next;
  char type;
  printf ("I'm the finisher...\n");
  /* Get message */
  while (1){
    read_from_server (s, string, 58);
    type = string[4];
    switch (type) {
      case MSG_STOP:
        return;
      case MSG_NEXT:
        //send a position
        *((uint16_t *) string) = msgId++;
        string[2] = TEAM_ID;
        string[3] = 0xFF;
        string[4] = MSG_POSITION;
        string[5] = get_x_position();          /* x */
        string[6]= 0x00;
        string[7] = get_y_position();     /* y */
        string[8] = 0x00;
        write(s, string, 9);
        if (side==0) go_to_position2(sn,sn_sonar,200,200,MAX_SPEED/3,TURN_SPEED,0);
        if (side==1) go_to_position2(sn,sn_sonar,-200,200,MAX_SPEED/3,TURN_SPEED,0);
        if (scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/3,MAX_SPEED/6,SONAR_DISTANCE)== 2){
          scan2(sn,sn3,sn_sonar,sn_color,TURN_SPEED/4,MAX_SPEED/6,SONAR_DISTANCE);
        }
        //pick up a ball
        *((uint16_t *) string) = msgId++;
        string[2] = TEAM_ID;
        string[3] = next;
        string[4] = MSG_BALL;
        string[5] = 0x1;
        string[6] = get_x_position();          /* x */
        string[7] = 0x00;
        string[8] = get_y_position();    /* y */
        string[9]= 0x00;
        write(s, string, 10);       
        if (side==0) go_to_position2(sn,sn_sonar,400,400,MAX_SPEED/3,TURN_SPEED,0);
        if (side==1) go_to_position2(sn,sn_sonar,400,400,MAX_SPEED/3,TURN_SPEED,0);
        //send a position
        string[2] = TEAM_ID;
        string[3] = 0xFF;
        string[4] = MSG_POSITION;
        string[5] = get_x_position();          /* x */
        string[6]= 0x00;
        string[7] = get_y_position();     /* y */
        string[8] = 0x00;
        write(s, string, 9);
        //Game over
        return;
      case MSG_BALL:
        //I know where the ball is
        printf("Ball dropped at %02X%02X,%02X%02X \n",string[7], string[6], string[9], string[8]);
        break;        
      default:
        printf ("Ignoring message %d\n", type);
    }
  }
}

void send_message(int s, int type_of_message, int dest, int pick_or_put){
  char string[48];
  extern uint16_t msgId;
  extern pthread_mutex_t mutex_msgId;
  pthread_mutex_lock(&mutex_msgId);
  *((uint16_t *) string) = msgId++;
  pthread_mutex_unlock(&mutex_msgId);

  string[2] = TEAM_ID;
  string[3] = dest;
  string[4] = type_of_message;

  switch (type_of_message){
    case MSG_NEXT:
      break;
    case MSG_CUSTOM:
      break;
    case MSG_POSITION:
      string[3] = 0xFF;
      string[5] = get_x_position()/10;   /* x */
      string[6] = 0x00;
      string[7] = get_y_position()/10;   /* y */
      string[8] = 0x00;
      break;
    case MSG_BALL:
      string[5] = pick_or_put;
      string[6] = get_x_position()/10;   /* x */
      string[7] = 0x00;
      string[8] = get_y_position()/10;   /* y */
      string[9] = 0x00;
      break;
    default :
      printf("[X] error I can't this type of message\n");
      return;
      write(s, string, 9);
  }
}
