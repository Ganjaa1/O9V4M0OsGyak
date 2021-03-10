#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(void) {
    int pid;
    int status;
    if ((pid == fork()) < 0)
        perror("fork error");
    else if (pid == 0)
        exit(7);
    if(wait(&status) != pid)
        perror("wait hiba");
    if(WIFEXITED(status))
        printf("Normális befejeződés!");
        return(0);
}
