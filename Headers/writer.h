#ifndef WRITER_H_
#define WRITER_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "llaves.h"
#include "inicializador.h"

//Inicializa los writers, recibe cantidad de writers, tiempo de escritura
// y tiempo de descanso
void initWriters(int,int,int);

#endif // WRITER_H_
