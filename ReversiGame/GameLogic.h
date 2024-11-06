#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "MoveList.h"
#include "MoveTree.h"
#include "ReversiGame.h"

void PlayGame(Board board, Player first, int h1, int h2);
int PlayOneTurn(Board board, Player player, int height);
int CheckMove(Board board, Player player, ReversiPos* move);
void MakeMove(Board board, Player player, ReversiPos* move);
int numOfReversePos(Board board, Player player, Player opponent, ReversiPos* move, int* dirArr);

// Functions for managing move trees and board states
MovesTree* ExpandMove(Board b, Player p, ReversiPos* move, int height);
MovesList FindMoves(Board board, Player player);

#endif // GAME_LOGIC_H
