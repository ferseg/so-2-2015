#include "../Headers/finalizador.h"


void liberar_memoria()
{
	int shmid;
    key_t key;
    char *shm;
    
    /*
    * Obtenemos el segmento llamado
    * "2015", creado por el inicializador.
    */
    key = LLAVE_SEGMENTO;
    
    int num_lineas = cantidad_lineas();
    int tamanio_mem = num_lineas*30 + 1;
    
    if ((shmid = shmget(key, tamanio_mem, 0666)) < 0) {
    	printf("Error creando el segmento para finalizarlo\n");
		perror(ERROR_CREACION);
		return;
	}

	/*
    * Se localiza el segmento.
    */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
    	printf("Error localizando el segmento para finalizarlo\n");
        perror(ERROR_LOCALIZACION);
        return;
    }
 
    printf("%s\n",shm);

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
