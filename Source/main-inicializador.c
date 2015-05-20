#include "../Headers/segmento.h"

void main(int argc, char *argv[])
{
	//Se esperan un parámetro para determinar la cantidad de líneas de memoria compartida.
	if(argc == 2) {
		// Inicializamos las variables y el segmento compartido
		int cantidadLineas = atoi(argv[1]);
		init(cantidadLineas);
	}
	else
	{
		printf("No indicó la cantidad de líneas que desea va a tener la memoria compartida\n");
	}
}
