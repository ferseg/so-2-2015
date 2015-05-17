# Copyrigth © 2015, All rights reserved.
# makefile
# Author: kenneth Madrigal Soto
INIT_FILES = Source/main-inicializador.c Source/inicializador.c Source/segmentoDatos.c
FINAL_FILES = Source/main-finalizador.c Source/finalizador.c Source/inicializador.c Source/segmentoDatos.c
CFLAGS = -w -I ../Hearders #-Wall
CC = gcc
INIT_NAME = bin/inicializador
FINAL_NAME = bin/finalizador
LIBS = -lpthread -lm

inicializador:
	$(CC) $(CFLAGS) $(INIT_FILES) -o $(INIT_NAME) $(LIBS)

finalizador:
	$(CC) $(CFLAGS) $(FINAL_FILES) -o $(FINAL_NAME) $(LIBS)