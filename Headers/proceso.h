#ifndef PROCESO_H_
#define PROCESO_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include "segmento.h"
#include "constantes.h"

#define WRITER "writer "
#define READER "reader "
#define READER_EGOISTA "readerE"

#define TIPO_WRITER 0
#define TIPO_READER 1
#define TIPO_READER_EGOISTA 2


typedef struct proceso
{
    int id;
    int descanso;
    int escritura;
    int tipo;
    int lineaActual;
    char *estado;
    char *segmentoDatos;
}proceso;

// Retorna un nuevo writer
// recibe id, tiempo de escritura, tiempo de descanso
// Tipo 0 = Writer
// 		1 = Reader
//		2 = Reader egoista
proceso* newProcess(int,int,int,int,char*);

// Inicializa los writers, recibe cantidad de writers, tiempo de escritura,
// tiempo de descanso, la llave del segmento al que va a escribir y el tipo
// de proceso
void initProcess(int,int,int,int,int);

// Hilo encargado de la ejecución del writer
void ejecutarProceso(proceso*);

#endif // PROCESO_H_
