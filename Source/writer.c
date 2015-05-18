#include "../Headers/writer.h"


// Retorna un nuevo writer
// recibe id, tiempo de escritura, tiempo de descanso
writer* newWriter(int pId, int pEscritura,int pDescanso){
	writer *newWriter = malloc(sizeof(writer));
  	newWriter->id = pId;
  	newWriter->escritura = pEscritura;
  	newWriter->descanso = pDescanso;
  	newWriter->estado = ESTADO_DESCANSO;
	return newWriter;
}

// Hilo encargado de la ejecución del writer
void ejecutarWriter(writer *writerActual){
	int shmid;
	char *id[TAMANIO_LINEAS];
	sprintf(id,"1|writer|%3d",writerActual->id);

	int segmentoDatosID,punteroMensaje,punteroSegmento;
    segmentoDatosID = getMemID(LLAVE_SEGMENTO_WRITERS,NULL);
	char *segmentoDatos,*mensaje;

	while(EXITO){
		if(shmid = getMemID(LLAVE_SEGMENTO,NULL)){
			///////////////////////////////////////////////////////
			// region critica, falta sincronizar
			if(escribir(id)){
				// Tiempo de escritura
				registrar(LLAVE_SEGMENTO_WRITERS,(writerActual->id-1),0,id,ESTADO_ESCRITURA);
				writerActual->estado = ESTADO_ESCRITURA;
				sleep(writerActual->escritura);
			}//////////////////////////////////////////////////////
			// Tiempo de descanso
			registrar(LLAVE_SEGMENTO_WRITERS,(writerActual->id-1),0,id,ESTADO_DESCANSO);
			writerActual->estado = ESTADO_DESCANSO;
			sleep(writerActual->descanso);
		}
		else{
			// Al no encontrar memoria compartida
			// el proceso muere.
			printf("El writer %d fue finalizado.\n",writerActual->id);
			return;//falta escribir en bitácora
		}
	}
}

//Inicializa los writers, recibe cantidad de writers, tiempo de escritura
// y tiempo de descanso
void initWriters(int cantidadWriters,int tiempoEscritura,int tiempoDescanso){
	int i;
	// Monitor de writers
	crearMemoria(LLAVE_SEGMENTO_WRITERS,cantidadWriters);
	pthread_t writerThread[cantidadWriters];
	for(i=1;i<=cantidadWriters;i++){
		writer *nWriter = newWriter(i,tiempoEscritura,tiempoDescanso);
		pthread_create(&writerThread[i-1], NULL, ejecutarWriter, nWriter);
	}
	for(i=0;i<cantidadWriters;i++){
		pthread_join(writerThread[i], NULL);
	}
}
