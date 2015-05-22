#include "../Headers/proceso.h"

int main()
{
	int cantidadReaders,tiempoEscritura,tiempoDescanso;

	//Se esperan un parámetro para determinar la cantidad writers.
	printf("Ingrese la cantidad de readers egoistas: ");
	scanf("%d", &cantidadReaders);

	//Se esperan un parámetro para determinar el tiempo de escritura.
	printf("Ingrese el tiempo de escritura: ");
	scanf("%d", &tiempoEscritura);
	
	//Se esperan un parámetro para determinar el tiempo de descanso.
	printf("Ingrese el tiempo de descanso: ");
	scanf("%d", &tiempoDescanso);

	if((cantidadReaders>0) && (tiempoEscritura>0) && (tiempoDescanso>0)){
		//Inicializamos los readers egoistas
		initProcesos(cantidadReaders,tiempoEscritura,tiempoDescanso,LLAVE_SEGMENTO_READERS_EGOISTAS,TIPO_READER_EGOISTA);
		}
	else{
		printf("Favor ingresar valores mayores a cero.\n");
	}
}