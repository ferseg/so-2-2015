#ifndef SEGMENTO_H_
#define SEGMENTO_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "proceso.h"
#include "constantes.h"
#include "segmentoDatos.h"

#define ERROR_CREACION "shmget"
#define ERROR_LOCALIZACION "shmat"

#define MENSAJE_ERROR_WRITERS "El finalizador no encontró writers.\n"
#define MENSAJE_ERROR_READERS "El finalizador no encontró readers.\n"
#define MENSAJE_ERROR_READERS_EGOISTAS "El finalizador no encontró readers egoistas.\n"

#define MENSAJE_CREACION_EXITOSA "El ambiente se inicializó correctamente.\n"
#define MENSAJE_CREACION_FALLIDA "No se pudo inicializar el ambiente, asegurese de finalizar corridas anteriores.\n"
#define MENSAJE_FINALIZACION_EXITOSA "Procesos finalizados correctamente.\n"
#define MENSAJE_FINALIZACION_FALLIDA "Se intentó finalizar la memoria, pero esta no ha sido inicializada.\n"

// Crea la memoria compartida
int crearMemoria(int,int);

//Libera la memoria compartida a partir de su llave
int liberarMemoria(int);

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

// Encuentra la siguiente linea vacía en el segmento
// y escribe en ella el mensaje
// retorna 0 si todas las lineas estaban llenas y en caso contrario
// el retorna el numero de la linea modificada.
// recibe un prefijo, el tamaño de la memoria y el segmento 
// compartido
int escribir(char*,int,char*);

// Escoje aleatoriamente una linea del segmento
// y si está llena la borra. Retorna 0 si 
// no borró nada en el segmento y el numero
// de linea que borró en caso contrario.
// Recibe el tamaño de la memiria y el
// segmento compartido
int borrar(int,char*);

// Lee una linea del segmento compartido
int leer(int,char*,struct proceso*);

// Retorna un char con la hora actual
char *getTime();

// Crea un mensaje valido para el segmento
// a partir de un id, el estado del proceso
// y la linea q modifico
char *crearMensaje(char*,char*,int);

#endif // SEGMENTO_H_
