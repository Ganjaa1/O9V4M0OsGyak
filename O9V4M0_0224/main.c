#include <stdio.h>
#include <stdlib.h>

int main()
{
    char kiiras[] = "Juh�sz Marcell Tibor, Programtervez� Informatikus, O9V4M0, OsGyak3, 02.24,";
    FILE * fPtr;
    fPtr = fopen("C:\\Users\\juhas\\Desktop\\programoz�s\\juhasz.txt", "w");
    if(fPtr == NULL)
    {
        printf("Nem lehet megnyitni.");
        exit(EXIT_FAILURE);
    }
    fputs(kiiras,fPtr);
    fclose(fPtr);
    return 0;
}
