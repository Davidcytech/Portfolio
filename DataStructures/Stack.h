#ifndef STACK_H
#define STACK_H
#include "Process.h"

typedef struct StackNode {
    Process process;
    struct StackNode *next;
} StackNode;

void push(StackNode **top, Process process);
void pop(StackNode **top);
StackNode *peek(StackNode *top);
void listStack(StackNode *top);
void freeStack(StackNode **top);

#endif
