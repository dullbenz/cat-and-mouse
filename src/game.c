#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "player.h"
#include "general.h"
#include "board.h"
#include "move.h"
#include "data.h"

struct Player* game_winner = NULL;
struct Player players[2];
const int save_signal = 9999;
int current_player_index = 0;
bool loaded_data_flag = false;

struct Player* persist_player_with_name(int i) {
    struct Player player_ = create_player();
    printf("Player %d: Enter your username: ", i);

    // do {
        // if (fgets(player_.username, sizeof(player_.username), stdin)) {
        //     if(string_is_empty(player_.username)) {
        //         snprintf(player_.username, username_max_length + 1, "Player %d", i);
        //         // strcpy(player_.username, "Player 1");
        //     }
        //     players[i - 1] = player_;
        //     return players + i - 1;
        // } else {
        //     printf("Error Reading String,\nMake sure the username is at most 10 characters. Try again : ");
        // }
        scanf("%s", player_.username);
        if(string_is_empty(player_.username)) {
            snprintf(player_.username, username_max_length + 1, "Player %d", i);
            // strcpy(player_.username, "Player 1");
        }
        players[i - 1] = player_;
        return players + i - 1;
    // } while(true);
}

void get_and_set_player_mode(struct Player* player_) {
    printf("%s: Play with cats or rats? \n", player_->username);
    printf(">>> Cats --> 1\n");
    printf(">>> Rats --> 2\n\n");
    printf("Enter your choice: ");

    int user_choice;
    c:
    scanf("%d", &user_choice);
    switch (user_choice) {
        case 1:
            player_->plays_with = cat;
            break;
        case 2:
            player_->plays_with = rat;
            break;
        default:
            printf("invalid option\nEnter a valid choice: ");
            goto c;
            break;
    }
}

struct Player* find_cat_player() {
    for(int i = 0; i < 2; i++) {
        if(players[i].plays_with == cat)
            return players + i;
    }
    return NULL;
}

struct Player* find_rat_player() {
    for(int i = 0; i < 2; i++) {
        if(players[i].plays_with == rat)
            return players + i;
    }
    return NULL;
}

void get_and_set_cat_positions() {
    int f, t;
	printf("%s: Enter the positions for the 2 cats: ", find_cat_player()->username);
	scanf("%d %d", &f, &t);
	place_cats(f, t);
}

bool is_game_ended() {
    if(eliminated_cats >= cat_number || have_rats_filled_refuge()) {
        game_winner = find_rat_player();
        return true;
    }

    if(eliminated_rats > rat_number - refuge_square_number) {
        game_winner = find_cat_player();
        return true;
    }

	return false;
}

void save_game_state() {
    FILE* file = open_file_write();
    if(file == NULL) {
        printf("\nFile could not be saved\n");
        return;
    }

    char plays_with_1, plays_with_2;
    if(players[0].plays_with == cat) {
        plays_with_1 = 'c';
    } else if(players[0].plays_with == rat) {
        plays_with_1 = 'r';
    }

    if(players[1].plays_with == cat) {
        plays_with_2 = 'c';
    } else if(players[1].plays_with == rat) {
        plays_with_2 = 'r';
    }

    fprintf(file, "*%s *%c*%s *%c*%d *", players[0].username, plays_with_1, players[1].username, plays_with_2, current_player_index);
    save_board_state(file);
    printf("\nGame has been successfully saved\n");
    close_file();
}

void players_move_pieaces() {
    printf("%s: Enter your move\n", players[0].username);
	printf("For example: 24 25\n");
	printf("The above moves the piece at position 24 to position 25\n\nEnter 9999 at any time to save the game\n\n");
	printf("\n\n");

    int f, t;
    struct Player* current_player;
    do {
        current_player = players + current_player_index;
        do {
            printf("%s : ", current_player->username);
            scanf("%d", &f);
            if(f == save_signal ) {
                save_game_state();
                continue;
            }
            scanf("%d", &t);
            if(t == save_signal ) {
                save_game_state();
                continue;
            }
            
            if(state_is_opposite(find_square_from_number(f)->state, current_player->plays_with)){
                printf("%s please move only your pieces. Try again ...\n", current_player->username);
            } else {
                break;
            }
        } while(true);
		move_piece(find_square_from_number(f), find_square_from_number(t));
        current_player_index = (current_player_index + 1) % 2;
	} while(!is_game_ended());
    // while(!is_game_ended());
}

void start_game() {
    if(!loaded_data_flag) {
        printf("\n\nGame is starting ...");
        initialize_board();
        display_board(board);
        get_and_set_cat_positions();
    } else {
        printf("\n\nContinuing previously saved game ...");
        display_board(board);
    }
}

void initialize_2_player_mode() {
    struct Player* player_1 = persist_player_with_name(1);
    get_and_set_player_mode(player_1);
    struct Player* player_2 = persist_player_with_name(2);
    player_2->plays_with = get_opposite_state(player_1->plays_with);
    // if(player_1->plays_with == cat) {
    //     player_2->plays_with = rat;
    // } else {
    //     player_2->plays_with = cat;
    // }
}

void initialize_new_game() {
    current_player_index = 0;
    loaded_data_flag = false;
    printf("Select your game mode \n");
    printf(">>> 2 player mode --> 1\n\n");
    printf("Enter your choice: ");

    int user_choice;
    b:
    scanf("%d", &user_choice);
    switch (user_choice) {
        case 1:
            initialize_2_player_mode();
            break;
        default:
            printf("invalid option\nEnter a valid choice: ");
            goto b;
            break;
    }
}

bool load_game() {
    loaded_data_flag = true;

    FILE* file = open_file_read();
    if(file == NULL) {
        printf("\nNo save data found\n");
        return false;
    }
    players[0] = create_player();
    players[1] = create_player();
    char player_1_plays_with_, player_2_plays_with_;

    fscanf(file, "*%s *%c*%s *%c*%d *", players[0].username, &player_1_plays_with_, players[1].username, &player_2_plays_with_, &current_player_index);

    if(player_1_plays_with_ == 'c') {
        players[0].plays_with = cat;
    } else if(player_1_plays_with_ == 'r') {
        players[0].plays_with = rat;
    }

    if(player_2_plays_with_ == 'c') {
        players[1].plays_with = cat;
    } else if(player_2_plays_with_ == 'r') {
        players[1].plays_with = rat;
    }

    initialize_board_from_data(file);

    printf("\nGame loaded successfully...\n");
    close_file();

    return true;
}

void initialize_game() {
    printf("\n\n\n** Welcome to the Cat and mouse game *** \n\n");
    printf(">>> Start new game --> 1\n");
    printf(">>> Load game ---> 2\n\n");
    printf("Enter your choice: ");
    
    int user_choice;
    a:
    scanf("%d", &user_choice);
    switch (user_choice) {
        case 1:
            initialize_new_game();
            break;
        case 2:
            if(!load_game()) {
                printf("\nStarting new game....\n");
                initialize_new_game();
            }
            break;
        default:
            printf("invalid option\nEnter a valid choice: ");
            goto a;
            break;
    }
}

void end_game() {
    if(game_winner != NULL) {
        printf("\n\n****");
        for(int i = 0; i < (int) strlen(game_winner->username); i++) printf("*");
        printf("************************\n");
        printf("*** %s has won the game ...***", game_winner->username);
        printf("\n****");
        for(int i = 0; i < (int) strlen(game_winner->username); i++) printf("*");
        printf("************************\n\n\n");
        printf("Press Enter to continue ");
        
        getchar(); 
        while (getchar() != '\n');
    }
    empty_board();
}
