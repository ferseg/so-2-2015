#ifndef INICIALIZADOR_H_
#define INICIALIZADOR_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <time.h>
#include "constantes.h"
#include "segmentoDatos.h"

#define ERROR_CREACION "shmget"
#define ERROR_LOCALIZACION "shmat"

#define MENSAJE_ERROR_WRITERS "El finalizador no encontró writers.\n"
#define MENSAJE_ERROR_READERS "El finalizador no encontró readers.\n"
#define MENSAJE_ERROR_READERS_EGOISTAS "El finalizador no encontró readers egoistas.\n"

#define MENSAJE_CREACION_EXITOSA "El ambiente se inicializaó correctamente.\n"
#define MENSAJE_CREACION_FALLIDA "No se pudo inicializar el ambiente, asegurese de finalizar corridas anteriores.\n"
#define MENSAJE_FINALIZACION_EXITOSA "Procesos finalizados correctamente.\n"
#define MENSAJE_FINALIZACION_FALLIDA "Se intentó finalizar la memoria, pero esta no ha sido inicializada.\n"

// Crea la memoria compartida
int crearMemoria(int,int);

//Libera la memoria compartida a partir de su llave
int liberarMemoria(int key);

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
// y escribe en ella el mensaje, retorna 1 si tuvo exito
// y 0 si todas las lineas estaban llenas
// el id debera venir en el formato 
// 1|tipo|id dl proceso
int escribir(char*);

// Retorna un char con la hora actual
char *getTime();

// Crea un mensaje valido para el segmento
// a partir de un id, el estado del proceso
// y la linea q modifico
char *crearMensaje(char*,char*,int);

#endif // INICIALIZADOR_H_
