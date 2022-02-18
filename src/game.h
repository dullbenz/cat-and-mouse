#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

extern struct Player* game_winner;

void initialize_game();
void start_game();
void players_move_pieaces();
void end_game();

#endif