#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int board_length = 41;
const int rat_number = 21;
const int refuge_square_number = 9;
struct BoardSquare* board;
struct BoardSquare** all_cats;
const int cat_number = 2;
int eliminated_rats;
int eliminated_cats;

struct BoardSquare* initialize_board() {
	board = (struct BoardSquare*) malloc(board_length * sizeof(struct BoardSquare));
	all_cats = (struct BoardSquare**) malloc (sizeof (struct BoardSquare*) * cat_number);
	if(board == NULL || all_cats == NULL) {
		printf("Error allocating memory");
		exit(1);
	}

	for(int i = 0; i < board_length; i++) {
		if(i < rat_number) {
			board[i].content = 's';
			board[i].state = rat;
		} else {
			board[i].content = ' ';
			board[i].state = empty;
		}

		if(i <= 29) {
			board[i].is_refuge = false;
			board[i].number = i + 1;
		} else if(i >= 30 && i <=32) {
			board[i].is_refuge = true;
			board[i].number = i + 3;
		} else if( i >=33 && i <= 34) {
			board[i].is_refuge = false;
			board[i].number = i - 2;
		} else {
			board[i].is_refuge = true;
			board[i].number = i + 1;
		}

		if(i <= 34) {
			board[i].row = i / 7 + 1;
			board[i].column = i % 7 + 1;
		} else {
			board[i].row = (i - 32) / 3 + 5;
			board[i].column = (i - 32) % 3 + 3;
		}

		// if(board[i].number <= 30) {
		// 	board[i].row = i / 7 + 1;
		// 	board[i].column = i % 7 + 1;
		// }
		// else if(board[i].number == 31 || board[i].number == 32) {
		// 	board[i].row = (i + 3) / 7 + 1;
		// 	board[i].column = (i + 3) % 7 + 1;
		// } else {
		// 	board[i].row = (i - 32) / 3 + 5;
		// 	board[i].column = (i - 32) % 3 + 3;
		// }
	}

	eliminated_cats = 0;
	eliminated_rats = 0;
	return board;
}

void save_board_state(FILE* file) {
    putc('{', file);
    for(int i = 0; i < board_length; i++) {
        if(is_empty(board[i])) {
			putc('e', file);
		} else if(is_cat(board[i])) {
			putc('c', file);
		} else if(is_rat(board[i])) {
			putc('r', file);
		}
    }
	putc('}', file);
	putc('[', file);
	fprintf(file, "%d %d ]", eliminated_cats, eliminated_rats);
}

struct BoardSquare* initialize_board_from_data(FILE* file) {
	board = (struct BoardSquare*) malloc(board_length * sizeof(struct BoardSquare));
	all_cats = (struct BoardSquare**) malloc (sizeof (struct BoardSquare*) * cat_number);

	if(board == NULL || all_cats == NULL) {
		printf("Error allocating memory");
		exit(1);
	}

	while(getc(file) != '{');
    for(int i = 0; i < board_length; i++) {
		char character = getc(file);
        if(character == 'e') {
			board[i].state = empty;
			board[i].content = ' ';
		} else if(character == 'c') {
			board[i].state = cat;
			board[i].content = 'C';
		} else if(character == 'r') {
			board[i].state = rat;
			board[i].content = 's';
		}

		if(i <= 29) {
			board[i].is_refuge = false;
			board[i].number = i + 1;
		} else if(i >= 30 && i <=32) {
			board[i].is_refuge = true;
			board[i].number = i + 3;
		} else if( i >=33 && i <= 34) {
			board[i].is_refuge = false;
			board[i].number = i - 2;
		} else {
			board[i].is_refuge = true;
			board[i].number = i + 1;
		}

		if(i <= 34) {
			board[i].row = i / 7 + 1;
			board[i].column = i % 7 + 1;
		} else {
			board[i].row = (i - 32) / 3 + 5;
			board[i].column = (i - 32) % 3 + 3;
		}
    }
	while(getc(file) != '}');
	while(getc(file) != '[');
	fscanf(file, "%d %d ]", &eliminated_cats, &eliminated_rats);
	
	return board;
}
void empty_board() {
	free(board);
	free(all_cats);
	board = NULL;
	all_cats = 	NULL;
}

