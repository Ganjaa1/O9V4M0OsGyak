#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATE = 1
int main (int argc, char *argv[]) {
        printf("Adjon meg egy parancsot: date, pwd, who ,whoami, w, uname \n");
        char valasz[20];
        scanf("%s", valasz);
        if (strcmp(valasz, "date") == 0) {
            system("time");
        }
        else if (strcmp(valasz, "who") == 0) {
            system("who");
        }else if (strcmp(valasz, "whoami") == 0) {
            system("whoami");
        }else if (strcmp(valasz, "w") == 0) {
            system("w");
        }else if (strcmp(valasz, "uname") == 0) {
            system("uname");
        }else{
            printf("Nincs ilyen választási lehetõség!");
        }
    return(0);
}
