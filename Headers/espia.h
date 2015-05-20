#ifndef ESPIA_H_
#define ESPIA_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "proceso.h"
#include "segmento.h"
#include "constantes.h"
#include "segmentoDatos.h"

#define BORDE                 "+-------------------------------------+\n"
#define TITULO_DATOS          "|        Segmento Compartido          |\n"
#define TITULO_WRITER         "|           Estado writers            |\n"
#define TITULO_READER         "|           Estado readers            |\n"
#define TITULO_READER_EGOISTA "|       Estado readers Egoistas       |\n"

// Registra un cambio en el segmento en el log
//aun no implementado
//void registrar(int,int,char*,proceso*);
void registrar(int,int,int,char*,char*,char*);

// Imprime un segmento a partir de su llave
void printEstado();

#endif // ESPIA_H_