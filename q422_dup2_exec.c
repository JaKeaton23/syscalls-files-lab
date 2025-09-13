#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "usage: %s output_file\n", argv[0]);
        exit(1);
    }
    int newfd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
    if (newfd < 0){ perror(argv[1]); exit(1); }

    printf("writing output of the command ls to %s\n", argv[1]);
    dup2(newfd, 1);
    close(newfd);

    char *cmd[] = { "/bin/ls", "-al", "/", NULL };
    execv(cmd[0], cmd);
    perror(cmd[0]);  // only if exec fails
    exit(1);
}
