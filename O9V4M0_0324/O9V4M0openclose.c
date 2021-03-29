#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd,ret;
    char buf[32];
    buf[0] = 0;
    //O_RDONLY - O_RDWR - O_WRONLY -- ezekbol valamelyik kotelezo
    //O_APPEND - minden write utan a vegere pozicional
    //O_CREAT - letrehozas
    //O_TRUNC
    fd = open("O9V4M0.txt",O_RDWR);
    if(fd == -1){
        perror("open() hiba!");
        exit(-1);
    }
    ret = read(fd,buf,32); // ret: mennyit sikerult beolvasni
    printf("read() olvasott %d byteot, ami a következo: %s",ret,buf);
    strcpy(buf,"O9V4M0");

    ret = lseek(fd,0,SEEK_SET); // SEEK_CUR, SEEK_END - ret:hova allt be tenylegesen
    printf("\nlseek() mondja: %d\n",ret);

    ret= write(fd,buf,6); //ret: mennyit irt ki valojaban
    printf("write() mondja: %d\n",ret);
    close(fd);
}
