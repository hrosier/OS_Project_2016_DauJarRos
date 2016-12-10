void init_all(uint8_t sn1, uint8_t sn2, uint8_t sn3, uint8_t sn4, uint8_t sn_sonar, uint8_t sn_color, uint8_t *sn, int *max_speed, int *max_speed_door, int *max_speed_cata);
void init_wheels(uint8_t sn1, uint8_t sn2, uint8_t *sn, int *max_speed);
void init_door_or_catapult(uint8_t sn3, int *max_speed,int port);
void init_catapult(uint8_t sn4, int *max_speed_cata);
void init_door(uint8_t sn3, int *max_speed_door);
void init_sonar(uint8_t sn_sonar );
void init_color(uint8_t sn_color);
