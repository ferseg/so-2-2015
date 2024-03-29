#ifndef SEGMENTO_DATOS_H_
#define SEGMENTO_DATOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "segmento.h"
#include "constantes.h"

typedef struct datos{
	int cantidadLineas;
	int lectura;
	int lectores;
	int cantidadReadersEgoistas;
}datos;

void newDatos(int);

// Obtiene la cantidad de lineas del segmento
int getCantidadLineas();

// Guarda la cantidad de lineas del segmento
void setCantidadLineas(int);

//
int getLectura();

void setLectura(int);

//
int incReader();

int decReader();

//
int getLectores();

int incLectores();

int decLectores();

#endif // SEGMENTO_DATOS_H_
