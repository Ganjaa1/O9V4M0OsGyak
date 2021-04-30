#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 67L

int main()
{
	int shmid;		// osztott mem azonosito
	key_t key;		// kulcs a shmem-hez
	int size=512;		// osztott szegmens meret byte-ban
	int shmflg;		// flag a jellemzokhoz
	struct beolv {
		int  hossz;
		char szoveg[512-sizeof(int)]; // az egesz merete 512, ezert a hossz valtozot levonjuk a tombbol
	} *segm;		// Ezt a strukturat kepezzuk a szegmensre

	key = SHMKEY;

	shmflg = 0;	// Nincs IPC_CREAT, feltetelezzuk, az shmcreate.c keszitett osztott memoria szegmenst
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("Az shmget system-call sikertelen!\n");
	    exit(-1);
	}

    // Attach - rakapcsolodunk

	shmflg = 00666 | SHM_RND;	// RND az igazitashoz 
	segm = (struct beolv *)shmat(shmid, NULL, shmflg);
				// Itt a NULL azt jelenti, hogy az OS-re bizom, milyen cimtartomanyt hasznaljon. 
	if (segm == (void *)-1) {
		perror("Sikertelen attach!\n");
		exit(-1);
	}

    // Sikeres attach utan a "segm" cimen ott az osztott memoria. Ha van benne valami, kiiratom.

	if (strlen(segm->szoveg) > 0) 
		printf("\nSzegmens szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);
	int rtn = shmctl(shmid, IPC_RMID, NULL);
		printf("Szegmens torolve. Hibakod: %d\n", rtn);
		return 0;

}
