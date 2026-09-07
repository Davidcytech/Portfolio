#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedLists.h"


void addProcess(Node **head, int pid, const char name[], int priority)
{
    Node *novo = malloc(sizeof *novo);
    if (novo==NULL) {
        printf("It wasn't possible to allocate memory\n");
        return;
    }
    if (strlen(name) >= sizeof(novo->process.name)) {
        printf("The name is too long\n");
        free(novo);
        return;
    }
    novo->process.pid = pid;
    snprintf(novo->process.name, sizeof(novo->process.name), "%s", name); // Uses snprintf to prevent buffer overflow by truncating long strings and ensuring a '\0' terminator.
    novo->process.priority = priority;
    novo->next = NULL;
    if (*head == NULL) { // If the list is empty, make novo the head of the list
        *head = novo;
    }
    else { //the list already has nodes
        Node *current = *head;
        // This while loop finds the last node by checking whether the next node is NULL
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = novo; // This connects the new node to the list
    }
}
//Loop that runs through the nodes
void listProcesses(Node *head) {
    Node *current = head; // Create a pointer so we don't lose track of the original head
    while(current != NULL) {
        printf("%d - %s - %d\n",
        current->process.pid,
        current->process.name,
        current->process.priority
        );
        current = current->next;
    }
}
Node *findProcess(Node *head, int pid)
{
    Node *current = head;

    while (current != NULL) {
        if (current->process.pid == pid) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}
void removeProcess(Node **head, int pid) {
    Node *current = *head;
    Node *previous = NULL;
    while(current != NULL) {
        if(current->process.pid == pid) {
            if (previous == NULL) { // This ensures that if we delete the head node, the next node becomes the new head
                *head = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
void freeList(Node **head) {
    Node *current = *head;
    while (current!=NULL) {
        Node *nextNode = current->next; // We store the next node because we can't access current after freeing it
        free(current);
        current = nextNode; // We can do this because free() only frees the memory pointed to by current;
        // the current pointer itself still exists and can be assigned to the next node

    }
    *head = NULL;
}