void display_board() {
	for(int k = 1; k <= 5; k++) {
		for(int j = 1; j <= 5; j++) {
			for(int i=1; i<=7; i++) {
				int array_index = (i-1) + 7 * (k-1);
				switch(j) {
					case 1:
						if(k != 1) {	
							if(i == 1) {
								printf("  |   /");
							} else if(i == 7) {
								printf("\\   |  ");
							} else {
								printf("\\   |   /");
							}
						}
						break;
					case 5:
						if(k != 5) {	
							if(i == 1) {
								printf("  |   \\");
							} else if(i == 7) {
								printf("/   |  ");
							} else {
								printf("/   |   \\");
							}
						} else if(k == 5 && i >= 3 && i <= 5) {	
							if(i == 3) {
								printf("    |   \\");
							} else if(i == 5) {
								printf("/   |    ");
							} else {
								printf("/   |   \\");
							}
						}
						else {
							if(i == 1) {
								printf("       ");
							} else if(i == 7) {
								printf("       ");
							} else {
								printf("         ");
							}
						}
						break;
					case 2:
						if(i == 1) {
							printf(",");
						} else {
							printf("  ,");
						}

						if(board[array_index].number < 10) {
							printf("_%d", board[array_index].number);
						}
						else {
							printf("%d", board[array_index].number);
						}

						if(i == 7) {
							printf("_,");
						} else {
							printf("_,  ");
						}
						break;
					case 3:
						if(i == 1) {
							printf("| %c |--", board[array_index].content);
						} else if(i == 7) {
							printf("--| %c |", board[array_index].content);
						} else {
							printf("--| %c |--", board[array_index].content);
						}
						break;
					case 4:
						if(i == 1) {
							printf("`---'  ");
						} else if(i == 7) {
							printf("  `---'");
						} else {
							printf("  `---'  ");
						}
						break;
				}
			}
			printf("\n");
		}
	}

	for(int k = 1; k <= 2; k++) {
		for(int j = 1; j <= 5; j++) {
			printf("                  ");
			for(int i=1; i<=3; i++) {
				int array_index = (i + 34) + 3 * (k-1);
				switch(j) {
					case 1:	
						if(i == 1) {
							printf("  |   /");
						} else if(i == 3) {
							printf("\\   |  ");
						} else {
							printf("\\   |   /");
						}
						break;
					case 5:
						if(k != 2) {	
							if(i == 1) {
								printf("  |   \\");
							} else if(i == 3) {
								printf("/   |  ");
							} else {
								printf("/   |   \\");
							}
						}
						break;
					case 2:
						if(i == 1) {
							printf(",");
						} else {
							printf("  ,");
						}

						if(board[array_index].number < 10) {
							printf("_%d", board[array_index].number);
						}
						else {
							printf("%d", board[array_index].number);
						}

						if(i == 3) {
							printf("_,");
						} else {
							printf("_,  ");
						}
						break;
					case 3:
						if(i == 1) {
							printf("| %c |--", board[array_index].content);
						} else if(i == 3) {
							printf("--| %c |", board[array_index].content);
						} else {
							printf("--| %c |--", board[array_index].content);
						}
						break;
					case 4:
						if(i == 1) {
							printf("`---'  ");
						} else if(i == 3) {
							printf("  `---'");
						} else {
							printf("  `---'  ");
						}
						break;
				}
			}
			printf("                  ");
			printf("\n");
		}
	}
}

struct BoardSquare* find_square(int row_index, int col_index) {
	for(int i = 0; i < board_length; i++) {
		if(board[i].row == row_index && board[i].column == col_index)
			return board + i;
	}
	
	return &not_a_square;
}

struct BoardSquare* find_square_from_number(int number) {
	for(int i = 0; i < board_length; i++) {
		if(board[i].number == number)
			return board + i;
	}

	return &not_a_square;
}

struct BoardSquare** find_all_cats() {
	int k = 0;

	for(int i = 0; i < board_length; i++) {
		if(is_cat(board[i])) {
			all_cats[k++] = board + i;
		}
	}

	for(int i = k; i < cat_number; i++) {
		all_cats[i] = &not_a_square;
	}

	return all_cats;
}

void execute_move(struct BoardSquare* from, struct BoardSquare* to) {
	to->content = from->content;
	to->state = from->state;
			
	from->content = ' ';
	from->state = empty;
}

void blonder_piece_at(struct BoardSquare* from) {
	if(from->state == cat)
		eliminated_cats++;
	else if(from->state == rat)
		eliminated_rats++;
	execute_move(from, from);
}

void elimate_rat_between(struct BoardSquare from, struct BoardSquare to) {
	struct BoardSquare* rat_square = find_square((from.row + to.row) / 2, (from.column + to.column) /2);
	blonder_piece_at(rat_square);
}

void place_cats(int first, int second) {
	if(first < 22 || first > 28 || second < 22 || second > 28) {
		printf("The cats must be placed within the 22nd to 28th squares\nTry again: ");
		scanf("%d %d", &first, &second);
		place_cats(first, second);
	} else if(first == second){
		printf("The cats cannot be on the same square\nTry again: ");
		scanf("%d %d", &first, &second);
		place_cats(first, second);
	} else {
		struct BoardSquare* first_ok;

		first_ok = find_square_from_number(first);
		first_ok->content = 'C';
		first_ok->state = cat;

		first_ok = find_square_from_number(second);
		first_ok->content = 'C';
		first_ok->state = cat;

		printf("The cats are now placed...\n\n");
		display_board();
	}
}

bool have_rats_filled_refuge() {
	for(int i = 0; i < board_length; i++) {
		if(board[i].is_refuge && board[i].state != rat)
			return false;
	}
	return true;
}

