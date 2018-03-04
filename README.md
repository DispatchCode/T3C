## T3C (TicTacToe in C) solved with MiniMax with alpha-beta pruning

An implementation of the MiniMax Algorithm with alpha-beta pruning optimization to solve a simple game: Tic Tac Toe (or Tris).
This algorithm play based on the assumption that the players are perfect: in other words, IA play assuming that his opponent dosen't make error.

The binary files for Windows users are located in the `/bin` folder. 

#### Dependencies
* SDL2
* SDL Image (and libpng)

Change `CMakeLists.txt` accordingly to your SDL2 location and your compiler location and options. 

`CMakeLists.txt` is configured assuming MinGw located in `C:` and SDL is placed inside that folder.
Being this project only an example and little more, other configurations need to be setup by yourself.
