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

#ifndef CLI_H_
#define CLI_H_

#include <stdint.h>
#include <stdio.h>

void display_board(const int_fast8_t* board);
void display_evaluations(const int_fast8_t* board,int_fast8_t side);
int_fast8_t get_choice(const char* prompt);
int_fast8_t get_num_players();
void player_move(int_fast8_t* board,int_fast8_t side);
inline void print_result(int_fast8_t result) {
    if (result == -1)
        printf("Draw!\n");
    else if (result == 1)
        printf("Player 1 wins!\n");
    else if (result == 2)
        printf("Player 2 wins!\n");
}

#endif
