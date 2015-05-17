#include "../Headers/inicializador.h"

void main(int argc, char *argv[])
{
	//Se esperan un parámetro para determinar la cantidad de líneas de memoria compartida.
	if(argc == 2) {
		// Comentario para github
		int cantidadLineas = atoi(argv[1]);
		crearMemoria(cantidadLineas);
	}
	else
	{
		printf("No indicó la cantidad de líneas que desea va a tener la memoria compartida\n");
	}
}
