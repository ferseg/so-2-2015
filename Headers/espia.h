#ifndef ESPIA_H_
#define ESPIA_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "proceso.h"
#include "segmento.h"
#include "utilities.h"
#include "constantes.h"
#include "segmentoDatos.h"

#define BORDE                 "+-------------------------------------+\n"
#define TITULO_DATOS          "|        Segmento Compartido          |\n"
#define TITULO_WRITER         "|           Estado writers            |\n"
#define TITULO_READER         "|           Estado readers            |\n"
#define TITULO_READER_EGOISTA "|       Estado readers Egoistas       |\n"

// Guarda un mensaje en el log
void registrar(proceso*);

// Registra un cambio en el segmento en el log
//aun no implementado
void actualizar(int,char*,proceso*);

// Imprime un segmento a partir de su llave
void printEstado();

#endif // ESPIA_H_