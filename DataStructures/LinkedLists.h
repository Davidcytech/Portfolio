#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H
#include "Process.h"

typedef struct Node {
    Process process;
    struct Node *next;
} Node;

void addProcess(Node **head, int pid, const char name[], int priority);
void listProcesses(Node *head);
Node *findProcess(Node *head, int pid);
void removeProcess(Node **head, int pid);
void freeList(Node **head);

#endif