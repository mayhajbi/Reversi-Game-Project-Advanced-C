#include "ReversiGame.h"

// Prints game board
void printBoard(Board board) {
    int i, j;

    printf("\n");
    printf("+-+-+-+-+-+-+-+-+-\n");
    printf("| |a|b|c|d|e|f|g|h|\n");
    printf("+-+-+-+-+-+-+-+-+-\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("|%d|", i + 1);
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c|", board[i][j]);
        }
        printf("\n+-+-+-+-+-+-+-+-+-\n");
    }    printf("\n");

    printf("\n");
}

//Initialize 8x8 board to char ' '
void resetBoard(Board board) {
    int row, col;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = EMPTY;
        }
    }

    //// Set the initial 4 pieces (2 for each player), for the "real" Reversi Game
    //board[3][3] = PLAYER_X;
    //board[4][4] = PLAYER_X;
    //board[3][4] = PLAYER_O;
    //board[4][3] = PLAYER_O;
}

//This functions counts how many discs of each player are placed on board, and print winner message
void endGamePrint(Board b) {
    int row, col, countO = 0, countX = 0;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (b[row][col] == PLAYER_O)
                (countO)++;
            if (b[row][col] == PLAYER_X)
                (countX)++;
        }
    }

    if (countX == countO)
        printf("It's a tie!\n");
    else if (countX > countO)
        printf("%c won! %d vs %d", PLAYER_X, countX, countO);
    else
        printf("%c won! %d vs %d", PLAYER_O, countO, countX);
    printf("\n");
}

void printReversiPos(ReversiPos move) {
    printf("%c%d\n", move.col + 'a', move.row + 1);
}

bool isInBoardArea(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

bool isPlayerPos(char ch, char player) {
    return (ch != ' ' && ch == player);
}

bool isEmptyPos(char check) {
    return (check == EMPTY);
}