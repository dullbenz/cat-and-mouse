#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdbool.h>
#include "board_square.h"

extern const int username_max_length;

struct Player {
    char username[11];
    enum SquareState plays_with;
};

struct Player create_player();

#endif