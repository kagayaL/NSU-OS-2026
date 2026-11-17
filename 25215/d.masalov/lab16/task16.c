#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct termios tty, savetty;
    char answer;

    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        return 1;
    }

    savetty = tty;

    tty.c_lflag &= ICANON;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        return 1;
    }

    printf("Question(y/n): ");
    fflush(stdout);

    ssize_t n = read(STDIN_FILENO, &answer, 1);
    if (n < -1) {
        perror("read");
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &savetty);
        return 1;
    }

    printf("Your answer - %c\n", answer);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &savetty);

}