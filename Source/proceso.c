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
	char *prefijo = malloc(sizeof(char)*50);
	char *prefijoLog = malloc(sizeof(char)*50);
    sem_t *mutex;
	mutex = sem_open(SEM_NAME,0,0644,1);
	clearString(&prefijo, 50);
	clearString(&prefijoLog, 50);

	char *segmentoDatos;
	int segmentoDatosID,punteroMensaje,punteroSegmento;
	char *tipoProceso = malloc(sizeof(char)*30);clearString(&tipoProceso, 30);
	switch(procesoActual->tipo){
	    case TIPO_WRITER:
	    	sprintf(tipoProceso,"%s", WRITER);
  			sprintf(prefijo,"1|%s|%3d",WRITER,procesoActual->id);
  			sprintf(prefijoLog,"%s|%3d",WRITER,procesoActual->id);
  			segmentoDatosID = getMemID(LLAVE_SEGMENTO_WRITERS,NULL);
			break;
		case TIPO_READER:
			sprintf(tipoProceso, "%s", READER);
			sprintf(prefijo,"1|%s|%3d",READER,procesoActual->id);
	 		sprintf(prefijoLog,"%s|%3d",READER,procesoActual->id);
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_READERS,NULL);
		    break;
	    case TIPO_READER_EGOISTA:
	    	sprintf(tipoProceso, "%s", READER_EGOISTA);
	    	sprintf(prefijoLog,"%s|%3d",READER_EGOISTA,procesoActual->id);
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_READERS_EGOISTAS,NULL);
	        break;
	    default:
	        break;
	}

	while(EXITO){
		// Inicializamos el semaforo
		sem_wait(mutex);
		if(shmid = getMemID(LLAVE_SEGMENTO,NULL)){
			switch(procesoActual->tipo){
			    case TIPO_WRITER:
					///////////////////////////////////////////////////////
					// region critica, falta sincronizar
					if(contadorLinea = escribir(prefijo)){
						// Tiempo de escritura
						procesoActual->lineaActual = contadorLinea;
						registrar(segmentoDatosID,(procesoActual->id)-1,contadorLinea,prefijoLog,ESTADO_ESCRITURA);
						procesoActual->estado = ESTADO_ESCRITURA;
						sleep(procesoActual->escritura);
						sem_post(mutex);
						// Tiempo de descanso
						registrar(segmentoDatosID,(procesoActual->id)-1,procesoActual->lineaActual,prefijoLog,ESTADO_DESCANSO);
						procesoActual->estado = ESTADO_DESCANSO;
						sleep(procesoActual->descanso);
					}
					else{
					 	sem_post(mutex);
					}
					//////////////////////////////////////////////////////
					//Luego de dormir se bloquean y esperan el semáforo
					procesoActual->estado = ESTADO_BLOQUEADO;
					registrar(segmentoDatosID,(procesoActual->id)-1,procesoActual->lineaActual,prefijoLog,ESTADO_BLOQUEADO);
					break;
				case TIPO_READER://////////////por implementar

				    break;
			    case TIPO_READER_EGOISTA://por implementar
			    	///////////////////////////////////////////////////////
					// region critica, falta sincronizar
					if(contadorLinea = borrar()){
						// Tiempo de escritura
						procesoActual->lineaActual = contadorLinea;
						registrar(segmentoDatosID,(procesoActual->id-1),contadorLinea,prefijoLog,ESTADO_LECTURA);
						procesoActual->estado = ESTADO_LECTURA;
						sleep(procesoActual->escritura);
						// Tiempo de descanso
						registrar(segmentoDatosID,(procesoActual->id-1),procesoActual->lineaActual,prefijoLog,ESTADO_DESCANSO);
						procesoActual->estado = ESTADO_DESCANSO;
						sleep(procesoActual->descanso);
					}//////////////////////////////////////////////////////
					//Luego de dormir se bloquean y esperan el semáforo
					procesoActual->estado = ESTADO_BLOQUEADO;
					registrar(segmentoDatosID,(procesoActual->id-1),procesoActual->lineaActual,prefijoLog,ESTADO_BLOQUEADO);
			        break;
			    default:
			        break;
			}
		}
		else{
			// Al no encontrar memoria compartida
			// el proceso muere.
			sem_post(mutex);
			sem_close(mutex);
			printf("El %s %d fue finalizado.\n",tipoProceso,procesoActual->id);////////////////////////////////////
		    pthread_exit(0);
			//falta escribir en bitácora
		}
	}
}

// Inicializa los writers, recibe cantidad de writers, tiempo de escritura,
// tiempo de descanso, la llave del segmento al que va a escribir y el tipo
// de proceso
void initProcesos(int cantidadProcesos,int tiempoEscritura,int tiempoDescanso,int llave,int tipo){
	int i;
	// Monitor de writers
	crearMemoria(llave,cantidadProcesos);
	pthread_t processThread[cantidadProcesos];
	for(i=1;i<=cantidadProcesos;i++){
		proceso *nProcess = newProcess(i,tiempoEscritura,tiempoDescanso,tipo);
		pthread_create(&processThread[i-1], NULL, ejecutarProceso, nProcess);
	}
	for(i=0;i<cantidadProcesos;i++){
		pthread_join(processThread[i], NULL);
	}
}
