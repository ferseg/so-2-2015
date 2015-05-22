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
  	newProcess->lineaActual = 1;
  	newProcess->estado = ESTADO_DESCANSO;
  	newProcess->segmentoDatos = pSegmentoDatos;
  	newProcess->mensaje = (char*)malloc(TAMANIO_LINEAS+10);
	return newProcess;
}

// Hilo encargado de la ejecución de los procesos
void ejecutarProceso(proceso *procesoActual){
	int shmid, datosID,llaveSegmento, contadorLinea, tipo;
	char *prefijo = (char*)malloc(TAMANIO_LINEAS);
	char *prefijoLog = (char*)malloc(TAMANIO_LINEAS);
	char *shm;
	datos *segmentoDatos;
    sem_t *mutex,*semDatos;
	int tamanioMem;
	char *tipoProceso = (char*)malloc(30);
	tipo = procesoActual->tipo;

	switch(procesoActual->tipo){
	    case TIPO_WRITER:
	    	sprintf(tipoProceso,"%s", WRITER);
  			sprintf(prefijo,"1|%s|%3d",WRITER,procesoActual->id);
  			sprintf(prefijoLog,"%s|%3d",WRITER,procesoActual->id);
  			llaveSegmento = LLAVE_SEGMENTO_WRITERS;
			break;
		case TIPO_READER:
			sprintf(tipoProceso, "%s", READER);
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
	if(shmid = getMemID(LLAVE_SEGMENTO,NULL)){
		datosID = getMem(LLAVE_SEGMENTO_DATOS);
		shm = getMem(shmid);
		segmentoDatos = getMem(datosID);
		tamanioMem = getCantidadLineas() * TAMANIO_LINEAS;
		mutex = sem_open(SEM_NAME,0,0644,1);
		semDatos = sem_open(SEM_DATOS_NAME,0,0644,1);
		}
	else{
		mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
		semDatos = sem_open(SEM_DATOS_NAME,O_CREAT,0644,1);
		}

	while(EXITO){
		// Inicializamos el semaforo
		//sem_wait(mutex);
		if(getMemID(LLAVE_SEGMENTO,NULL)){
			if(tipo == TIPO_WRITER){
				sem_wait(mutex);
				sem_wait(semDatos);
				/////////////////////////////////////////////////////
				//region critica
				if(getLectores() == 0){
				//if(contadorLinea = escribir(prefijo,tamanioMem,shm,procesoActual)){
					// Tiempo de escritura
					//sem_wait(semDatos);
					if(contadorLinea = escribir(prefijo,tamanioMem,shm,procesoActual)){
					//if(getLectores()==0){
						setLectura(0);decReader();
						//sem_post(semDatos);
						//procesoActual->lineaActual = contadorLinea;
						//procesoActual->estado = ESTADO_ESCRITURA;
						actualizar(llaveSegmento,prefijoLog,procesoActual);
						registrar(procesoActual);
						sleep(procesoActual->escritura);
						setLectura(1);
						}
					//sem_post(semDatos);
					}
				sem_post(semDatos);
				sem_post(mutex);
				}
			else if(tipo == TIPO_READER){
				//sem_post(mutex);
				sem_wait(semDatos);
				if(getLectura()){
					decReader();
					incLectores();
					sem_post(semDatos);
					leer(tamanioMem,shm,procesoActual);
					sem_wait(semDatos);
					decLectores();
					//sem_post(semDatos);
				 	}
				// else{
				// 	sem_post(semDatos);
				// 	}
				sem_post(semDatos);
				}
			else if(tipo == TIPO_READER_EGOISTA){
				/////////////////////////////////////////////////////
				//region critica
				sem_wait(mutex);
				sem_wait(semDatos);
				//if(contadorLinea = borrar(tamanioMem,shm,procesoActual)){
				if(incReader()<4 && getLectores() == 0){
					// Tiempo de escritura
					//sem_wait(semDatos);
				
					//if(incReader()<3 && getLectores()==0){
					if(contadorLinea = borrar(tamanioMem,shm,procesoActual)){
						setLectura(0);
						//procesoActual->estado = ESTADO_LECTURA;
						actualizar(llaveSegmento,prefijoLog,procesoActual);
						registrar(procesoActual);
						sleep(procesoActual->escritura);
						setLectura(1);

						}
					}
				sem_post(semDatos);
				sem_post(mutex);
				}
				//sem_post(mutex);
				// Tiempo de descanso
				procesoActual->estado = ESTADO_DESCANSO;
				actualizar(llaveSegmento,prefijoLog,procesoActual);
				sleep(procesoActual->descanso);
				/////////////////////////////////////////////////////
				// Luego de dormir se bloquean y esperan el semáforo
				procesoActual->estado = ESTADO_BLOQUEADO;
				actualizar(llaveSegmento,prefijoLog,procesoActual);
			}
		else{
			// Al no encontrar memoria compartida
			// el proceso muere.
			sem_post(mutex);
			sem_close(mutex);
			sem_close(semDatos);
			printf("El %s %d fue finalizado.\n",tipoProceso,procesoActual->id);////////////////////////////////////
		    break;
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
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_WRITERS,cantidadProcesos*TAMANIO_LINEAS);
			break;
		case TIPO_READER:
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_READERS,cantidadProcesos*TAMANIO_LINEAS);
			break;
		case TIPO_READER_EGOISTA:
			segmentoDatosID = getMemID(LLAVE_SEGMENTO_READERS_EGOISTAS,cantidadProcesos*TAMANIO_LINEAS);
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
