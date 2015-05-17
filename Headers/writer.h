#ifndef WRITER_H_
#define WRITER_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include "llaves.h"
#include "inicializador.h"

typedef struct writer 
{
    int id;
    int descanso;
    int escritura;
}writer;

// Retorna un nuevo writer
// recibe id, tiempo de escritura, tiempo de descanso
writer* newWriter(int,int,int);

// Inicializa los writers, recibe cantidad de writers, tiempo de escritura
// y tiempo de descanso
void initWriters(int,int,int);

// Hilo encargado de la ejecución del writer
void ejecutarWriter(writer*);

#endif // WRITER_H_
