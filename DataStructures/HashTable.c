#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
//Hash tables are another type of data structure
//They are really useful for fast search due to their sorting system
void initHashTable(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL; //The buckets divide the contents inside the table based on the hash function
    }
}
int hash(int pid) //Hash Function
{
    return pid % TABLE_SIZE;
}
void insert(HashTable *table, Process process)
{
    int index = hash(process.pid);

    HashNode *novo = malloc(sizeof *novo);

    if (novo == NULL) {
        printf("It wasn't possible to allocate memory\n");
        return;
    }

    novo->process = process;
    novo->next = table->buckets[index];
    table->buckets[index] = novo;
}
void removeHashProcess(HashTable *table, int pid)
{
    int index = hash(pid);

    HashNode *current = table->buckets[index];
    HashNode *previous = NULL;

    while (current != NULL) {
        if (current->process.pid == pid) {

            if (previous == NULL) {
                table->buckets[index] = current->next;
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
HashNode *search(HashTable *table, int pid) {
    int index = hash(pid);
    HashNode *novo = table->buckets[index];
    while (novo != NULL) {
        if (novo->process.pid == pid) {
            return novo;
        }
        novo = novo->next;
    }
    return NULL;
}
void displayHashTable(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);

        HashNode *current = table->buckets[i];

        while (current != NULL) {
            printf("%d - %s - %d",
                   current->process.pid,
                   current->process.name,
                   current->process.priority);

            current = current->next;

            if (current != NULL) {
                printf(" -> ");
            }
        }

        printf("\n");
    }
}
void freeHashTable(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *current = table->buckets[i];
        while (current != NULL) {
            HashNode *nextNode = current->next;
        free(current);

            current = nextNode;
        }
        table->buckets[i] = NULL;
    }
}
