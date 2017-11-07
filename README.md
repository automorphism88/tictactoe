# tictactoe
Simple text-based tic-tac-toe game written in C. Can be played with 0, 1, or 2
human players, with the computer using a
[minimax](https://en.wikipedia.org/wiki/Minimax) search with
[alpha-beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)
for the remaining player(s). The search depth is unlimited, so the computer will
always play perfectly. Where two or moves have an equal evaluation, the computer
will select randomly, with equal probability of choosing each move, except on
the first move, when the computer will choose between playing in the center,
corner, or edge with probability 1/3 of each, so that the probability of
choosing a given specific non-center square is 1/12.

## Instructions
```
make
```
then
```
./tictactoe
```
If it fails to compile, try removing `-flto` from the first line of the Makefile
(`sed -i 's/ -flto//' Makefile`) and try again (or set your `CFLAGS` environment
variable). In particular this is known to be necessary and sufficient to compile
on Android in Termux with clang. Only the standard library is used, however a
compiler supporting C99 is required.
