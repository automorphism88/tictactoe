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
#include "tictactoe.h"

int leaf_nodes_evaluated=0;

void computer_move(int* board,int side) {
    leaf_nodes_evaluated=0;
    int values[9];
    int i;
    int* temp_board=malloc(9*sizeof(int));
    if (temp_board == NULL) {
        fprintf(stderr,"Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    /*Evaluate each possible move, assigning a value
     of -100 to illegal moves*/
    int max_value=-100;
    for (i=0;i<9;i++) {
        if (board[i] == 0) {
            memcpy(temp_board,board,9*sizeof(int));
            temp_board[i]=side;
            values[i]=evaluate_node(temp_board,side,0);
            if (values[i] > max_value)
                max_value=values[i];
        } else
            values[i]=-100;
    }
    free(temp_board);
    /*Randomly select one of the top scoring moves*/
    int num_best=0;
    int best[9];
    for (i=0;i<9;i++) {
        if (values[i] == max_value) {
            best[num_best]=i;
            num_best++;
        }
    }
    int move,rand1,rand2;
    /*If the board is empty, choose randomly between center, corner, or
      edge with probability 1/3 of each*/
    if (num_best == 9) {
        rand1=rand()%3;
        if (rand1 == 0)
            move=4;
        else {
            rand2=rand()%4;
            if (rand2 < 2)
                move=rand1+2*rand2-1;
            else
                move=rand1+2*rand2;
        }
    } else
        move = best[rand()%num_best];
    if (play_move(board,side,move) != 0) {
        fprintf(stderr,"Fatal error in computer_move()\n");
        exit(EXIT_FAILURE);
    }
}

/*Recursive function to look ahead until the end of the game*/
int evaluate_node(const int* board,int side,int depth) {
    int eval=game_over(board);
    if (eval == side) {
        leaf_nodes_evaluated++;
        return 10-depth;
    }
    else if (eval == -1) {
        leaf_nodes_evaluated++;
        return 0;
    }
    else if (eval == 0) {
        int value;
        int* temp_board=malloc(9*sizeof(int));
        if (temp_board == NULL) {
            fprintf(stderr,"Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        /*For each free square, check what happens if we play there*/
        int i;
        int best=-100;
        for (i=0;i<9;i++) {
            if (board[i] == 0) {
                memcpy(temp_board,board,9*sizeof(int));
                temp_board[i]=(side+depth)%2+1;
                value=evaluate_node(temp_board,side,depth+1);
                if (depth % 2 == 0)
                    value*=-1;
                if (value > best)
                    best=value;
            }
        }
        free(temp_board);
        if ((depth%2)==0)
            return -1*best;
        else
            return best;
    }
    else {
        leaf_nodes_evaluated++;
        return depth-10;
    }
}

/* Returns 0 if game not over, -1 if game is a draw,
   1 if player 1 has won, 2 if player 2 has won*/
int game_over(const int* board) {
    int i,j;
    for (i=1;i<3;i++) {
        /*Check if either player has won by a horizontal*/
        for (j=0;j<3;j++)
            if ((board[3*j] == i)&&
                (board[3*j+1] == i)&&
                (board[3*j+2] == i))
                return i;
        /*Check if either player has won by a vertical*/
        for (j=0;j<3;j++)
            if ((board[j] == i)&&
                (board[j+3] == i)&&
                (board[j+6] == i))
                return i;
        /*Check if either player has won by the 0-4-8 diagonal*/
        if ((board[0] == i)&&
            (board[4] == i)&&
            (board[8] == i))
            return i;
        /*Check if either player has won by the 6-4-2 diagonal*/
        if ((board[6] == i)&&
            (board[4] == i)&&
            (board[2] == i))
            return i;
    }
    /*Neither player has won.  Check if the board is full*/
    j=0;
    for (i=0;i<9;i++)
        if (board[i] == 0) {
            j++;
            break;
        }
    if (j == 0)
        return -1;
    else
        return 0;
}

int play_move(int* board,int side,int move) {
    if (move == -1)
        return -1;
    else if ((move >= 0)&&(move <= 8)&&(board[move] == 0)) {
        printf("Player %d played %d\n",side,move + 1);
        board[move] = side;
        return 0;
    } else {
        fprintf(stderr,"Fatal error in play_move()\n");
        exit(EXIT_FAILURE);
    }
}
