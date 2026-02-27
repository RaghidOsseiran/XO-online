#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xo.h"


int init_game_state(game_state_t* gs)
{
    gs->side_to_play = X;
    gs->finished = false;
    for(int i = 0; i < DIMS; i++)
    {
        for(int j = 0; j < DIMS; j++)
        {
            gs->grid[i][j] = EMPTY_SQ;
        }
    }
}

void print_game_state(const game_state_t* gs)
{
    for(int i = 0; i < DIMS; i++)
    {
        for(int j = 0; j < DIMS; j++)
        {
            char cell = '.';
            switch (gs->grid[i][j])
            {
            case EMPTY_SQ:
                cell = '_';
                break;
            case X:
                cell = 'X';
                break;
            case O:
                cell = 'O';
                break;
            default:
                break;
            }
            printf(" %c", cell);
        }
        printf("\n");
    }
}

move_type_t input_to_move(char move_input[2])
{
  int res = -1;
  switch (move_input[0])
  {
    case 'T':
      switch(move_input[1])
      {
        case 'L':
          res = TL;
          break;
        case 'M':
          res = TM;
          break;
        case 'R':
          res = TR;
          break;
        default:
          break;
      }
      break;
    case 'M': 
      switch(move_input[1])
      {
        case 'L':
          res = ML;
          break;
        case 'M':
          res = MM;
          break;
        case 'R':
          res = MR;
          break;
        default:
          break;
      }
      break;
    case 'B': 
      switch(move_input[1])
      {
        case 'L':
          res = BL;
          break;
        case 'M':
          res = BM;
          break;
        case 'R':
          res = BR;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  return res;
}

bool test_valid_move(int input_move, const game_state_t* gs)
{
  if (input_move == -1) return false;
  bool res = true;
  switch (input_move)
  {
    case TL:
      res = (gs->grid[0][0] == EMPTY_SQ) ? res : false;
      break;
    case TM:
      res = (gs->grid[0][1] == EMPTY_SQ) ? res : false;
      break;
    case TR:
      res = (gs->grid[0][2] == EMPTY_SQ) ? res : false;
      break;
    case ML:
      res = (gs->grid[1][0] == EMPTY_SQ) ? res : false;
      break;
    case MM:
      res = (gs->grid[1][1] == EMPTY_SQ) ? res : false;
      break;
    case MR:
      res = (gs->grid[1][2] == EMPTY_SQ) ? res : false;
      break;
    case BL:
      res = (gs->grid[2][0] == EMPTY_SQ) ? res : false;
      break;
    case BM:
      res = (gs->grid[2][1] == EMPTY_SQ) ? res : false;
      break;
    case BR:
      res = (gs->grid[2][2] == EMPTY_SQ) ? res : false;
      break;
    default:
      break;
  }
  return res;
}

void game_play_move(int input_move, game_state_t* game)
{
  switch(input_move)
  {
    case TL:
      game->grid[0][0] = game->side_to_play;
      break;
    case TM:
      game->grid[0][1] = game->side_to_play;
      break;
    case TR:
      game->grid[0][2] = game->side_to_play;
      break;
    case ML:
      game->grid[1][0] = game->side_to_play;
      break;
    case MM:
      game->grid[1][1] = game->side_to_play;
      break;
    case MR:
      game->grid[1][2] = game->side_to_play;
      break;
    case BL:
      game->grid[2][0] = game->side_to_play;
      break;
    case BM:
      game->grid[2][1] = game->side_to_play;
      break;
    case BR:
      game->grid[2][2] = game->side_to_play;
      break;
    default:
      break;
  }
  game->side_to_play = (game->side_to_play == X) ? O : X;
}

void check_win_condition(game_state_t* gs, Side last_played_side)
{
  bool is_won = false;
  // check for horizontal alignements
  for(int i = 0; i < DIMS; i++)
  {
    is_won = (gs->grid[i][0] == last_played_side && gs->grid[i][1] == last_played_side && gs->grid[i][2] == last_played_side) ? true : false;
    if (is_won) {gs->finished = true; return;}
  } 
  

  // check for vertical alignements
  for(int i = 0; i < DIMS; i++)
  {
    is_won = (gs->grid[0][i] == last_played_side && gs->grid[1][i] == last_played_side && gs->grid[2][i] == last_played_side) ? true : false;
    if (is_won) {gs->finished = true; return;}
  }


  // check for diagonal alignements
  is_won = (gs->grid[0][0] == last_played_side && gs->grid[1][1] == last_played_side && gs->grid[2][2] == last_played_side) ? true : false;
  if (is_won) {gs->finished = true; return;}
  is_won = (gs->grid[0][2] == last_played_side && gs->grid[1][1] == last_played_side && gs->grid[2][0] == last_played_side) ? true : false; 
  if (is_won) {gs->finished = true; return;}
}

int main()
{   
    game_state_t game;
    init_game_state(&game);
    
    char move_input[2];
    while(!game.finished)
    {
      print_game_state(&game);
      printf("--------------------\nSide to move: %c\nWaiting for user input...\n--------------------\n", (game.side_to_play == X) ? 'X' : 'O');
      int input_move = 0;
      scanf("%s", move_input);
      input_move = input_to_move(move_input);
      while(!test_valid_move(input_move, &game))
      {
        fprintf(stderr, "Please try again, invalid move.\n>: ");
        scanf("%s", move_input);
        input_move = input_to_move(move_input);
      } 
      Side prev_player = game.side_to_play;
      game_play_move(input_move, &game);
      check_win_condition(&game, prev_player);
    }
    print_game_state(&game);
    printf("Player : %c has won!\n", (game.side_to_play == X) ? 'O' : 'X');
    return 0;
}
