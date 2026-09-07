//
// Created by torch on 8/31/26.
//

#ifndef DATASTRUCTURES_HASHTABLE_H
#define DATASTRUCTURES_HASHTABLE_H
#include "Process.h"
#define TABLE_SIZE 10
typedef struct HashNode {
    Process process;
    struct HashNode *next;
} HashNode;
typedef struct {
    HashNode *buckets[TABLE_SIZE];
} HashTable;

void initHashTable(HashTable *table);
void insert(HashTable *table, Process process);
HashNode *search(HashTable *table, int pid);
void removeHashProcess(HashTable *table, int pid);
void displayHashTable(HashTable *table);
void freeHashTable(HashTable *table);
#endif //DATASTRUCTURES_HASHTABLE_H
