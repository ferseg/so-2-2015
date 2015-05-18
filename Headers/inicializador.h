#ifndef INICIALIZADOR_H_
#define INICIALIZADOR_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <time.h>
#include "llaves.h"
#include "segmentoDatos.h"

#define EXITO 1
#define FRACASO 0
#define ERROR_CREACION "shmget"
#define ERROR_LOCALIZACION "shmat"
#define MENSAJE_CREACION_EXITOSA "El ambiente se inicializaó correctamente.\n"
#define MENSAJE_CREACION_FALLIDA "No se pudo inicializar el ambiente, asegurese de finalizar corridas anteriores.\n"
#define MENSAJE_FINALIZACION_EXITOSA "Procesos finalizados correctamente.\n"
#define MENSAJE_FINALIZACION_FALLIDA "Se intentó finalizar la memoria, pero esta no ha sido inicializada.\n"

// Crea la memoria compartida
int crearMemoria(int,int);

//Libera la memoria compartida a partir de su llave
int liberar_memoria(int key);

// Obtiene el ID  del segmento compartido a partir de su llave y su tamanio
int getMemID(int,int);

// Obtiene un puntero al inicio del segmento compartido
// a partir de su shmid
char *getMem(int);

// Inicializa el ambiente para que los demás procesos
// encuentren todo listo para ejecutarse
// recibe la cantidad de lineas que tendrá el segmento
void init(int);

// Finaliza todos los procesos
void finalizar();

int escribir(char*);

#endif // INICIALIZADOR_H_
