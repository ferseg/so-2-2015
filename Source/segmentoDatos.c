#include "../Headers/segmentoDatos.h"

// Inicializa las variables globales del segmentos de datos
datos* newDatos(int pCantidadLineas){
	datos *newData = malloc(sizeof(datos));
	newData->cantidadLineas = pCantidadLineas;
	newData->lectura = 1;
	newData->cantidadReadersEgoistas = 0;
	return newData;
}

// Obtiene la cantidad de lineas del segmento
int getCantidadLineas(){
    int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	// char *shm = malloc(sizeof(char)*2000);
	// shm = getMem(shmid);
	// return atoi(shm);
	datos *shm = getMem(shmid);
	return shm->cantidadLineas;
}

// Guarda la cantidad de lineas del segmento
void setCantidadLineas(int cantidadLineas){
    int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
    // char *shm = getMem(shmid);
    // sprintf(shm,"%d",cantidadLineas);
    datos *shm = getMem(shmid);
    shm->cantidadLineas = cantidadLineas;
}

int getLectura(){
	int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	datos *shm = getMem(shmid);
	return shm->lectura;
}

void setLectura(int pLectura){

    int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
    datos *shm = getMem(shmid);
    shm->lectura = pLectura;

}

int incReader(){
	int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	datos *shm = getMem(shmid);
	return shm->cantidadReadersEgoistas++;
}

int decReader(){
	int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	datos *shm = getMem(shmid);
	shm->cantidadReadersEgoistas = 0;
	return 0;
}