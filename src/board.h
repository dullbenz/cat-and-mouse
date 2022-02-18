#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include "board_square.h"

extern const int cat_number;
extern struct BoardSquare* board;
extern const int board_length;
extern const int rat_number;
extern const int refuge_square_number;
extern int eliminated_rats;
extern int eliminated_cats;

struct BoardSquare* initialize_board();
struct BoardSquare* initialize_board_from_data(FILE* file);
void empty_board();
void display_board();
struct BoardSquare* find_square(int row_index, int col_index);
struct BoardSquare* find_square_from_number(int number);
struct BoardSquare** find_all_cats();
void execute_move(struct BoardSquare* from, struct BoardSquare* to);
void blonder_piece_at(struct BoardSquare* from);
void elimate_rat_between(struct BoardSquare from, struct BoardSquare to);
void place_cats(int first, int second);
bool have_rats_filled_refuge();
void save_board_state(FILE* file);

#endif