#include "ReversiUtils.h"

//void printReversiPos(ReversiPos move) {
//    printf("%c%d\n", move.col + 'a', move.row + 1);
//}

bool isInBoardArea(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

bool isPlayerPos(char ch, char player) {
    return (ch != ' ' && ch == player);
}

bool isEmptyPos(char check) {
    return (check == EMPTY);
}

