#include "../Headers/proceso.h"

int main()
{
	int cantidadReaders,tiempoLectura,tiempoDescanso;

	//Se esperan un parámetro para determinar la cantidad readers.
	printf("Ingrese la cantidad de readers: ");
	scanf("%d", &cantidadReaders);

	//Se esperan un parámetro para determinar el tiempo de lectura.
	printf("Ingrese el tiempo de lectura: ");
	scanf("%d", &tiempoLectura);
	
	//Se esperan un parámetro para determinar el tiempo de descanso.
	printf("Ingrese el tiempo de descanso: ");
	scanf("%d", &tiempoDescanso);

	//Inicializamos los readers
	initProcesos(cantidadReaders,tiempoLectura,tiempoDescanso,LLAVE_SEGMENTO_READERS,TIPO_READER);
}