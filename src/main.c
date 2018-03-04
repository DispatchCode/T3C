/* #########################################################
 * Description: This is just a simple implementation of the 
 *            : MiniMax algoritm with Alpha-Beta pruning.
 *            : TicTacToe was choosen only for its simplicity
 * ---------------------------------------------------------
 * Version    : 1.0
 * ---------------------------------------------------------
 * Author     : Marco 'DispatchCode' C.
 * ---------------------------------------------------------
 * License    : GNU/GPL v.3 (see LICENSE file for more details)
 * #########################################################
 */

#include <stdio.h>
#include <conio.h>

#include "../include/game.h"
#include "../include/minimax_alphabeta.h"


// Print current board state
void print_state(_state state, char player)
{
	printf("\n========== player %c move ==========\n\n", player);

	for (int i = 0; i < BOARD_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS; j++)
		{
			spatial_coords coords;
			coords.x = i;
			coords.y = j;
			printf("\t%c  ", state.board[spatial_coords_2_index(coords)]);
		}
		printf("\n\n");
	}
	printf("\n========== waiting.... ==============\n");
}

void print_message(double val)
{
    
    if(val == 0.5)
        printf("\nDraw!\n");
    else if(val == 0)
        printf("\nPlayer O Win!\n");
    else if(val == 1)
        printf("\nPlayer X Win!\n");
}

int main()
{
	_state initial_state = _game_start();

	printf("Player (you): X\nPlayer (IA): O\n\nType the corresponding number to move in:\n");
	printf("1 2 3\n4 5 6\n7 8 9\n");

	while (!_game_is_terminal(initial_state))
	{
		int index;
		printf("\nPosition: ");
		scanf("%d", &index);

		index--;

		if (index < 0 || index > 8)
		{
			printf("\n\tInvalid position!\n");
			continue;
		}
        
        
        // Human move...
		_state_move(&initial_state, index_to_xy(index));
		print_state(initial_state, PLAYER_X);

        // ...IA check the board, and find his best move
		spatial_coords coords = _minimax_alpha_beta_search(initial_state);
		_state_move(&initial_state, coords);

		print_state(initial_state, PLAYER_O);

		if (initial_state.utility != -1)
			print_message(initial_state.utility);
	}

    getch();
    
	return 0;

}