#include <stdio.h>
#include <stdbool.h>

#include "game.h"

// struct linkedSquares {
// 	struct BoardSquare square;
// 	struct linkedSquares* next;
// };

int main() {
	for(;;) {
		game_winner = NULL;
		initialize_game();
		start_game();
		players_move_pieaces();
		end_game();
	}
	return 0;
}

