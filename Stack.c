#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
//Unlike lists, stacks start on the last node inserted on the list
//This makes most of the functions much easier
void push(StackNode **top, Process process) {
    //No need to go through the whole list
    StackNode *novo = malloc(sizeof(StackNode));

    if (novo == NULL) {
        printf("It wasn't possible to allocate memory\n");
        return;
    }
    novo->process = process;
    novo->next = *top; //with stacks, the last node to come in stays on the top of the list, it is also the first to get out
    *top = novo;
}
void pop(StackNode **top) {
    if (*top == NULL) {
        printf("Stack is empty\n");
    }
    else {
        StackNode *previous = *top;
        *top = previous->next;
        free(previous);
    }
}
    StackNode *peek(StackNode *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
    }
    else {
        return top;
    }
}
    void listStack(StackNode *top) {  //lists all the nodes starting from the top, just like a stack of plates
            StackNode *current = top;

            while (current != NULL) {
                printf("%d - %s - %d\n",
                       current->process.pid,
                       current->process.name,
                       current->process.priority);

                current = current->next;
            }
        }
void freeStack(StackNode **top)
{
    StackNode *current = *top;

    while (current != NULL) {
        StackNode *nextNode = current->next;

        free(current);

        current = nextNode;
    }
    *top = NULL; //same reason as for the queue
}