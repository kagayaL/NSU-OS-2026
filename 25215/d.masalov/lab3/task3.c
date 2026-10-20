#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    FILE* file;

    printf("Real id: %u\n", (unsigned)getuid());
    printf("Effective id: %u\n", (unsigned)geteuid());

    file = fopen("secretFile.txt", "r");
    if (file != NULL) {
        printf("File was opened\n");
        fclose(file);
    }
    else {
        perror("Cannot open file");
    }

    if (setuid(getuid()) == -1) {
        perror("setuid");
        return 1;
    }
    printf("\nUse setuid\n\n");

    printf("Real id: %u\n", (unsigned)getuid());
    printf("Effective id: %u\n", (unsigned)geteuid());

    file = fopen("secretFile.txt", "r");
    if (file != NULL) {
        printf("File was opened\n");
        fclose(file);
    }
    else {
        perror("Cannot open file");
    }

    return 0;
}