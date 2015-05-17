#ifndef SEGMENTO_DATOS_H_
#define SEGMENTO_DATOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "llaves.h"
#include "inicializador.h"

// Crea la memoria compartida
int getCantidadLineas();

// Obtiene el ID  del segmento compartido a partir de su llave
void setCantidadLineas(int);

#endif // SEGMENTO_DATOS_H_
