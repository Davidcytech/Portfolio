#include <stdio.h>
#include "LinkedLists.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "InputUtils.h"

void linkedListMenu(void)
{
    Node *head = NULL;
    int option;
    int pid;
    Process process;

    do {
        printf("\n=== Linked List ===\n");
        printf("1. Add process\n");
        printf("2. Remove process\n");
        printf("3. Find process\n");
        printf("4. List processes\n");
        printf("5. Free list\n");
        printf("0. Back\n");

        option = readInt("Option: ");

        switch (option) {
            case 1:
                process = readProcess();
                addProcess(&head, process.pid, process.name, process.priority);
                break;

            case 2:
                pid = readInt("PID to remove: ");
                removeProcess(&head, pid);
                break;

            case 3:
                pid = readInt("PID to find: ");
                Node *result = findProcess(head, pid);

                if (result != NULL) {
                    printf("%d - %s - %d\n",
                           result->process.pid,
                           result->process.name,
                           result->process.priority);
                }
                else {
                    printf("Process not found\n");
                }
                break;

            case 4:
                listProcesses(head);
                break;

            case 5:
                freeList(&head);
                printf("List cleared\n");
                break;

            case 0:
                freeList(&head);
                break;

            default:
                printf("Invalid option\n");
        }

    } while (option != 0);
}


void stackMenu(void)
{
    StackNode *top = NULL;
    int option;
    Process process;

    do {
        printf("\n=== Stack ===\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. List stack\n");
        printf("5. Free stack\n");
        printf("0. Back\n");

        option = readInt("Option: ");

        switch (option) {
            case 1:
                process = readProcess();
                push(&top, process);
                break;

            case 2:
                pop(&top);
                break;

            case 3:
                {
                    StackNode *result = peek(top);

                    if (result != NULL) {
                        printf("%d - %s - %d\n",
                               result->process.pid,
                               result->process.name,
                               result->process.priority);
                    }
                }
                break;

            case 4:
                listStack(top);
                break;

            case 5:
                freeStack(&top);
                printf("Stack cleared\n");
                break;

            case 0:
                freeStack(&top);
                break;

            default:
                printf("Invalid option\n");
        }

    } while (option != 0);
}


void queueMenu(void)
{
    QueueNode *front = NULL;
    QueueNode *rear = NULL;

    int option;
    Process process;

    do {
        printf("\n=== Queue ===\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. List queue\n");
        printf("5. Free queue\n");
        printf("0. Back\n");

        option = readInt("Option: ");

        switch (option) {
            case 1:
                process = readProcess();
                enqueue(&front, &rear, process);
                break;

            case 2:
                dequeue(&front, &rear);
                break;

            case 3:
                {
                    QueueNode *result = peekQueue(front);

                    if (result != NULL) {
                        printf("%d - %s - %d\n",
                               result->process.pid,
                               result->process.name,
                               result->process.priority);
                    }
                }
                break;

            case 4:
                listQueue(front);
                break;

            case 5:
                freeQueue(&front, &rear);
                printf("Queue cleared\n");
                break;

            case 0:
                freeQueue(&front, &rear);
                break;

            default:
                printf("Invalid option\n");
        }

    } while (option != 0);
}


void hashTableMenu(void)
{
    HashTable table;
    initHashTable(&table);

    int option;
    int pid;
    Process process;

    do {
        printf("\n=== Hash Table ===\n");
        printf("1. Insert\n");
        printf("2. Remove\n");
        printf("3. Search\n");
        printf("4. Display hash table\n");
        printf("5. Free hash table\n");
        printf("0. Back\n");

        option = readInt("Option: ");

        switch (option) {
            case 1:
                process = readProcess();
                insert(&table, process);
                break;

            case 2:
                pid = readInt("PID to remove: ");
                removeHashProcess(&table, pid);
                break;

            case 3:
                pid = readInt("PID to find: ");

                {
                    HashNode *result = search(&table, pid);

                    if (result != NULL) {
                        printf("%d - %s - %d\n",
                               result->process.pid,
                               result->process.name,
                               result->process.priority);
                    }
                    else {
                        printf("Process not found\n");
                    }
                }
                break;

            case 4:
                displayHashTable(&table);
                break;

            case 5:
                freeHashTable(&table);
                printf("Hash table cleared\n");
                break;

            case 0:
                freeHashTable(&table);
                break;

            default:
                printf("Invalid option\n");
        }

    } while (option != 0);
}


int main(void)
{
    int option;

    do {
        printf("\n==============================\n");
        printf("     DATA STRUCTURES IN C\n");
        printf("==============================\n");
        printf("1. Linked List\n");
        printf("2. Stack\n");
        printf("3. Queue\n");
        printf("4. Hash Table\n");
        printf("0. Exit\n");

        option = readInt("Option: ");

        switch (option) {
            case 1:
                linkedListMenu();
                break;

            case 2:
                stackMenu();
                break;

            case 3:
                queueMenu();
                break;

            case 4:
                hashTableMenu();
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option\n");
        }

    } while (option != 0);

    return 0;
}
