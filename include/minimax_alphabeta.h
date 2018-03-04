#ifndef  _MINIMAX_ALPHABETA
#define  _MINIMAX_ALPHABETA

#include "state.h"

spatial_coords  _minimax_alpha_beta_search(_state);
double          _minimax_min(_state, double, double, char);
double          _minimax_max(_state, double, double, char);

#endif