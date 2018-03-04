/* #########################################################
 * Description: This is the "core". 
 *            : _minimax_alpha_beta_search returns an (x,y)
 *            : position that rapresent the best move for the
 *            : considered player.
 *            : The algorithm expand the tree of the possible
 *            : moves and cut its search with the help of 
 *            : alpha-beta pruning
 * #########################################################
 */
 

#include "../include/game.h"
#include "../include/minimax_alphabeta.h"

/*
 * Function: _minimax_alpha_beta_search
 * ----------------------------------------------------------
 * 
 *
 */
spatial_coords _minimax_alpha_beta_search(_state state)
{
	spatial_coords coords;

	double res  = DBL_MIN;
	char player = _game_get_player(state);

	spatial_coords actions[BOARD_SIZE];
	int len = _game_get_actions(state, actions);

	for (int i = 0; i < len; i++)
	{
		double value = _minimax_min(_game_get_result(state, actions[i]), DBL_MIN, DBL_MAX, player);

		if (value > res)
		{
			coords.x = actions[i].x;
			coords.y = actions[i].y;
			res      = value;
		}
	}

	return coords;
}

double _minimax_min(_state state, double alpha, double beta, char player)
{
	if (_game_is_terminal(state))
		return _game_get_utility(state, player);

	double value = DBL_MAX;

	spatial_coords actions[BOARD_SIZE];
	int len = _game_get_actions(state, actions);

	for (int i = 0; i < len; i++)
	{
		value = min_value(value, _minimax_max(_game_get_result(state, actions[i]), alpha, beta, player));

		if (value <= alpha)
			return value;

		beta = min_value(beta, value);
	}

	return value;
}

double _minimax_max(_state state, double alpha, double beta, char player)
{
	if (_game_is_terminal(state))
		return _game_get_utility(state, player);

	double value = DBL_MIN;
	spatial_coords actions[BOARD_SIZE];
	int len = _game_get_actions(state, actions);

	for (int i = 0; i < len; i++)
	{
		value = max_value(value, _minimax_min(_game_get_result(state, actions[i]), alpha, beta, player));

		if (value >= beta)
			return value;

		alpha = max_value(alpha, value);
	}

	return value;
}