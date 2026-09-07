#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    char name[50];
    int priority;
} Process;

#endif
