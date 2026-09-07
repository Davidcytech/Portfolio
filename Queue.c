#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
void enqueue(QueueNode **front, QueueNode **rear, Process process)
{
    QueueNode *novo = malloc(sizeof *novo);

    if (novo == NULL) {
        printf("It wasn't possible to allocate memory\n");
        return;
    }

    novo->process = process;
    novo->next = NULL;

    if (*front == NULL) { //if there is no front the queue would be empty
        *front = novo;
        *rear = novo;
    }
    else {
        (*rear)->next = novo; //if the next element to the rear is the last one on the queue then it is the only element
        *rear = novo;
    }
}
void dequeue(QueueNode **front, QueueNode **rear)
{
    if (*front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    QueueNode *temp = *front;
    *front = (*front)->next;//here we promote the second element to the first element after taking it off the queue
    //we dont need to move rear up a slot on the queue because it continues to be the last element
    if (*front == NULL) {
        *rear = NULL;
    }

    free(temp);
}
QueueNode *peekQueue(QueueNode *front) { //peeking only means checking the next element to come out of the queue
        if (front == NULL) {
            printf("Stack is empty\n");
            return NULL; //The function gets interrupted to avoid a segmentation fault
        }
        else {
            return front;
        }
}
void listQueue(QueueNode *front) {

    QueueNode *current = front;

    while (current != NULL) {
        printf("%d - %s - %d\n",
               current->process.pid,
               current->process.name,
               current->process.priority);

        current = current->next;
    }
}
void freeQueue(QueueNode **front, QueueNode **rear)
{
    QueueNode *current = *front;

    while (current != NULL) {
        QueueNode *nextNode = current->next;

        free(current);

        current = nextNode; // Same approach as freeList(): store the next node before freeing the current one
    }

    *front = NULL;
    *rear = NULL; //Queue has these two pointers that we need to clear before we can free the memory
}