#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "segmento.h"
#include "constantes.h"
#include "segmentoDatos.h"

int getRandomNumber(int,int);

void clearString(char*, int);

#endif // UTILS_H_