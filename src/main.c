/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cli.h"
#include "tictactoe.h"

int main() {
    srand(time(NULL));
    int_fast8_t verbose;
    int_fast8_t num_players;
    int_fast8_t first,turn;
    int_fast8_t* board;
    int_fast8_t result;
    /*Main loop*/
    do {
        board = calloc(9,sizeof(int_fast8_t));
        malloc_fail_check(board);
        verbose = get_choice("Show computer evaluations [Y/N]?");
        num_players = get_num_players();
        if (num_players == 1)
            first = get_choice("Play first [Y/N]?");
        turn = 0;
        /*Play the game*/
        do {
            display_board(board);
            if (verbose)
                display_evaluations(board,turn%2+1);
            switch (num_players) {
            case 0:
                computer_move(board,turn%2+1);
                break;
            case 1:
                if (first) {
                    if (turn%2 == 0)
                        player_move(board,1);
                    else
                        computer_move(board,2);
                } else {
                    if (turn%2 == 0)
                        computer_move(board,1);
                    else
                        player_move(board,2);
                }
                break;
            case 2:
                player_move(board,turn%2+1);
                break;
            }
            turn++;
        } while (!(result = game_over(board)));
        print_result(result);
        display_board(board);
        free(board);
        /*See https://www.youtube.com/watch?v=NHWjlCaIrQo*/
        if ((num_players == 0) &&
            ((rand() % 100) == 0)) {
            printf("A strange game. The only winning move is not to play.\n");
            printf("How about a nice game of chess?\n");
        }
    } while (get_choice("Play again [Y/N]?"));
    return EXIT_SUCCESS;
}
