# Copyrigth © 2015, All rights reserved.
# makefile
# Author: kenneth Madrigal Soto

#Archivos
INIT_FILES = Source/main-inicializador.c Source/segmento.c Source/segmentoDatos.c Source/espia.c Source/utilities.c
WRITER_FILES = Source/main-writer.c Source/proceso.c Source/segmento.c Source/segmentoDatos.c Source/espia.c Source/utilities.c
READER_FILES = Source/main-reader.c Source/proceso.c Source/segmento.c Source/segmentoDatos.c Source/espia.c Source/utilities.c
READER_E_FILES = Source/main-readerEgoista.c Source/proceso.c Source/segmento.c Source/segmentoDatos.c Source/espia.c Source/utilities.c
SPY_FILES = Source/main-espia.c Source/segmento.c Source/segmentoDatos.c Source/espia.c Source/utilities.c
FINAL_FILES = Source/main-finalizador.c Source/segmento.c Source/segmentoDatos.c Source/espia.c Source/utilities.c

#Librerías
CFLAGS = -w -I ../Hearders #-Wall
CC = gcc
LIBS = -lpthread -lm

#Rutas
INIT_NAME = bin/inicializador
WRITER_NAME = bin/writer
READER_NAME = bin/reader
READER_E_NAME = bin/readerE
SPY_NAME = bin/espia
FINAL_NAME = bin/finalizador

inicializador:
	$(CC) $(CFLAGS) $(INIT_FILES) -o $(INIT_NAME) $(LIBS)

writer:
	$(CC) $(CFLAGS) $(WRITER_FILES) -o $(WRITER_NAME) $(LIBS)

reader:
	$(CC) $(CFLAGS) $(READER_FILES) -o $(READER_NAME) $(LIBS)

readerE:
	$(CC) $(CFLAGS) $(READER_E_FILES) -o $(READER_E_NAME) $(LIBS)

espia:
	$(CC) $(CFLAGS) $(SPY_FILES) -o $(SPY_NAME) $(LIBS)

finalizador:
	$(CC) $(CFLAGS) $(FINAL_FILES) -o $(FINAL_NAME) $(LIBS)