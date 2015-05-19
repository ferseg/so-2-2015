#ifndef WRITER_H_
#define WRITER_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include "constantes.h"
#include "inicializador.h"

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
}proceso;

// Retorna un nuevo writer
// recibe id, tiempo de escritura, tiempo de descanso
// Tipo 0 = Writer
// 		1 = Reader
//		2 = Reader egoista
proceso* newProcess(int,int,int,int);

// Inicializa los writers, recibe cantidad de writers, tiempo de escritura,
// tiempo de descanso, la llave del segmento al que va a escribir y el tipo
// de proceso
void initProcess(int,int,int,int,int);

// Hilo encargado de la ejecución del writer
void ejecutarProceso(proceso*);

#endif // WRITER_H_
