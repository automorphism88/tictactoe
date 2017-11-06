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

extern int leaf_nodes_evaluated;

void computer_move(int* board,int side);
int evaluate_node(const int* board,int side,int depth);
int game_over(const int* board);
int play_move(int* board,int side,int move);

#endif
