#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

#include <stdbool.h>

// Constants
#define EMPTY ' '
#define BOARD_SIZE 8
#define DIRECTIONS 8
#define PLAYER_X 'X'  // Black
#define PLAYER_O 'O'  // White
#define NO_MORE_MOVES 0

// Basic Data Structures
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;

typedef struct _reversiPos {
    char row, col;
} ReversiPos;

// General Game Management Functions
void resetBoard(Board board);
void printBoard(Board board);
void PlayGame(Board board, Player first, int h1, int h2);

#endif // REVERSI_GAME_H
