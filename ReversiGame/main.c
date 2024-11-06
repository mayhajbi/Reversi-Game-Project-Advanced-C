#define _CRT_SECURE_NO_WARNINGS
#include "GameLogic.h"

void main() {
    Board b;
    Player firstPlayer, opponent, p;
    int h1, h2, flag = 1;
    ReversiPos move;

    //The user chooses the first player and heights for each player
    printf("Choose player (X/O): ");
    scanf("%c", &firstPlayer);
    (firstPlayer == PLAYER_X) ? (opponent = PLAYER_O) : (opponent = PLAYER_X);
    printf("%c player, choose height: ", firstPlayer);
    scanf("%d", &h1);
    printf("%c player, choose height: ", opponent);
    scanf("%d", &h2);
    printf("\n");

    //Initialize board
    resetBoard(b);
    printf("Initializing board\n");

    while (flag == 1) {
        printf("Please choose a player to place on board:");
        getchar();
        scanf("%c", &p);

        printf("Please choose a row and a column:");
        getchar();
        scanf("%c%c", &move.row, &move.col);
        (b)[(int)(move.row - '1')][(int)(move.col - 'a')] = p;

        printf("Enter 1 to continue, 0 to end:");
        getchar();
        scanf("%d", &flag);
    }

    PlayGame(b, firstPlayer, h1, h2);
}
