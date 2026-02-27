#ifndef XO
#define XO

#define DIMS 3

#define EMPTY_SQ -1

typedef enum
{
    X,
    O
} Side;


typedef enum
{
  TL, TM, TR,
  ML, MM, MR,
  BL, BM, BR
} move_type_t;



typedef struct
{
  Side side_to_play;
  int grid[DIMS][DIMS];
  bool finished;
} game_state_t;


int init_game_state(game_state_t* gs);

void print_game_state(const game_state_t* gs);

move_type_t input_to_move(char move_input[2]);

bool test_valid_move(int input_move, const game_state_t* gs);

void game_play_move(int input_move, game_state_t* gs);

void check_win_condition(const game_state_t* gs);

#endif
