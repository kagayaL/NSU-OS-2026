#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) 
{
    pid_t pid = fork();
    
    //unluck
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    // if pid = 0, it is child process
    if (pid == 0) {
        execlp("cat", "cat", "longFile.txt", (char *)NULL);
        perror("execlp");
        exit(1);
    }

    
    printf("It is parent process. Child's PID  - %d\n", pid);
    return 0;
}
