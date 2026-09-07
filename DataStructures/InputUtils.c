#include <stdio.h>
#include <string.h>
#include "InputUtils.h"
#include "Process.h"

int readInt(const char *prompt) {
    int value;
    printf("%s", prompt);

    // Tries to read an int but if it fails the buffer is cleared
    while (scanf("%d", &value) != 1) {
        printf("Invalid input! Please enter an integer: ");

        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    return value;
}

Process readProcess(void) {
    Process p;

    p.pid = readInt("PID: ");

    printf("Name: ");
    if (fgets(p.name, sizeof(p.name), stdin) != NULL) {
        size_t len = strlen(p.name);
        if (len > 0 && p.name[len - 1] == '\n') {
            p.name[len - 1] = '\0';
        }
    }

    p.priority = readInt("Priority: ");

    return p;
}
