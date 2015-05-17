#ifndef INICIALIZADOR_H_
#define INICIALIZADOR_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "llaves.h"

#define TAMANIO_LINEAS 30
#define ARCHIVO "cantidadLineas.txt"
#define ERROR_CREACION "shmget"
#define ERROR_LOCALIZACION "shmat"

// Crea la memoria compartida
int crearMemoria(int);

int getMemId();

#endif // INICIALIZADOR_H_
