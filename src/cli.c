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
#include<string.h>
#include "cli.h"
#include "tictactoe.h"

static inline void display_square(const int* board,int pos);
static int one_legal_move(const int* board);
static inline void print_evaluation(int evaluation);
extern inline void print_result(int result);
static int valid_move(const int* board,int move);

void display_board(const int* board) {
    static const char* begin_row="|     |     |     |\n|  ";
    static const char* end_row="  |\n|     |     |     |\n";
    static const char* new_column="  |  ";
    static const char* new_row="-------------------\n";
    int i;
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

void display_evaluations(const int* board,int side) {
    static const char* header=" Move | Evaluation (1 move = 2 plies)\n";
    static const char* divider="-------------------------------------\n";
    leaf_nodes_evaluated=0;
    int values[9];
    int* temp_board=malloc(9*sizeof(int));
    if (temp_board == NULL) {
        fprintf(stderr,"Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    int i;
    for (i=0;i<9;i++) {
        if (board[i] == 0) {
            memcpy(temp_board,board,9*sizeof(int));
            temp_board[i]=side;
            values[i]=evaluate_node(temp_board,side,0);
        }
    }
    free(temp_board);
    printf("Evaluated %d leaf node(s)\n%s%s%s",
           leaf_nodes_evaluated,divider,header,divider);
    for (i=0;i<9;i++) {
        if (board[i] == 0) {
            printf("   %d  | ",i+1);
            print_evaluation(values[i]);
        }
    }
    printf("%s",divider);
}

static inline void display_square(const int* board,int pos) {
    if (board[pos] == 0)
        printf("%d",pos+1);
    else if (board[pos] == 1)
        printf("X");
    else if (board[pos] == 2)
        printf("O");
}

int get_choice(const char* prompt) {
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

int get_num_players() {
    static const char* prompt="Number of players? ";
    int c;
    int ret=-1;
    while ((ret < 0)||(ret > 2)) {
        printf("%s",prompt);
        while (scanf("%d",&ret) != 1) {
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
static int one_legal_move(const int* board) {
    int num_free=0;
    int last_free=-1;
    int i;
    for (i=0;i<9;i++) {
        if (board[i] == 0) {
            num_free++;
            last_free=i;
        }
    }
    if (num_free == 1) {
        printf("You must play %d since it is the only empty square\n",
               last_free+1);
        return last_free+1;
    } else
        return 0;
}

void player_move(int* board,int side) {
    int choice = one_legal_move(board);
    int c;
    if (choice == 0) {
        do {
            printf("Enter a move for player %d: ",side);
            while (scanf("%d",&choice) != 1) {
                printf("Input is not a valid number\n");
                while (((c=getchar()) != EOF) && (c != '\n'));
                printf("Enter a move for player %d: ",side);
            }
        } while (!valid_move(board,choice));
    }
    play_move(board,side,choice-1);
}

static inline void print_evaluation(int evaluation) {
    if (evaluation == 0)
        printf("Draw\n");
    else if (evaluation < 0)
        printf("Loses in %d move(s)\n",(evaluation+11)/2);
    else
        printf("Wins in %d move(s)\n",(12-evaluation)/2);
}

static int valid_move(const int* board,int move) {
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
