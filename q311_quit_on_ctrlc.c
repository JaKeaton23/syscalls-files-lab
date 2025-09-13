#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

static void on_int(int sig){
    (void)sig;
    const char *msg = "Do you really want to quit [y/n]? ";
    char ch;
    write(1, msg, strlen(msg));
    if (read(0, &ch, 1) == 1) {
        if (ch == 'y' || ch == 'Y') _exit(0);
    }
    write(1, "\n", 1);
}

int main(void){
    struct sigaction sa = {0};
    sa.sa_handler = on_int;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    while (1) pause();
}
