#include "../Headers/finalizador.h"


void liberar_memoria(int key)
{    
    /*
    * Obtenemos el segmento 
    * creado por el inicializador.
    */
    int shmid = getMemID(key);
    char *shm = getMem(shmid);
    
    //ver segmento
    printf("%s",shm);

 	/*
 	* Se quita el segmento del espacio de datos en memoria
 	*/   
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        return;
    }

	/*
 	* Se libera el segmento de memoria
 	*/   
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return;
    }
}
