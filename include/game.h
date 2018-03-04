#ifndef  _GAME
#define  _GAME

#include <float.h>
#include "state.h"

_state  _game_start();
int     _game_get_actions(_state, spatial_coords*);
_state  _game_get_result(_state, spatial_coords);
double  _game_get_utility(_state, char);
char    _game_get_player(_state);
bool    _game_is_terminal(_state);

#endif