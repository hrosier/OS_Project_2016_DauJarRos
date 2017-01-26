void debug (const char *fmt, ...) ;
int read_from_server (int sock, char *buffer, size_t maxSize) ;
int init_bluetooth(int *s) ;
void test_bluetooth(uint8_t *sn, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, int *s, int *choice_parameters);
void send_message(int s, char type_of_message, char dest, char pick_or_put);
