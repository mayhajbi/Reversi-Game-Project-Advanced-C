#include "MoveTree.h"

void FreeMovesTree(MovesTree tr) {
    FreeMovesTreeHelper(tr.root);
}

void FreeMovesTreeHelper(MovesTreeNode* root) {
    if (root == NULL)
        return;

    for (int i = 0; i < root->num_moves; i++) {
        FreeMovesTreeHelper((root->next_moves[i]));
    }
    free(root->next_moves);
    free(root);
}

int ScoreTree(MovesTree* movesTree) {
    Player player = movesTree->root->player;
    int sum = 0, res;

    scoreTreeHelper(movesTree->root, player, player, &sum, &res);
    return res;
}

void scoreTreeHelper(MovesTreeNode* node, Player firstPlayer, Player currPlayer, int* sum, int* res) {
    if (node == NULL)
        return;

    if (node->num_moves == 0) {
        if (currPlayer == firstPlayer)
            (*res) = (*sum) + node->flips;
        else
            (*res) = (*sum) - node->flips;
    }

    else {
        Player opponent = (currPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        int subRes, subSum, move, subRes2;

        (currPlayer == firstPlayer) ? ((*sum) += node->flips) : ((*sum) -= node->flips);
        subSum = (*sum);
        scoreTreeHelper(node->next_moves[0], firstPlayer, opponent, &subSum, res);

        for (move = 0; move < node->num_moves; move += 2) {
            subSum = (*sum);
            scoreTreeHelper(node->next_moves[move], firstPlayer, opponent, &subSum, &subRes);

            subSum = (*sum);
            if (move + 1 < node->num_moves) {
                scoreTreeHelper(node->next_moves[move + 1], firstPlayer, opponent, &subSum, &subRes2);
                (subRes) = (currPlayer == firstPlayer) ? min((subRes2), subRes) : max((subRes2), subRes);
            }
            (*res) = (currPlayer == firstPlayer) ? min((subRes), *res) : max((subRes), *res);
        }
    }
}