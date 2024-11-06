#ifndef REVERSI_UTILS_H
#define REVERSI_UTILS_H

#include "ReversiGame.h"

// Utility Functions
bool isInBoardArea(int row, int col);
bool isPlayerPos(char ch, char player);
bool isEmptyPos(char check);

//void printReversiPos(ReversiPos move);

#endif // REVERSI_UTILS_H
