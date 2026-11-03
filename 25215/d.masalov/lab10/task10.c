#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int *status;

    if (argc < 2) {
        fprintf(stderr, "argv cannot be empty\n", argv[0]);
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(1);
    }

    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status)) {
        printf("Command ends with %d code\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Command was terminate with signal %d\n", WTERMSIG(status));
    } else {
        printf("Unknown return method\n", status);
    }

    return 0;
}