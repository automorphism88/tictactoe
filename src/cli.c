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

#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cli.h"
#include "tictactoe.h"

static inline void display_square(const int_fast8_t* board,int_fast8_t pos);
static int_fast8_t one_legal_move(const int_fast8_t* board);
static inline void print_evaluation(int_fast8_t evaluation);
extern inline void print_result(int_fast8_t result);
static int_fast8_t valid_move(const int_fast8_t* board,int_fast8_t move);

void display_board(const int_fast8_t* board) {
    static const char* begin_row="|     |     |     |\n|  ";
    static const char* end_row="  |\n|     |     |     |\n";
    static const char* new_column="  |  ";
    static const char* new_row="-------------------\n";
    int_fast8_t i;
    for (i=0;i<3;i++) {
        printf("%s%s",new_row,begin_row);
        display_square(board,3*i+0);
        printf("%s",new_column);
        display_square(board,3*i+1);
        printf("%s",new_column);
        display_square(board,3*i+2);
        printf("%s",end_row);
    }
    printf("%s",new_row);
}

void display_evaluations(const int_fast8_t* board,int_fast8_t side) {
    static const char* header=" Move | Evaluation (1 move = 2 plies)\n";
    static const char* divider="-------------------------------------\n";
    leaf_nodes_evaluated=0;
    int_fast8_t values[9];
    int_fast8_t* temp_board=malloc(9*sizeof(int_fast8_t));
    malloc_fail_check(temp_board);
    int_fast8_t i;
    for (i=0;i<9;i++) {
        if (board[i] == 0) {
            memcpy(temp_board,board,9*sizeof(int_fast8_t));
            temp_board[i]=side;
            values[i]=evaluate_node(temp_board,side,0,-100,100);
        }
    }
    free(temp_board);
    printf("Evaluated %"PRIdFAST32" leaf node(s)\n%s%s%s",
           leaf_nodes_evaluated,divider,header,divider);
    for (i=0;i<9;i++) {
        if (board[i] == 0) {
            printf("   %"PRIdFAST8"  | ",i+1);
            print_evaluation(values[i]);
        }
    }
    printf("%s",divider);
}

static inline void display_square(const int_fast8_t* board,int_fast8_t pos) {
    if (board[pos] == 0)
        printf("%"PRIdFAST8,pos+1);
    else if (board[pos] == 1)
        printf("X");
    else if (board[pos] == 2)
        printf("O");
}

int_fast8_t get_choice(const char* prompt) {
    char choice='\0';
    int c;
    while ((choice != 'Y')&&(choice != 'y')&&
           (choice != 'N')&&(choice != 'n')) {
        printf("%s ",prompt);
        if (scanf(" %c",&choice) != 1) {
            printf("Error reading input\n");
            exit(EXIT_FAILURE);
        }
        while (((c=getchar()) != EOF) && (c != '\n'));
    }
    if ((choice == 'Y')||(choice == 'y'))
        return 1;
    else
        return 0;
}

int_fast8_t get_num_players() {
    static const char* prompt="Number of players? ";
    int c;
    int_fast8_t ret=-1;
    while ((ret < 0)||(ret > 2)) {
        printf("%s",prompt);
        while (scanf("%"SCNdFAST8,&ret) != 1) {
            printf("Input is not a valid number\n");
            while (((c=getchar()) != EOF) && (c != '\n'));
            printf("%s",prompt);
        }
        if ((ret < 0)||(ret > 2))
            printf("Error: Number of players must be 0, 1, or 2!\n");
    }
    return ret;
}

/*Check if there is only one open square on the board. If so,
  return that square (1-9). Else, return 0.*/
static int_fast8_t one_legal_move(const int_fast8_t* board) {
    int_fast8_t num_free=0;
    int_fast8_t last_free=-1;
    int_fast8_t i;
    for (i=0;i<9;i++) {
        if (board[i] == 0) {
            num_free++;
            last_free=i;
        }
    }
    if (num_free == 1) {
        printf("You must play %"PRIdFAST8" since it is the only empty square\n",
               last_free+1);
        return last_free+1;
    } else
        return 0;
}

void player_move(int_fast8_t* board,int_fast8_t side) {
    int_fast8_t choice = one_legal_move(board);
    int c;
    if (choice == 0) {
        do {
            printf("Enter a move for player %"PRIdFAST8": ",side);
            while (scanf("%"SCNdFAST8,&choice) != 1) {
                printf("Input is not a valid number\n");
                while (((c=getchar()) != EOF) && (c != '\n'));
                printf("Enter a move for player %"PRIdFAST8": ",side);
            }
        } while (!valid_move(board,choice));
    }
    play_move(board,side,choice-1);
}

static inline void print_evaluation(int_fast8_t evaluation) {
    if (evaluation == 0)
        printf("Draw\n");
    else if (evaluation < 0)
        printf("Loses in %"PRIdFAST8" move(s)\n",(evaluation+11)/2);
    else
        printf("Wins in %"PRIdFAST8" move(s)\n",(12-evaluation)/2);
}

static int_fast8_t valid_move(const int_fast8_t* board,int_fast8_t move) {
    if ((move < 1)||(move > 9)) {
        printf("Invalid move!  Please select a number from 1 to 9.\n");
        return 0;
    } else if (board[move-1] == 0)
        return 1;
    else if (board[move-1] == 1) {
        printf("Invalid move!  Player 1 has already played there.\n");
        return 0;
    } else if (board[move-1] == 2) {
        printf("Invalid move!  Player 2 has already played there.\n");
        return 0;
    } else
        return 0;
}
