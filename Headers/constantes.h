#ifndef LLAVES_H_
#define LLAVES_H_

#include "../Headers/utilities.h"

#define ARCHIVO "bitacora.txt"
#define SEM_NAME "Ken"
#define SEM_LOG_NAME "Log"
#define EXITO 1
#define FRACASO 0
#define LINEA_VACIA '_'
#define LINEA_LLENA '1'
#define TAMANIO_LINEAS 40
#define LLAVE_SEGMENTO 2015
#define LLAVE_SEGMENTO_DATOS 1000
#define LLAVE_SEGMENTO_WRITERS 1010
#define LLAVE_SEGMENTO_READERS 1020
#define LLAVE_SEGMENTO_READERS_EGOISTAS 1030

#define ESTADO_DESCANSO  "Dormido              "
#define ESTADO_BLOQUEADO "Bloqueado            "
#define ESTADO_LECTURA   "Leyendo              "
#define ESTADO_ESCRITURA "Escribiendo          "

#endif // LLAVES_H_
