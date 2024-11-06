#include "GameLogic.h"
#include <string.h>

// Plays one turn for the current player on the given board.
// Finds all valid moves, evaluates them using a move tree expansion, and selects the best move based on scoring.
// The best move is made, and the function returns 1 to indicate that the turn was successfully played, or 0 if no valid moves are available.
int PlayOneTurn(Board board, Player player, int height) {
    MovesList moves = FindMoves(board, player);

	if (isEmptyList(moves))
        return 0;

    MovesListNode* curr = moves.head;
    ReversiPos bestMove;
    MovesTree* moveTree;
    int moveScore, tmpMoveScore;

    //Initialize parameters
    moveTree = ExpandMove(board, player, &(curr->pos), height);
    moveScore = ScoreTree(moveTree);
    bestMove.col = curr->pos.col;
    bestMove.row = curr->pos.row;

    while (curr->next != NULL) {
        FreeMovesTree(*moveTree);
        curr = curr->next;

        moveTree = ExpandMove(board, player, &(curr->pos), height);
        if (moveTree == NULL) {
            break;
        }
        tmpMoveScore = ScoreTree(moveTree);
        if (tmpMoveScore > moveScore) {
            moveScore = tmpMoveScore;
            bestMove = curr->pos;
        }
        if (tmpMoveScore == moveScore) {
            if ((bestMove.row > curr->pos.row) || ((bestMove.row == curr->pos.row) && (bestMove.col > curr->pos.col))) {
                (bestMove = curr->pos);
            }
        }
    }

    printf("\n%c's turn: ", player);
    printReversiPos(bestMove);
    MakeMove(board, player, &bestMove);

    return 1;
}

// Checks if a move is valid for the current player on the given board at the specified position.
// Returns the number of flips if the move is valid, or 0 if the move is invalid.
int CheckMove(Board board, Player player, ReversiPos* move) {
    char opponent = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
    int numOfFlips;
    int dirArr[DIRECTIONS];

    if ((!isInBoardArea(move->row, move->col)) || (!isEmptyPos(board[move->row][move->col])))
        return 0;

    numOfFlips = numOfReversePos(board, player, opponent, move, dirArr);

    return numOfFlips;
}

// Makes the specified move for the current player on the board, flipping opponent's discs as necessary.
// This function will update the board and flip discs in the directions where flips are possible.
void MakeMove(Board board, Player player, ReversiPos* move) {
    char row = move->row;
    char col = move->col;
    int sumOfFlips, flips, j;
    char opponent = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
    int dirFlipsArr[DIRECTIONS];

    // Array for all possible directions to check for flips
    int dirRow[] = { -1, -1, -1, 0, 0, 1, 1, 1 };   //move up or dowm
    int dirCol[] = { -1, 0, 1, -1, 1, -1, 0, 1 };   //move right or left

    sumOfFlips = numOfReversePos(board, player, opponent, move, dirFlipsArr);

    // Place the player's disc on the target square
    board[row][col] = player;

    j = 0;
    while ((sumOfFlips > 0) && (j < DIRECTIONS)) {
        row = move->row;
        col = move->col;
        flips = dirFlipsArr[j];

        while (flips > 0) {
            row += dirRow[j];
            col += dirCol[j];
            board[row][col] = player;
            flips--;
            sumOfFlips--;
        }
        j++;
    }
}

