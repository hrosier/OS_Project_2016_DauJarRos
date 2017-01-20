#include "basic_include.h"
#include <stdarg.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

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


