# Copyrigth © 2015, All rights reserved.
# makefile
# Author: kenneth Madrigal Soto

#Archivos
INIT_FILES = Source/main-inicializador.c Source/inicializador.c Source/segmentoDatos.c
WRITER_FILES = Source/main-writer.c Source/writer.c
FINAL_FILES = Source/main-finalizador.c Source/inicializador.c Source/segmentoDatos.c

#Librerías
CFLAGS = -w -I ../Hearders #-Wall
CC = gcc
LIBS = -lpthread -lm

#Rutas
INIT_NAME = bin/inicializador
FINAL_NAME = bin/finalizador
WRITER_NAME = bin/writer

inicializador:
	$(CC) $(CFLAGS) $(INIT_FILES) -o $(INIT_NAME) $(LIBS)

writer:
	$(CC) $(CFLAGS) $(WRITER_FILES) -o $(WRITER_NAME) $(LIBS)

finalizador:
	$(CC) $(CFLAGS) $(FINAL_FILES) -o $(FINAL_NAME) $(LIBS)