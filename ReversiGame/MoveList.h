#ifndef MOVE_LIST_H
#define MOVE_LIST_H
#include "ReversiGame.h"

typedef struct _movesListNode {
    ReversiPos pos;
    int flips;
    struct _movesListNode* next;
} MovesListNode;

typedef struct _movesList {
    MovesListNode* head;
    MovesListNode* tail;
} MovesList;

MovesListNode* createNewListNode(MovesListNode* next, int flips, ReversiPos move);
bool isEmptyList(MovesList lst);
void makeEmptyList(MovesList* lst);
void insertDataToEndList(MovesList* lst, int flips, ReversiPos move);
void insertNodeToEndList(MovesList* lst, MovesListNode* newTail);
int listLen(MovesList lst);

#endif // MOVE_LIST_H
