#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int child;
    mkfifo("o9v4m0", S_IRUSR | S_IWUSR);
    child = fork();
    if(child  > 0){
        char s[1024];
        int fd;
        fd = open("o9v4m0", O_RDONLY);
        read(fd, s, sizeof(s));
        printf("%s",s);
        close(fd);
        unlink("o9v4m0");
    }else if(child == 0){
        int fd;
        fd = open("o9v4m0",O_WRONLY);
        wrtie(fd," JMT O9V4M0\n",12);
        close(fd);
    }
    return 0;
}
