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

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

extern int_fast32_t leaf_nodes_evaluated;

void computer_move(int_fast8_t* board,int_fast8_t side);
int_fast8_t
evaluate_node(const int_fast8_t* board,int_fast8_t side,int_fast8_t depth,
              int_fast8_t alpha,int_fast8_t beta);
int_fast8_t game_over(const int_fast8_t* board);
int_fast8_t play_move(int_fast8_t* board,int_fast8_t side,int_fast8_t move);

#endif
