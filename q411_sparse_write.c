#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void){
    char buffer[200];
    memset(buffer, 'a', sizeof buffer);
    int fd = open("test.txt", O_CREAT|O_RDWR, 0644);
    write(fd, buffer, 200);
    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, 100);
    lseek(fd, 500, SEEK_CUR);     // creates a hole of zeros
    write(fd, buffer, 100);
    close(fd);
    return 0;
}
