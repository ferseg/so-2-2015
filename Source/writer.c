#include "../Headers/writer.h"


// Retorna un nuevo writer
// recibe id, tiempo de escritura, tiempo de descanso
writer* newWriter(int pId, int pEscritura,int pDescanso){
	writer *newWriter = malloc(sizeof(writer));
  	newWriter->id = pId;
  	newWriter->descanso = pEscritura;
  	newWriter->escritura = pDescanso;
	return newWriter;
}

void ejecutarWriter(writer *writerActual){
	printf("%d %d\n",writerActual->id,writerActual->escritura);
	sleep(writerActual->escritura);
	printf("%d %d\n",writerActual->id,writerActual->descanso);
	sleep(writerActual->descanso);
	printf("fin\n");
}

//Inicializa los writers, recibe cantidad de writers, tiempo de escritura
// y tiempo de descanso
void initWriters(int cantidadWriters,int tiempoEscritura,int tiempoDescanso){
	int i;
	pthread_t writerThread[cantidadWriters];
	for(i=1;i<=cantidadWriters;i++){
		writer *nWriter = newWriter(i,tiempoEscritura,tiempoDescanso);
		pthread_create(&writerThread[i-1], NULL, ejecutarWriter, nWriter);
	}
	for(i=0;i<cantidadWriters;i++){
		pthread_join(writerThread[i], NULL);
	}
}
