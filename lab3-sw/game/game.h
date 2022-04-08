enum duck_state { flap_up, flap_down, dead, inactive };

typedef struct {
unsigned int x,y;
} coord_t;
typedef struct {
	// none of these values are larger than 16 bits
	unsigned int vx, vy, value;
	coord_t coord;
	enum duck_state state;
} duck_t;

typedef struct {
  // We should only need 8 bits for each of these
  unsigned char bullets, score, round;
} game_config_t;

typedef struct {
  duck_t duck_1;
  duck_t duck_2;
  game_config_t game_conf;
} all_game_data_t;

// Checks to see if a given shot has hit any of the ducks.
int shoot(duck_t * duck_array, int duck_array_length, coord_t cross_hair);

// Caclulates hit square associated with x,y position of the duck. Returns 1 if cross_hair is in the hit square. Returns 0 if cross_hair is outside of the hit square.
int calculate_hit(duck_t * duck, coord_t cross_hair);
int set_up_config(game_config_t * game_config);

int move_duck(duck_t * duck);



