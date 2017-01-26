#include "basic_include.h"
#include <stdarg.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <pthread.h>

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

void test_bluetooth(uint8_t *sn, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, int *s, int *choice_parameters){
  extern uint16_t msgId;
  extern unsigned char rank,length,previous,next,side;
  unsigned char dest;
  if( init_bluetooth(s) == 0 ) {
    printf("[S] Init bluetooth is a success !! \n");
    char string[58];
    // Wait for START message 
    read_from_server (*s, string, 9);
    if (string[4] == MSG_START) {
      printf ("Received start message!\n");
      rank = (unsigned char) string[5];
      side = (unsigned char) string[6];
      dest = (unsigned char) string[7];
    }
    create_thread_print_coordinates();
    if (side==0 && rank==0 && choice_parameters[0]==1){
    create_thread_send_message(s);
      printf("I Big arena beg right \n");
      big_arena_beginner(sn,sn3,sn4,sn_sonar,1,*s,dest);
    }
    if (side==1 && rank==0 && choice_parameters[0]==1){
    create_thread_send_message(s);
      printf("I Big arena beg left \n");
      big_arena_beginner(sn,sn3,sn4,sn_sonar,-1,*s,dest);
    }
    if (side==0 && rank==1 && choice_parameters[0]==1){
      printf("I Big arena fin right \n");
      big_arena_finisher(sn,sn3,sn4,sn_sonar,sn_color,1,*s,dest);
    }
    if (side==1 && rank==1 && choice_parameters[0]==1){
    create_thread_send_message(s);
      printf("I Big arena beg left \n");
      big_arena_finisher(sn,sn3,sn4,sn_sonar,sn_color,-1,*s,dest);
    }
    if (side==0 && rank==0 && choice_parameters[0]==2){
      printf("I small arena beg left \n");
      set_position(1100,300);
      set_side_angle(0);
      while (1){
        small_arena_beginner(sn,sn3,sn_sonar,sn_color,*s,dest);
      }
    }
    if (side==0 && rank==1 && choice_parameters[0]==2){
      printf("I small arena fin \n");
      set_position(100,1700);
      set_side_angle(180);
      while (1){
        small_arena_finisher(sn,sn3,sn_sonar,sn_color,*s,dest);
      }
    }
    close (*s);
    sleep (5);
  } else {
    fprintf (stderr, "Failed to connect to server...\n");
    sleep (2);
    exit (EXIT_FAILURE);
  }
  close(*s);
}

void send_message(int s, char type_of_message, char dest, char pick_or_put){
  int tmp_pos_x, tmp_pos_y;
  char string[48];
  extern uint16_t msgId;
  extern pthread_mutex_t mutex_msgId;

  pthread_mutex_lock(&mutex_msgId);
  //msgId++;
  //string[0] = (msgId >> 8) & 0xFF;
  //string[1] = msgId & 0xFF;
  *((uint16_t *)string)=msgId++;
  pthread_mutex_unlock(&mutex_msgId);

  string[2] =  (uint8_t)TEAM_ID;
  string[3] =  (uint8_t)dest;
  string[4] = (uint8_t) type_of_message;

  if (type_of_message==MSG_NEXT) write(s, string, 5);
  if (type_of_message==MSG_POSITION){
    string[3] = 0xFF;
    string[4] = (uint8_t)MSG_POSITION; 
    tmp_pos_x=(int) get_x_position()/10;
    tmp_pos_y=(int) get_y_position()/10;
    //    string[5] = 0x05;
    //    string[6] = 0x00;
    //    string[7] = 0x05;
    //    string[8] = 0x00;
    string[6] = (tmp_pos_x >> 8) & 0xFF; 
    string[5] = tmp_pos_x & 0xFF;
    string[8] = (tmp_pos_y >> 8) & 0xFF;
    string[7] = tmp_pos_y & 0xFF;
    write(s, string, 9);
    //printf("[I,messageBT] I am sending : %d,%d,%d,%d,%d,%d,%d,%d,%d \n",string[0],string[1],string[2],string[3],string[4],string[5],string[6],string[7],string[8]);
  }
  if (type_of_message== MSG_BALL){
    string[5] = pick_or_put;
    tmp_pos_x=(int) get_x_position()/10;
    tmp_pos_y=(int) get_y_position()/10;
    string[7] = (tmp_pos_x >> 8) & 0xFF; 
    string[6] = tmp_pos_x & 0xFF;
    string[9] = (tmp_pos_y >> 8) & 0xFF;
    string[8] = tmp_pos_y & 0xFF;
    //printf("[I,messageBT] I am sending : %d,%d,%d,%d,%d,%d,%d,%d,%d,%d \n",string[0],string[1],string[2],string[3],string[4],string[5],string[6],string[7],string[8],string[9]);
    write(s, string, 10);
  }
}
