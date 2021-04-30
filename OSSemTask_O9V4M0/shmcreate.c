#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMKEY 67L
#define KEY 41L
#define PERM 00666

int main()
{
    int shmid;		// osztott mem azonosito
    key_t key;		// kulcs a shmem-hez
    int size=512;		// osztott szegmens meret byte-ban
    int shmflg;		// flag a jellemzokhoz

    struct kiolv {
	    int  hossz;
	    char szoveg[512-sizeof(int)]; // az egesz merete 512, ezert a hossz valtozot levonjuk a tombbol
    } *segm;
    key = SHMKEY;

    //Megnezzuk, van-e mar SHMKEY kulcsu es "size" meretu szegmens.
    shmflg = 0;
    if ((shmid=shmget(key, size, shmflg)) < 0) {
       printf("Nincs meg szegmens! Csinaljunk egyet!\n");
       shmflg = 00666 | IPC_CREAT;
       if ((shmid=shmget(key, size, shmflg)) < 0) {
          perror("Az shmget() system-call sikertelen!\n");
          exit(-1);
       }
    } else {
    printf("Van mar ilyen shm szegmens!\n");
    exit(-1);
    }

    printf("\nAz shm szegmens azonositoja %d! \n", shmid);
    shmflg = 00666 | SHM_RND;	// RND az igazitashoz
    segm = (struct kiolv *)shmat(shmid, NULL, shmflg);
    // Itt a NULL azt jelenti, hogy az OS-re bizom, hogy milyen cimtartomanyt hasznaljon.

    if (segm == (void *)-1) {
	    perror("Sikertelen attach!\n");
	    exit(-1);
    }
    int id; // A szemafor azonositoja

    if ((id = semget(KEY, 1, 0)) < 0) { // Meg nem letezik.
	    if ((id = semget(KEY, 1, PERM | IPC_CREAT)) < 0) {
	     	perror(" A szemafor nem nyithato meg. ");
		    exit(-1);
	    }
    }else{
	    perror(" Mar letezik a szemafor. ");
	    exit(0);
    }

    if (semctl(id, 0, SETVAL, 1) < 0) {
	    perror(" Nem lehetett inicializalni. ");
    } else {
	    puts(" Kesz es inicializalt a szemafor!");
    }

    struct sembuf up[1]  =  {0,  1, SEM_UNDO};
    struct sembuf down[1] = {0, -1, SEM_UNDO};

    semop(id, down, 1);   // A belepesi szakasz.
    strcpy(segm->szoveg,"Juhász Marcell Tibor O9V4M0");

    sleep(5);
    semop(id, up, 1);    // Ez a kilepesi szakasz. 
    puts(" Beiras sikeres volt! ");

    if (semctl(id, 0, IPC_RMID, 0) < 0) {
	    perror(" Nem sikerult torolni.");
	    exit(-1);
    }
    puts(" A szemafort megszuntettuk. \n");
    shmdt(segm);
    return 0;

}
