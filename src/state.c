/* #########################################################
 * Description: This file rappresent the state of the board and
 *            : the actions that can change or read it.
 * #########################################################
 */

#include <string.h>
#include "../include/state.h"


double _state_get_utility(_state state)
{
    return state.utility;
}

char _state_get_player(_state state)
{
    return state.next_player;
}

/* 
 * Function: _state_get_empty_positions
 * --------------------------------------------------------------------
 * This function returns the number of possible moves (the value of k),
 * and an array of moves filling the argument buffer (*out)
 *
 */
int _state_get_empty_positions(_state state, spatial_coords *out)
{
    int k = 0;

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            spatial_coords _tmp_coord;
            _tmp_coord.x = i;
            _tmp_coord.y = j;

            if (state.board[spatial_coords_2_index(_tmp_coord)] == EMPTY)
                out[k++] = _tmp_coord;
        }
    }

    return k;
}

_state _state_get_copy(_state state_obj)
{
    _state state_copy;

    state_copy.utility = state_obj.utility;
    state_copy.player2 = state_obj.player2;
    state_copy.player1 = state_obj.player1;
    
    state_copy.empty       = state_obj.empty;
    state_copy.next_player = state_obj.next_player;
    
    strncpy(state_copy.board, state_obj.board, 9);

    return state_copy;
}

void _state_move_xy(_state *state, int x, int y)
{
    spatial_coords coords;
    coords.x = x;
    coords.y = y;

    _state_move(state, coords);
}

/*
 * Function: _state_move
 * --------------------------------------------------------------------
 * called for move at the location specified by coords and after that 
 * check if the board is full or if the current move is a winner move;
 * the last instruction set the next player
 *
 */
void _state_move(_state *state, spatial_coords coords)
{
    if (state->utility != -1 || !_state_is_empty(state, coords)) 
        return;

    state->board[spatial_coords_2_index(coords)] = state->next_player;
    _state_evaluate_utility(state);
    state->next_player = (state->next_player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

/*
 * Function: _state_evaluate_utility
 * --------------------------------------------------------------------
 * called after each move. 
 * If the state of the game is terminal we have 2 possibilities:
 *   0 -> victory of O;
 *   1 -> victory of X (have faith);
 *
 * If the board is full, then the utility is 0.5
 *
 */
void _state_evaluate_utility(_state *state)
{
    if (_state_is_terminal(state))
        state->utility = state->next_player == PLAYER_X ? 1 : 0;
    
    else if (_state_board_is_full(state))
        state->utility = 0.5;
}

bool _state_board_is_full(_state *state)
{
    int i = -1;
    while ((++i) < 9 && state->board[i] != EMPTY);
    return i == 9;
}

bool _state_is_empty(_state *state, spatial_coords coords)
{
    return state->board[spatial_coords_2_index(coords)] == EMPTY;
}

/*
 * used to evaluate the game: if return true, 
 * the game is ended with victory of "next_player"
 *
 */
bool _state_is_terminal(_state *state)
{
    char player = state->next_player;

    if (player == state->board[0] && player == state->board[1] && player == state->board[2] || /* Horizontal */
        player == state->board[3] && player == state->board[4] && player == state->board[5] ||
        player == state->board[6] && player == state->board[7] && player == state->board[8] ||

        player == state->board[0] && player == state->board[3] && player == state->board[6] || /* Vertical */
        player == state->board[1] && player == state->board[4] && player == state->board[7] ||
        player == state->board[2] && player == state->board[5] && player == state->board[8] ||

        player == state->board[0] && player == state->board[4] && player == state->board[8] || /* Oblique */
        player == state->board[2] && player == state->board[4] && player == state->board[6]) return true;

    return false;
}

void _state_init_game(_state *state)
{
    for (int i = 0; i < 9; i++)
        state->board[i] = EMPTY;
    
    state->player1 = PLAYER_X;
    state->player2 = PLAYER_O;
    state->empty   = EMPTY;

    state->utility = -1;
    state->next_player = PLAYER_X;
}