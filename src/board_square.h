#ifndef BOARD_SQUARE_H_INCLUDED
#define BOARD_SQUARE_H_INCLUDED

#include <stdbool.h>

enum SquareState{empty, cat, rat};

struct BoardSquare {
   bool is_refuge;
   char content; // c, r or empty
   enum SquareState state;
   int number;
   int row; // starts from 1
   int column; // starts from 1
};

extern struct BoardSquare not_a_square;

bool boardsquare_is_equal(const struct BoardSquare first, const struct BoardSquare second);
bool is_not_a_square(struct BoardSquare);
bool is_cat(struct BoardSquare from);
bool is_rat(struct BoardSquare from);
bool is_empty(struct BoardSquare from);
bool state_is_opposite(enum SquareState first, enum SquareState second);
enum SquareState get_opposite_state(enum SquareState first);
#endif