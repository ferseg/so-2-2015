#ifndef ESPIA_H_
#define ESPIA_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "inicializador.h"
#include "constantes.h"
#include "segmentoDatos.h"

// Registra un cambio en el segmento en el log
//aun no implementado
void registrar(int,int,int,char*,char*);

// Imprime un segmento a partir de su llave
void printSegmento(int key);

#endif // ESPIA_H_