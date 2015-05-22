#include "../Headers/segmentoDatos.h"

// Inicializa las variables globales del segmentos de datos
void newDatos(int pCantidadLineas){
    int segmentoID = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	datos *newData = getMem(segmentoID);
	newData->cantidadLineas = pCantidadLineas; 
	newData->lectura = 1;
	newData->lectores = 0;
	newData->cantidadReadersEgoistas = 0;
}

// Obtiene la cantidad de lineas del segmento
int getCantidadLineas(){
    int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	datos *shm = getMem(shmid);
	return shm->cantidadLineas;
}

// Guarda la cantidad de lineas del segmento
void setCantidadLineas(int cantidadLineas){
    int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
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

int getLectores(){
	int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	datos *shm = getMem(shmid);
	return shm->lectores;
}

int incLectores(){
	int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	datos *shm = getMem(shmid);
	return shm->lectores++;
}

int decLectores(){
	int shmid = getMemID(LLAVE_SEGMENTO_DATOS,NULL);
	datos *shm = getMem(shmid);
	return shm->lectores--;
}