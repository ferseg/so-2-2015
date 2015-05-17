#include "../Headers/writer.h"


void writer(int ID){
	printf("%d\n",ID);
}

//Inicializa los writers, recibe cantidad de writers, tiempo de escritura
// y tiempo de descanso
void initWriters(int cantidadWriters,int tiempoEscritura,int tiempoDescanso){
	int i;
	for(i=1;i<=cantidadWriters;i++){
		writer(i);
	}
}
