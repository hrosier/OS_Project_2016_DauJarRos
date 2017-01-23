void debug (const char *fmt, ...) ;
int read_from_server (int sock, char *buffer, size_t maxSize) ;
int init_bluetooth(int *s) ;
void test_bluetooth(uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int *s, int *choice_parameters);
void beginner (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int side) ;
void finisher (uint8_t *sn, uint8_t sn3, uint8_t sn_sonar, uint8_t sn_color, int s, int side) ;
void send_message(int s, int type_of_message, int dest, int pick_or_put);
