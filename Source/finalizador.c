#include "../Headers/finalizador.h"


void liberar_memoria()
{
	int shmid = getMemID();
    key_t key;
    char *shm;
    
    /*
    * Obtenemos el segmento llamado
    * "2015", creado por el inicializador.
    */
    key = LLAVE_SEGMENTO;
    
    int num_lineas = cantidad_lineas();

	/*
    * Se localiza el segmento.
    */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
    	printf("Error localizando el segmento para finalizarlo\n");
        perror(ERROR_LOCALIZACION);
        return;
    }
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


int cantidad_lineas() 
{
	FILE *fp;
	char buffer[2];

	fp = fopen(ARCHIVO, "r");
	fscanf(fp, "%s", buffer);
	fclose(fp);
	
	return atoi(buffer);
}
