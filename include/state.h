#ifndef   _STATE
#define   _STATE

#include <stdbool.h>

#include "utils.h"
#include "spatial_coords.h"

#define  BOARD_COLS 3
#define  BOARD_ROWS 3
#define  BOARD_SIZE (BOARD_COLS*BOARD_ROWS)

#define  EMPTY        '-'
#define  PLAYER_O     'O'
#define  PLAYER_X     'X'

typedef struct game_state {
    char   board[BOARD_SIZE];   // the board of the game
    
    /* 
     * the utility number for this game:
	 *   0.5 -> draw
	 *   0   -> player O win
	 *   1   -> player X win					      
     */
    double utility;  
	                          
    char player1;    // X player
    char player2;    // O player
    char empty;

	char next_player; // next player turn
} _state;

void    _state_init_game(_state*);
double  _state_get_utility(_state);
void    _state_move(_state*, spatial_coords);
void    _state_move_xy(_state*, int, int);
char    _state_get_player(_state);
bool    _state_is_terminal(_state*);
bool    _state_is_empty(_state*, spatial_coords);
bool    _state_board_is_full(_state*);
void    _state_evaluate_utility(_state*);
int     _state_get_empty_positions(_state, spatial_coords*);
_state  _state_get_copy(_state);

#endif