#include "../Headers/writer.h"

int main()
{
	int cantidadWriters,tiempoEscritura,tiempoDescanso;

	//Se esperan un parámetro para determinar la cantidad writers.
	printf("Ingrese la cantidad de writers: ");
	scanf("%d", &cantidadWriters);

	//Se esperan un parámetro para determinar el tiempo de escritura.
	printf("Ingrese el tiempo de escritura: ");
	scanf("%d", &tiempoEscritura);
	
	//Se esperan un parámetro para determinar el tiempo de descanso.
	printf("Ingrese el tiempo de descanso: ");
	scanf("%d", &tiempoDescanso);

	//Inicializamos los writers
	initWriters(cantidadWriters,tiempoEscritura,tiempoDescanso);
}