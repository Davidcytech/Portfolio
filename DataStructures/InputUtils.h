
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H
#include "HashTable.h"
#include "Process.h"
//This file's purpose is to make sure that the user's input is the same as the defined type
int readInt(const char *prompt);
Process readProcess(void);

#endif // INPUT_UTILS_H