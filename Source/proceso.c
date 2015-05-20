#include "../Headers/proceso.h"


// Retorna un nuevo writer
// recibe id, tiempo de escritura, tiempo de descanso
// Tipo 0 = Writer
// 		1 = Reader
//		2 = Reader egoista
proceso* newProcess(int pId, int pEscritura,int pDescanso,int pTipo,char *pSegmentoDatos){
	proceso *newProcess = malloc(sizeof(proceso));
  	newProcess->id = pId;
  	newProcess->escritura = pEscritura;
  	newProcess->descanso = pDescanso;
  	newProcess->tipo = pTipo;
  	newProcess->lineaActual = 0;
  	newProcess->estado = ESTADO_DESCANSO;
  	newProcess->segmentoDatos = pSegmentoDatos;
	return newProcess;
}

// Hilo encargado de la ejecución de los procesos
void ejecutarProceso(proceso *procesoActual){
	int shmid, llaveSegmento, contadorLinea, tipo;
	char *prefijo = (char*)malloc(TAMANIO_LINEAS);
	char *prefijoLog = (char*)malloc(TAMANIO_LINEAS);
	char *shm,*segmentoDatos;
    sem_t *mutex;
	mutex = sem_open(SEM_NAME,0,0644,1);

	int tamanioMem;
	char *tipoProceso = (char*)malloc(30);
	tipo = procesoActual->tipo;
	tamanioMem = getCantidadLineas() * TAMANIO_LINEAS;
	switch(procesoActual->tipo){
	    case TIPO_WRITER:
	    	sprintf(tipoProceso,"%s", WRITER);
  			sprintf(prefijo,"1|%s|%3d",WRITER,procesoActual->id);
  			sprintf(prefijoLog,"%s|%3d",WRITER,procesoActual->id);
  			llaveSegmento = LLAVE_SEGMENTO_WRITERS;
			break;
		case TIPO_READER:
			sprintf(tipoProceso, "%s", READER);
			sprintf(prefijo,"1|%s|%3d",READER,procesoActual->id);
	 		sprintf(prefijoLog,"%s|%3d",READER,procesoActual->id);
			llaveSegmento = LLAVE_SEGMENTO_READERS;
		    break;
	    case TIPO_READER_EGOISTA:
	    	sprintf(tipoProceso, "%s", READER_EGOISTA);
	    	sprintf(prefijoLog,"%s|%3d",READER_EGOISTA,procesoActual->id);
			llaveSegmento = LLAVE_SEGMENTO_READERS_EGOISTAS;
	        break;
	    default:
	        break;
	}
	shmid = getMemID(LLAVE_SEGMENTO,tamanioMem);
	shm = getMem(shmid);

	while(EXITO){
		// Inicializamos el semaforo
		sem_wait(mutex);
		if(getMemID(LLAVE_SEGMENTO,NULL)){
			if(tipo == TIPO_WRITER){
				/////////////////////////////////////////////////////
				//region critica
				if((contadorLinea = escribir(prefijo,tamanioMem,shm)) > 0){
					// Tiempo de escritura
					procesoActual->lineaActual = contadorLinea;
					procesoActual->estado = ESTADO_ESCRITURA;
				//registrar(llaveSegmento,contadorLinea,prefijoLog,procesoActual);
					registrar(llaveSegmento,(procesoActual->id)-1,contadorLinea,prefijoLog,ESTADO_ESCRITURA,procesoActual->segmentoDatos);
					sleep(procesoActual->escritura);
					}

				sem_post(mutex);
				// Tiempo de descanso
				procesoActual->estado = ESTADO_DESCANSO;
				//registrar(llaveSegmento,contadorLinea,prefijoLog,procesoActual);
				registrar(llaveSegmento,(procesoActual->id)-1,procesoActual->lineaActual,prefijoLog,ESTADO_DESCANSO,procesoActual->segmentoDatos);
				//sleep(procesoActual->descanso);
				////////////////////////////////////////////////////
				// // Luego de dormir se bloquean y esperan el semáforo
				procesoActual->estado = ESTADO_BLOQUEADO;
				//registrar(llaveSegmento,contadorLinea,prefijoLog,procesoActual);
				registrar(llaveSegmento,(procesoActual->id)-1,procesoActual->lineaActual,prefijoLog,ESTADO_BLOQUEADO,procesoActual->segmentoDatos);
			}


			// switch(tipo){
			//     case TIPO_WRITER:
			// 		///////////////////////////////////////////////////////
			// 		// region critica, falta sincronizar
			// 		// if(contadorLinea = escribir(prefijo)){
			// 		// 	// Tiempo de escritura
			// 		// 	procesoActual->lineaActual = contadorLinea;
			// 		// 	registrar(segmentoDatosID,(procesoActual->id)-1,contadorLinea,prefijoLog,ESTADO_ESCRITURA);
			// 		// 	procesoActual->estado = ESTADO_ESCRITURA;
			// 		// 	sleep(procesoActual->escritura);
			// 		// 	sem_post(mutex);
			// 		// 	// Tiempo de descanso
			// 		// 	registrar(segmentoDatosID,(procesoActual->id)-1,procesoActual->lineaActual,prefijoLog,ESTADO_DESCANSO);
			// 		// 	procesoActual->estado = ESTADO_DESCANSO;
			// 		// 	sleep(procesoActual->descanso);
			// 		// }
			// 		// else{
			// 		//  	sem_post(mutex);
			// 		// }
			//     	printf("0\n");
			//     	sem_post(mutex);
			// 		//////////////////////////////////////////////////////
			// 		//Luego de dormir se bloquean y esperan el semáforo
			// 		procesoActual->estado = ESTADO_BLOQUEADO;
			// 		registrar(segmentoDatosID,(procesoActual->id)-1,procesoActual->lineaActual,prefijoLog,ESTADO_BLOQUEADO);
			// 		break;
			// 	case TIPO_READER://////////////por implementar

			//     	sem_post(mutex);
			// 	    break;
			//     case TIPO_READER_EGOISTA://por implementar
			//     	///////////////////////////////////////////////////////
			// 		// region critica, falta sincronizar
			// 		// if(contadorLinea = borrar()){
			// 		// 	// Tiempo de escritura
			// 		// 	procesoActual->lineaActual = contadorLinea;
			// 		// 	registrar(segmentoDatosID,(procesoActual->id-1),contadorLinea,prefijoLog,ESTADO_LECTURA);
			// 		// 	procesoActual->estado = ESTADO_LECTURA;
			// 		// 	sleep(procesoActual->escritura);
			// 		// 	// Tiempo de descanso
			// 		// 	registrar(segmentoDatosID,(procesoActual->id-1),procesoActual->lineaActual,prefijoLog,ESTADO_DESCANSO);
			// 		// 	procesoActual->estado = ESTADO_DESCANSO;
			// 		// 	sleep(procesoActual->descanso);
			// 		// }

			//     	sem_post(mutex);
			// 		//////////////////////////////////////////////////////
			// 		//Luego de dormir se bloquean y esperan el semáforo
			// 		// procesoActual->estado = ESTADO_BLOQUEADO;
			// 		// registrar(segmentoDatosID,(procesoActual->id-1),procesoActual->lineaActual,prefijoLog,ESTADO_BLOQUEADO);
			//         break;
			//     default:
			//     	sem_post(mutex);
			//         break;
			// }



		}
		else{
			// Al no encontrar memoria compartida
			// el proceso muere.
			sem_post(mutex);
			sem_close(mutex);
			printf("El %s %d fue finalizado.\n",tipoProceso,procesoActual->id);////////////////////////////////////
		    break;
			//falta escribir en bitácora
		}
	}
}

// Inicializa los writers, recibe cantidad de writers, tiempo de escritura,
// tiempo de descanso, la llave del segmento al que va a escribir y el tipo
// de proceso
void initProcesos(int cantidadProcesos,int tiempoEscritura,int tiempoDescanso,int llave,int tipo){
	int i,segmentoDatosID;
	char *segmentoDatos;
	// Monitor
	switch(tipo){
		case TIPO_WRITER:
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_WRITERS,cantidadProcesos);
			break;
		case TIPO_READER:
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_READERS,cantidadProcesos);
			break;
		case TIPO_READER_EGOISTA:
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_READERS_EGOISTAS,cantidadProcesos);
			break;
		default:
			break;
		}
	segmentoDatos = getMem(segmentoDatosID);
	crearMemoria(llave,cantidadProcesos);
	pthread_t processThread[cantidadProcesos];
	for(i=1;i<=cantidadProcesos;i++){
		proceso *nProcess = newProcess(i,tiempoEscritura,tiempoDescanso,tipo,segmentoDatos);
		pthread_create(&processThread[i-1], NULL, ejecutarProceso, nProcess);
	}
	for(i=0;i<cantidadProcesos;i++){
		pthread_join(processThread[i], NULL);
	}
}
