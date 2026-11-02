#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) 
{
    pid_t pid = fork();
    //неудача
    if (pid == -1) {
        perror("fork error")
        return 1;
    }
    // если pid = 0, то это дочерний процесс
    if (pid == 0) {
        execlp("cat", "cat", "longfile.txt", (char *)NULL);
        perror("execlp");
        _exit(1);
    }

    printf("Это родительский процесс. PID дочернего - %d\n", pid);
}