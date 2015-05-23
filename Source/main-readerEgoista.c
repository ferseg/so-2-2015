#include "../Headers/proceso.h"

int main()
{
	char term1,term2,term3;
	int cantidadReaders,tiempoEscritura,tiempoDescanso;

	//Se esperan un parámetro para determinar la cantidad writers.
	printf("Ingrese la cantidad de readers egoistas: ");
	if(scanf("%d%c", &cantidadReaders, &term1) != 2 || term1 != '\n'){
		printf(ERROR_PARAMETRO);
		return;
		}

	//Se esperan un parámetro para determinar el tiempo de escritura.
	printf("Ingrese el tiempo de escritura: ");
	if(scanf("%d%c", &tiempoEscritura, &term2) != 2 || term2 != '\n'){
		printf(ERROR_PARAMETRO);
		return;
	}
	
	//Se esperan un parámetro para determinar el tiempo de descanso.
	printf("Ingrese el tiempo de descanso: ");
	if(scanf("%d%c", &tiempoDescanso, &term3) != 2 || term3 != '\n'){
		printf(ERROR_PARAMETRO);
		return;
	}

	if((cantidadReaders < 1) || (tiempoEscritura < 1) || (tiempoDescanso < 1)){
		printf(ERROR_NUMERO);
		return;
		}
	//Inicializamos los readers egoistas
	initProcesos(cantidadReaders,tiempoEscritura,tiempoDescanso,LLAVE_SEGMENTO_READERS_EGOISTAS,TIPO_READER_EGOISTA);
}