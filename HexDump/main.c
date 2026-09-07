#include <stdio.h>
#include <ctype.h>

int main(void)
{
    FILE *file = fopen("example.txt", "rb");

    if (file == NULL) {
        printf("Couldn't open file\n");
        return 1;
    }

    unsigned char byte;
    unsigned char buffer[16];        //Buffer that stores the bytes until it reaches 16
    size_t buffer_index = 0;
    size_t offset = 0;               //Each offset represents a byte

    while (fread(&byte, sizeof(byte), 1, file) == 1) {
        buffer[buffer_index] = byte;
        buffer_index++;
        //When it reaches 16 bytes it prints everything that has been stored so far
        if (buffer_index == 16) {
            printf("%08zX  ", offset - 15);
            // Prints 16 bytes
            for (size_t i = 0; i < 16; i++) {
                printf("%02X ", buffer[i]);
            }

            // Prints the ASCII translation
            printf(" |");

            for (size_t i = 0; i < 16; i++) {
                if (isprint(buffer[i])) {
                    printf("%c", buffer[i]);
                } else {
                    printf(".");
                }
            }

            printf("|\n");

            // Resets the buffer index
            buffer_index = 0;
        }

        offset++;
    }
    //We only print the buffer if it is = to 16 bytes
    //however if there are extra elements we have to make sure that they get printed as well
    if (buffer_index > 0) {

        for (size_t i = 0; i < buffer_index; i++) {
            printf("%02X ", buffer[i]);
        }
        printf(" |");
        for (size_t i = 0; i < buffer_index; i++) {
            if (isprint(buffer[i])) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }
        printf("|\n");
    }

    fclose(file);

    return 0;
}
