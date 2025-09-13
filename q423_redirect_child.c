#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "usage: %s output_file\n", argv[0]);
        exit(1);
    }
    pid_t pid = fork();
    if (pid < 0){ perror("fork"); exit(1); }

    if (pid == 0){
        int newfd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
        if (newfd < 0){ perror(argv[1]); _exit(1); }
        if (dup2(newfd, 1) < 0){ perror("dup2"); _exit(1); }
        close(newfd);
        char *cmd[] = { "/bin/ls", "-al", "/", NULL };
        execv(cmd[0], cmd);
        perror(cmd[0]);
        _exit(1);
    }

    int status = 0;
    waitpid(pid, &status, 0);
    printf("all done\n");
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}
