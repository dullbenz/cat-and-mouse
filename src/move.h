#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include <stdbool.h>
#include "board_square.h"

bool consecutive_square_move(struct BoardSquare from, struct BoardSquare to);
bool jump_square_move(struct BoardSquare from, struct BoardSquare to);
bool move_will_eat_rat(struct BoardSquare from, struct BoardSquare to);
bool is_move_valid(struct BoardSquare from, struct BoardSquare to);
bool can_eat_rat(struct BoardSquare from);
struct BoardSquare* piece_to_eat_rat();
void validate_move(struct BoardSquare* from, struct BoardSquare* to);
void move_piece(struct BoardSquare* from, struct BoardSquare* to);

#endif