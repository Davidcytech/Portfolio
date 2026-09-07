//
// Created by torch on 8/30/26.
//

#ifndef QUEUE_H
#define QUEUE_H
#include "Process.h"

typedef struct QueueNode {
    Process process;
    struct QueueNode *next;
} QueueNode;

void enqueue(QueueNode **front, QueueNode **rear, Process process);
void dequeue(QueueNode **front, QueueNode **rear);
QueueNode *peekQueue(QueueNode *front);
void listQueue(QueueNode *front);
void freeQueue(QueueNode **front, QueueNode **rear);

#endif