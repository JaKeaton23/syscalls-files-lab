#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    int newfd;
    if ((newfd = open("output_file.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0)
        exit(1);
    printf("Luke, I am your...\n");   // terminal
    dup2(newfd, 1);                    // stdout -> file
    printf("father\n");                // goes to output_file.txt
    close(newfd);
    return 0;
}
