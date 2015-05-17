#ifndef INICIALIZADOR_H_
#define INICIALIZADOR_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "llaves.h"
#include "segmentoDatos.h"

#define TAMANIO_LINEAS 30
#define ERROR_CREACION "shmget"
#define ERROR_LOCALIZACION "shmat"

// Crea la memoria compartida
int crearMemoria(int,int);

//Libera la memoria compartida a partir de su llave
void liberar_memoria(int key);

// Obtiene el ID  del segmento compartido a partir de su llave
int getMemID(int);

// Obtiene un puntero al inicio del segmento compartido
// a partir de su shmid
char *getMem(int);

// Inicializa el ambiente para que los demás procesos
// encuentren todo listo para ejecutarse
// recibe la cantidad de lineas que tendrá el segmento
void init(int);

// Finaliza todos los procesos
void finalizar();

#endif // INICIALIZADOR_H_
