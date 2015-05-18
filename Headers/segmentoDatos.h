#ifndef SEGMENTO_DATOS_H_
#define SEGMENTO_DATOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "constantes.h"
#include "inicializador.h"

// Obtiene la cantidad de lineas del segmento
int getCantidadLineas();

// Guarda la cantidad de lineas del segmento
void setCantidadLineas(int);

#endif // SEGMENTO_DATOS_H_