// Counts how many opponent's pieces would be flipped if the player made a move at the specified position.
// Also updates the direction array `dirArr` with the number of flips in each possible direction (if any).
// Returns the total number of flips that would occur for this move.
int numOfReversePos(Board board, Player player, Player opponent, ReversiPos* move, int* dirArr) {
    char row = move->row;
    char col = move->col;
    int i, curCol, curRow, flips, sumFlips = 0;

    //Set the available directions of flips array data to be all 0
    for (i = 0; i < DIRECTIONS; i++)
        dirArr[i] = 0;

    // Array for all possible directions to check for flips
    int dirRow[] = { -1, -1, -1, 0, 0, 1, 1, 1 };   //move up or dowm
    int dirCol[] = { -1, 0, 1, -1, 1, -1, 0, 1 };   //move right or left

    // Check each direction
    for (i = 0; i < DIRECTIONS; i++) {
        curRow = row + dirRow[i];
        curCol = col + dirCol[i];
        flips = 0;

        // Check how many flips need to be updated
        while ((isPlayerPos(board[curRow][curCol], opponent) && (isInBoardArea(curRow, curCol)))) {
            curRow += dirRow[i];
            curCol += dirCol[i];
            flips++;
        }
        if ((isPlayerPos(board[curRow][curCol], player) && flips > 0) && (isInBoardArea(curRow, curCol))) {
            dirArr[i] += flips;
            sumFlips += flips;
        }
    }

    return sumFlips;
}

void PlayGame(Board board, Player first, int h1, int h2) {
    Player player = first;
    Player opponent = (first == PLAYER_X) ? PLAYER_O : PLAYER_X;
    int hight = h1;
    int flag = 1;

    while (flag != NO_MORE_MOVES) {
        printBoard(board);
        flag = PlayOneTurn(board, player, hight);

        //switch players
        (player == PLAYER_X) ? (player = PLAYER_O) : (player = PLAYER_X);
        (hight == h1) ? (hight = h2) : (hight = h1);
    }

    //Print end game
    endGamePrint(board);
}

MovesTree* ExpandMove(Board b, Player p, ReversiPos* move, int height) {
    MovesTree* tree = (MovesTree*)malloc(sizeof(MovesTree));
    if (tree == NULL) {
        return NULL;
    }

    //initialize tree
    char opponent = (p == PLAYER_X) ? PLAYER_O : PLAYER_X;
    MovesList opponentList;
    int ind;
    Board tmpBoard;

    memcpy(tree->board, b, sizeof(Board));
    tree->root = (MovesTreeNode*)malloc(sizeof(MovesTreeNode));
    if (tree->root == NULL) {
        free(tree);
        return NULL;
    }
    tree->root->pos.col = move->col;
    tree->root->pos.row = move->row;
    tree->root->player = p;
    tree->root->flips = CheckMove(tree->board, p, move);
    memcpy(tmpBoard, b, sizeof(Board));
    MakeMove(tmpBoard, p, move);
    opponentList = FindMoves(tmpBoard, opponent);
    tree->root->num_moves = listLen(opponentList);
    // END

    // Reached max height or no more valid moves (breakpoint)
    if ((height == 0) || (tree->root->flips == 0)) {
        tree->root->next_moves = NULL;
        tree->root->num_moves = 0;
        return tree;
    }

    tree->root->next_moves = (MovesTreeNode**)malloc((tree->root->num_moves) * sizeof(MovesTreeNode*));
    if (tree->root->next_moves == NULL) {
        free(tree->root);
        free(tree);
        return NULL;
    }

    ind = 0;
    MovesListNode* current = opponentList.head;
    while ((current != NULL)) {
        MovesTree* subTree = ExpandMove(tmpBoard, opponent, &(current->pos), height - 1);
        if (subTree == NULL)
            tree->root->next_moves[ind] = NULL;
        else
            tree->root->next_moves[ind] = subTree->root;
        ind++;
        current = current->next;
    }
    return tree;
}

// Finds all legal moves for a player on the given board. 
// Returns a linked list of all possible moves, each associated with the number of discs to be flipped.
// If no valid moves exist, an empty list is returned.
MovesList FindMoves(Board board, Player player) {
    MovesList moves;
    int row, col, flips;
    ReversiPos move;
    MovesListNode* curr;

    makeEmptyList(&moves);
    curr = moves.head;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            move.col = col;
            move.row = row;
            flips = CheckMove(board, player, &move);
            if (flips) {
                insertDataToEndList(&moves, flips, move);
            }
        }
    }
    return moves;
}
