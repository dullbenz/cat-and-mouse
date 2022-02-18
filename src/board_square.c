#include "board_square.h"

struct BoardSquare not_a_square;

bool boardsquare_is_equal(const struct BoardSquare first, const struct BoardSquare second) {
	if(first.column == second.column)
		if(first.content == second.content)
			if(first.is_refuge == second.is_refuge)
				if(first.number == second.number)
					if(first.row == second.row) 
						if(first.state == second.state)
							return true;

	return false;
}

bool is_not_a_square(struct BoardSquare square) {
    return boardsquare_is_equal(square, not_a_square);
}

bool is_cat(struct BoardSquare from) {
	if(is_not_a_square(from)) return false;

	if(from.state == cat) return true;

	return false;
}

bool is_rat(struct BoardSquare from) {
	if(is_not_a_square(from)) return false;

	if(from.state == rat) return true;

	return false;
}

bool is_empty(struct BoardSquare from) {
	if(is_not_a_square(from)) return false;

	if(from.state == empty) return true;

	return false;
}

enum SquareState get_opposite_state(enum SquareState first) {
	if(first == cat) {
        return rat;
    } else if(first == rat) {
        return cat;
    }

	// get opposite returns empty if the square is empty
	return empty;
}

bool state_is_opposite(enum SquareState first, enum SquareState second) {
	if(first == cat && second == rat) return true;
	if(first == rat && second == cat) return true;

	return false;
}

