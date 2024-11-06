#ifndef MOVE_TREE_H
#define MOVE_TREE_H
#include "ReversiGame.h"

typedef struct _movesTreeNode {
    ReversiPos pos;
    Player player;
    int flips;
    struct _movesTreeNode** next_moves;
    int num_moves;
} MovesTreeNode;

typedef struct _movesTree {
    Board board;
    MovesTreeNode* root;
} MovesTree;

int ScoreTree(MovesTree* movesTree);
void scoreTreeHelper(MovesTreeNode* node, Player firstPlayer, Player currPlayer, int* sum, int* res);
void FreeMovesTree(MovesTree tr);
void FreeMovesTreeHelper(MovesTreeNode* root);

#endif // MOVE_TREE_H
