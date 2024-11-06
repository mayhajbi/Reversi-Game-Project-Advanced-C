#include "MoveList.h"

MovesListNode* createNewListNode(MovesListNode* next, int flips, ReversiPos move) {
    MovesListNode* node = (MovesListNode*)malloc(sizeof(MovesListNode));
    if (node != NULL) {
        node->pos.col = move.col;
        node->pos.row = move.row;
        node->flips = flips;
        node->next = next;
    }
    return node;
}

void makeEmptyList(MovesList* lst) {
    lst->head = lst->tail = NULL;
}

void insertDataToEndList(MovesList* lst, int flips, ReversiPos move) {
    MovesListNode* newTail;
    newTail = createNewListNode(NULL, flips, move);
    insertNodeToEndList(lst, newTail);
}

void insertNodeToEndList(MovesList* lst, MovesListNode* newTail) {
    if (isEmptyList(*lst))
        lst->head = lst->tail = newTail;
    else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

bool isEmptyList(MovesList lst) {
    return (lst.head == NULL);
}

// Returns the length of the move list (linked list), which is the number of valid moves available for the player.
int listLen(MovesList lst) {
    MovesListNode* curr = lst.head;
    int len = 0;

    while (curr != NULL) {
        len++;
        curr = curr->next;
    }

    return len;
}