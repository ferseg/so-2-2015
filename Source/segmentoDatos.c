#include "../Headers/segmentoDatos.h"


// Obtiene la cantidad de lineas del segmento
int getCantidadLineas(){
    int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	char *shm = malloc(sizeof(char)*2000);
	shm = getMem(shmid);
	return atoi(shm);
}

// Guarda la cantidad de lineas del segmento
void setCantidadLineas(int cantidadLineas){
    int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
    char *shm = getMem(shmid);
    sprintf(shm,"%d",cantidadLineas);
}
