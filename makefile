# Copyrigth © 2015, All rights reserved.
# makefile
# Author: kenneth Madrigal Soto

#Archivos
INIT_FILES = Source/main-inicializador.c Source/inicializador.c Source/segmentoDatos.c Source/espia.c
WRITER_FILES = Source/main-writer.c Source/proceso.c Source/inicializador.c Source/segmentoDatos.c Source/espia.c
READER_E_FILES = Source/main-readerEgoista.c Source/proceso.c Source/inicializador.c Source/segmentoDatos.c Source/espia.c
FINAL_FILES = Source/main-finalizador.c Source/inicializador.c Source/segmentoDatos.c Source/espia.c

#Librerías
CFLAGS = -w -I ../Hearders #-Wall
CC = gcc
LIBS = -lpthread -lm

#Rutas
INIT_NAME = bin/inicializador
FINAL_NAME = bin/finalizador
WRITER_NAME = bin/writer
READER_E_NAME = bin/readerE

inicializador:
	$(CC) $(CFLAGS) $(INIT_FILES) -o $(INIT_NAME) $(LIBS)

writer:
	$(CC) $(CFLAGS) $(WRITER_FILES) -o $(WRITER_NAME) $(LIBS)

readerE:
	$(CC) $(CFLAGS) $(READER_E_FILES) -o $(READER_E_NAME) $(LIBS)

finalizador:
	$(CC) $(CFLAGS) $(FINAL_FILES) -o $(FINAL_NAME) $(LIBS)