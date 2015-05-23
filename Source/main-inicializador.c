#include "../Headers/segmento.h"

void main(int argc, char *argv[])
{
	int cantidadLineas;
	char terminacion;
	// Inicializamos las variables y el segmento compartido
	printf("Ingrese la cantidad de lineas que tendra el segmento compartido: ");
	if(scanf("%d%c", &cantidadLineas, &terminacion) != 2 || terminacion != '\n'){
		printf(ERROR_PARAMETRO);
		return;
	}
	if(cantidadLineas < 1){
		printf(ERROR_NUMERO);
		return;
	}
	init(cantidadLineas);
}
