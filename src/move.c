#include "move.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>


bool consecutive_square_move(struct BoardSquare from, struct BoardSquare to) {
	if(is_not_a_square(from) || is_not_a_square(to)) return false;
	if(abs(from.column - to.column) == 1) {
		if(abs(from.row - to.row) <= 1) {
			return true;
		}
	} else if(abs(from.column - to.column) == 0 && abs(from.row - to.row) == 1) {
		return true;
	}

	return false;
}

bool jump_square_move(struct BoardSquare from, struct BoardSquare to) {
	if(is_not_a_square(from) || is_not_a_square(to)) return false;
	if(to.is_refuge) return false;

	if(abs(from.column - to.column) == 2) {
		if(abs(from.row - to.row) == 0 || abs(from.row - to.row) == 2) {
			return true;
		}
	} else if(abs(from.column - to.column) == 0 && abs(from.row - to.row) == 2) {
		return true;
	}

	return false;
}

bool move_will_eat_rat(struct BoardSquare from, struct BoardSquare to) {
	if(is_not_a_square(from) || is_not_a_square(to)) return false;
	if(to.is_refuge) return false;

	
	if(jump_square_move(from, to)) {
		if(is_rat(*find_square((from.row + to.row) / 2, (from.column + to.column) /2)))
			return true;
	}
	return false;
}

bool is_move_valid(struct BoardSquare from, struct BoardSquare to) {
	if(is_rat(from)) {
		if(is_empty(to)) {
			if(to.row - from.row == 1) {
				if(abs(to.column - from.column) <= 1)
					return true;
			} else if(to.row - from.row == 0 && abs(to.column - from.column) == 1) {
				return true;
			}
		}
	} else if(is_cat(from)) {
		if(to.is_refuge) return false;
		if(is_empty(to)) {
			if(consecutive_square_move(from, to)) 
				return true;
			else if(move_will_eat_rat(from, to))
				return true;
		}
	}

	return false;
}

bool can_eat_rat(struct BoardSquare from) {
	if(boardsquare_is_equal(from, not_a_square)) return false;
	
	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			if(i == 0 && j == 0)
				continue;
			if(is_rat(*find_square(from.row + i, from.column + j))) {
				if(is_move_valid(from, *find_square(from.row + 2*i, from.column + 2*j))) {
					return true;
				}
			}
		}
	}

	return false;
}

struct BoardSquare* piece_to_eat_rat() {
	struct BoardSquare** cats = find_all_cats();
	for(int i = 0; i < cat_number; i++) {
		if(can_eat_rat(*cats[i])) {
			return cats[i];
		}
	}

	return &not_a_square;
}

void validate_move(struct BoardSquare* from, struct BoardSquare* to) {
	struct BoardSquare* piece_;
	if(is_cat(*from)) {
		if(move_will_eat_rat(*from, *to)) {
			elimate_rat_between(*from, *to);
			execute_move(from, to);
		} else if(!boardsquare_is_equal(*(piece_ = piece_to_eat_rat()), not_a_square)) {
			if(boardsquare_is_equal(*piece_, *from)) {
				blonder_piece_at(piece_);
			} else {
				execute_move(from, to);
				blonder_piece_at(piece_);
			}
		} else {
			execute_move(from, to);
		}
	} else {
		execute_move(from, to);
	}
}

void move_piece(struct BoardSquare* from, struct BoardSquare* to) {
	int f, t;
	if(is_move_valid(*from, *to)) {
		validate_move(from, to);
		printf("Your move has been applied\n");
		display_board();
	} else {
		printf("The move is not valid, try again!!\n");
		printf("Player : ");
		scanf("%d %d", &f, &t);
		move_piece(find_square_from_number(f), find_square_from_number(t));
	}
}