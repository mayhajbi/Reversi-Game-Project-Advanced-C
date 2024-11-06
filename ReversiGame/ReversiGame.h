#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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
void endGamePrint(Board b);
void printReversiPos(ReversiPos move);
bool isInBoardArea(int row, int col);
bool isPlayerPos(char ch, char player);
bool isEmptyPos(char check);

#endif // REVERSI_GAME_H
