#include "../Headers/proceso.h"

int main()
{
	char term1,term2,term3;
	int cantidadReaders,tiempoLectura,tiempoDescanso;

	//Se esperan un parámetro para determinar la cantidad readers.
	printf("Ingrese la cantidad de readers: ");
	if(scanf("%d%c", &cantidadReaders,&term1) != 2 || term1 != '\n'){
		printf(ERROR_PARAMETRO);
		return;
	}

	//Se esperan un parámetro para determinar el tiempo de lectura.
	printf("Ingrese el tiempo de lectura: ");
	if(scanf("%d%c", &tiempoLectura,&term2) != 2 || term2 != '\n'){
		printf(ERROR_PARAMETRO);
		return;
	}
	
	//Se esperan un parámetro para determinar el tiempo de descanso.
	printf("Ingrese el tiempo de descanso: ");
	if(scanf("%d%c", &tiempoDescanso,&term3) != 2 || term3 != '\n'){
		printf(ERROR_PARAMETRO);
		return;
	}

	if((cantidadReaders < 1) || (tiempoLectura < 1) || (tiempoDescanso < 1)){
		//Inicializamos los readers
		printf(ERROR_NUMERO);
		return;
		}
	initProcesos(cantidadReaders,tiempoLectura,tiempoDescanso,LLAVE_SEGMENTO_READERS,TIPO_READER);
}