/**
* Copyrigth © 2015, All rights reserved.
* fileManager.h
* Author: Fernando Segovia Salgado
*/
#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include "segmento.h"
#include "constantes.h"
#include "segmentoDatos.h"

int getRandomNumber(int,int);

void clearString(char*, int);

void guardarBuffer(char*,char*,int,int);

FILE* openFile(char *filename, char *options);

void getNextLine(FILE *file,char *singleLine);

void writeInFile(FILE *file, char *message);

void closeFile(FILE *file);


#endif // UTILITIES_H_