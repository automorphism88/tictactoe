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

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "cli.h"
#include "tictactoe.h"

int main()
{
    int verbose=get_choice("Show computer evaluations [Y/N]?");
    srand(time(NULL));
    int num_players;
    int turn;
    int* board;
    /*Main loop*/
    do {
        board=calloc(9,sizeof(int));
        if (board == NULL) {
            fprintf(stderr,"Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        num_players = get_num_players();
        if (num_players==1)
            turn = get_choice("Play first [Y/N]?");
        else
            turn = 0;
        /*Play the game*/
        do {
            display_board(board);
            switch (num_players) {
            case 0:
                if (turn==0) {
                    if (verbose)
                        display_evaluations(board,1);
                    computer_move(board,1);
                    turn=1;
                } else {
                    if (verbose)
                        display_evaluations(board,2);
                    computer_move(board,2);
                    turn=0;
                }
                break;
            case 1:
                if (turn==0) {
                    if (verbose)
                        display_evaluations(board,2);
                    computer_move(board,2);
                    turn=1;
                } else {
                    if (verbose)
                        display_evaluations(board,1);
                    player_move(board,1);
                    turn=0;
                }
                break;
            case 2:
                if (turn==0) {
                    if (verbose)
                        display_evaluations(board,1);
                    player_move(board,1);
                    turn=1;
                } else {
                    if (verbose)
                        display_evaluations(board,2);
                    player_move(board,2);
                    turn=0;
                }
                break;
            }
        } while (!game_over(board));
        done(board);
        free(board);
        if ((num_players == 0) &&
            ((rand() % 100) == 0)) {
            printf("A strange game. The only winning move is not to play.\n");
            printf("How about a nice game of chess?\n");
        }
    } while (get_choice("Play again [Y/N]?"));
    return EXIT_SUCCESS;
}
