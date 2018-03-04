/* #########################################################
 * Description: This file use a "state". For example, giving
 *            : a state and a buffer of spatial_coords, returns
 *            : all the possible moves. Most of the game functions
 *            : are used by MiniMax algorithm.
 * #########################################################
 */

#include "../include/game.h"

_state _game_start()
{
	_state state;
	_state_init_game(&state);
	return state;
}

int _game_get_actions(_state state, spatial_coords *out_buffer)
{
	return _state_get_empty_positions(state, out_buffer);
}

_state _game_get_result(_state state, spatial_coords coords)
{
	_state state_cpy = _state_get_copy(state);
	_state_move(&state_cpy, coords);
	return state_cpy;
}

/*
 * Functions: _game_get_utility
 * ----------------------------------------------------------------
 * called when the game reached a terminal state (=victory).
 *
 */
double _game_get_utility(_state state, char player)
{
	double utility = _state_get_utility(state);

	if (utility != -1 && player == PLAYER_O)
		utility = 1 - utility;

	return utility;
}

char _game_get_player(_state state)
{
	return _state_get_player(state);
}

bool _game_is_terminal(_state state)
{
	return _state_get_utility(state) != -1;
}