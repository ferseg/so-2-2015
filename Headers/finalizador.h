#ifndef FINALIZADOR_H_
#define FINALIZADOR_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

#define LLAVE_SEGMENTO 2015
#define ARCHIVO "cantidadLineas.txt"
#define ERROR_CREACION "shmget"
#define ERROR_LOCALIZACION "shmat"

//Libera la memoria compartida
void liberar_memoria();
//Devuelve la cantidad de líneas que posee la memoria compartida
int cantidad_lineas();


#endif // FINALIZADOR_H_
