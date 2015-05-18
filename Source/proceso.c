#include "../Headers/proceso.h"


// Retorna un nuevo writer
// recibe id, tiempo de escritura, tiempo de descanso
// Tipo 0 = Writer
// 		1 = Reader
//		2 = Reader egoista
proceso* newProcess(int pId, int pEscritura,int pDescanso,int pTipo){
	proceso *newProcess = malloc(sizeof(proceso));
  	newProcess->id = pId;
  	newProcess->escritura = pEscritura;
  	newProcess->descanso = pDescanso;
  	newProcess->tipo = pTipo;
  	newProcess->lineaActual = 0;
  	newProcess->estado = ESTADO_DESCANSO;
	return newProcess;
}

// Hilo encargado de la ejecución de los procesos
void ejecutarProceso(proceso *procesoActual){
	int shmid, contadorLinea;
	char *prefijo[TAMANIO_LINEAS];
	char *prefijoLog[TAMANIO_LINEAS];
	char *segmentoDatos,*mensaje;
	int segmentoDatosID,punteroMensaje,punteroSegmento;
	char *tipoProceso[30];
	switch(procesoActual->tipo){
	    case TIPO_WRITER:
	    	sprintf(tipoProceso,"%s", WRITER);
  			sprintf(prefijo,"1|%s|%3d",WRITER,procesoActual->id);
  			sprintf(prefijoLog,"%s|%3d",WRITER,procesoActual->id);
  			segmentoDatosID = getMemID(LLAVE_SEGMENTO_WRITERS,NULL);
			break;
		case TIPO_READER://////////////por implementar
			sprintf(tipoProceso, "%s", READER);
			sprintf(prefijo,"1|%s|%3d",READER,procesoActual->id);
	 		sprintf(prefijoLog,"%s|%3d",READER,procesoActual->id);
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_READERS,NULL);
		    break;
	    case TIPO_READER_EGOISTA://por implementar
	    	sprintf(tipoProceso, "%s", READER_EGOISTA);
	    	sprintf(prefijo,"0|%s|%3d",READER_EGOISTA,procesoActual->id);
	    	sprintf(prefijoLog,"%s|%3d",READER_EGOISTA,procesoActual->id);
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_READERS_EGOISTAS,NULL);
	        break;
	    default:
	        break;
	}

	while(EXITO){
		if(shmid = getMemID(LLAVE_SEGMENTO,NULL)){
			switch(procesoActual->tipo){
			    case TIPO_WRITER:
					///////////////////////////////////////////////////////
					// region critica, falta sincronizar
					if(contadorLinea = escribir(prefijo)){
						// Tiempo de escritura
						procesoActual->lineaActual = contadorLinea;
						registrar(LLAVE_SEGMENTO_WRITERS,(procesoActual->id-1),contadorLinea,prefijoLog,ESTADO_ESCRITURA);
						procesoActual->estado = ESTADO_ESCRITURA;
						sleep(procesoActual->escritura);
						// Tiempo de descanso
						registrar(LLAVE_SEGMENTO_WRITERS,(procesoActual->id-1),procesoActual->lineaActual,prefijoLog,ESTADO_DESCANSO);
						procesoActual->estado = ESTADO_DESCANSO;
						sleep(procesoActual->descanso);
					}//////////////////////////////////////////////////////
					//Luego de dormir se bloquean y esperan el semáforo
					procesoActual->estado = ESTADO_BLOQUEADO;
					registrar(LLAVE_SEGMENTO_WRITERS,(procesoActual->id-1),procesoActual->lineaActual,prefijoLog,ESTADO_BLOQUEADO);
					break;
				case TIPO_READER://////////////por implementar

				    break;
			    case TIPO_READER_EGOISTA://por implementar
			    	
			        break;
			    default:
			        break;
			}
		}
		else{
			// Al no encontrar memoria compartida
			// el proceso muere.
			printf("El %s %d fue finalizado.\n",tipoProceso,procesoActual->id);////////////////////////////////////
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
		proceso *nProcess = newProcess(i,tiempoEscritura,tiempoDescanso,TIPO_WRITER);
		pthread_create(&writerThread[i-1], NULL, ejecutarProceso, nProcess);
	}
	for(i=0;i<cantidadWriters;i++){
		pthread_join(writerThread[i], NULL);
	}
}
