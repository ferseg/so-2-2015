#include "../Headers/segmento.h"

// Obtiene el ID  del segmento compartido a partir de su llave y su tamanio
int getMemID(int key,int tamanio_mem){
    int shmid;
    if ((shmid = shmget(key, tamanio_mem, IPC_CREAT | 0666)) < 0){
        return FRACASO;
    }
    return shmid;
}

// Obtiene un puntero al inicio del segmento compartido
// a partir de su shmid
char *getMem(int shmid){
    return shmat(shmid, NULL, 0);
}

// Retorna un arreglo de chars con la hora
char *getTime(){
    time_t timer;
    char *buffer = malloc(sizeof(char)*100);
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", tm_info);
    char *fecha= malloc(sizeof(char)*100);
    sprintf(fecha,"%s",buffer);
    free(buffer);
    return fecha;
}

// Crea un mensaje valido para el segmento
// a partir de un id, el estado del proceso
// y la linea q modifico
char *crearMensaje(char *prefijo,char *extra,int linea){
    char *mensaje = (char*)malloc(TAMANIO_LINEAS+2);
    char *str = (char*)malloc(TAMANIO_LINEAS+2);
    sprintf(str,"%s",extra);
    sprintf(mensaje,"|%s|%3d|%s|",prefijo,linea,str);
    free(str);
    /*
|1|writer |  1|  1|2015-05-18 13:53:57|
|writer |  1|  1|Escribiendo          |
_0_____________________________________
    */
    return mensaje;
}

char *crearMensajeVacio(){
    char *mensaje = (char*)malloc(TAMANIO_LINEAS+2);
    sprintf(mensaje,"%s","|_____________________________________|");
    return mensaje;
}

// Crea la memoria compartida
int crearMemoria(int key, int cantidadLineas){
    int shmid;
    char *shm, *s;
    int tamanio_mem = cantidadLineas*TAMANIO_LINEAS;
    //Se crea el segmento.
    if(shmid = getMemID(key,tamanio_mem)){
        //Se adjunta el segmento al espacio de memoria de datos.	
        shm = getMem(shmid);
        s = shm;
        int i;
        for (i = 0; i < tamanio_mem; i++){
            if((i % TAMANIO_LINEAS == 0)||(i % TAMANIO_LINEAS == TAMANIO_LINEAS-2))
                *s++ = '|';
            else if(i % TAMANIO_LINEAS == TAMANIO_LINEAS-1)
                *s++ = '\n';
            else
                *s++ = '_';
        }
        return EXITO;
    }
    return FRACASO;
}

//Libera la memoria compartida a partir de su llave
int liberarMemoria(int key){
    int shmid;
    // Comprobamos que exista
    if(shmid = getMemID(key,NULL)){
        char *shm = getMem(shmid);
        if (shmdt(shm) == -1){
            fprintf(stderr, "shmdt failed\n");
            return FRACASO;
        }
 
        if (shmctl(shmid, IPC_RMID, 0) == -1){
            fprintf(stderr, "shmctl(IPC_RMID) failed\n");
            return FRACASO;
        }
        return EXITO;
    }
    else{
        return FRACASO;
    }
}

// Encuentra la siguiente linea vacía en el segmento
// y escribe en ella el mensaje
// retorna 0 si todas las lineas estaban llenas y en caso contrario
// el retorna el numero de la linea modificada.
// recibe un prefijo, el tamaño de la memoria y el segmento 
// compartido
int escribir(char *prefijo,int tamanioMem,char *segmento,proceso *procesoActual){
    int punteroSegmento,contadorLinea;
    contadorLinea = 1;
    for(punteroSegmento = 1; punteroSegmento < tamanioMem; ){
        if(segmento[punteroSegmento] == LINEA_VACIA){
            char *mensaje = (char*)malloc(TAMANIO_LINEAS);
            mensaje = crearMensaje(prefijo,getTime(),contadorLinea);
            
            guardarBuffer(segmento,mensaje,punteroSegmento-1,TAMANIO_LINEAS - 1);
            sprintf(procesoActual->mensaje, mensaje);

            free(mensaje);
            return contadorLinea;
        }
        punteroSegmento += TAMANIO_LINEAS;
        contadorLinea++;
    }
    return FRACASO;
}

// Escoje aleatoriamente una linea del segmento
// y si está llena la borra. Retorna 0 si 
// no borró nada en el segmento y el numero
// de linea que borró en caso contrario.
// Recibe el tamaño de la memiria y el
// segmento compartido
int borrar(int tamanioMem,char *segmento,proceso *procesoActual){
    int punteroSegmento,contadorLinea;
    contadorLinea = getRandomNumber(0,(tamanioMem/TAMANIO_LINEAS)-1);
    punteroSegmento = 1 + (contadorLinea * TAMANIO_LINEAS);
    if(segmento[punteroSegmento] != LINEA_VACIA){
        int punteroMensaje = 0;
        char *mensaje = (char*)malloc(TAMANIO_LINEAS);
        char *mensaje2 = (char*)malloc(TAMANIO_LINEAS);
        mensaje = crearMensajeVacio();
        guardarBuffer(mensaje2,&segmento[punteroSegmento-1],punteroMensaje,TAMANIO_LINEAS - 1);
        guardarBuffer(segmento,mensaje,punteroSegmento-1,TAMANIO_LINEAS - 1);
        sprintf(procesoActual->mensaje, mensaje2);
        free(mensaje);free(mensaje2);
        return contadorLinea+1;
    }
    return FRACASO;
}

// Lee una linea del segmento compartido
int leer(int tamanioMem,char *s,proceso *procesoActual){
    int punteroSegmento,contadorLinea;
    contadorLinea  = procesoActual->lineaActual;
    punteroSegmento = 1 + ((contadorLinea-1)*TAMANIO_LINEAS);
    char *prefijoLog = (char*)malloc(TAMANIO_LINEAS+2);

    if(s[punteroSegmento] != LINEA_VACIA){
        int punteroMensaje = 0;
        char *mensaje = (char*)malloc(TAMANIO_LINEAS+2);
        sprintf(prefijoLog,"%s|%3d",READER,procesoActual->id);
        guardarBuffer(mensaje,&s[punteroSegmento-1],punteroMensaje,TAMANIO_LINEAS - 1);
        procesoActual->estado = ESTADO_LECTURA;
        sprintf(procesoActual->mensaje,mensaje);
        free(mensaje);
        actualizar(LLAVE_SEGMENTO_READERS,prefijoLog,procesoActual);
        registrar(procesoActual);
        sleep(procesoActual->escritura);
        procesoActual->lineaActual += 1;
        if(procesoActual->lineaActual == (tamanioMem/TAMANIO_LINEAS)){
            procesoActual->lineaActual = 1;
            }
        free(prefijoLog);
        return contadorLinea;
        }
    free(prefijoLog);
    procesoActual->lineaActual = 1;
    return FRACASO;
}

// Inicializa el ambiente para que los demás procesos
// encuentren todo listo para ejecutarse
// recibe la cantidad de lineas que tendrá el segmento
void init(int lineas){
    sem_t *mutex,*semLog,*semDatos;
    mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
    semLog = sem_open(SEM_LOG_NAME,O_CREAT,0644,1);
    semDatos = sem_open(SEM_DATOS_NAME,O_CREAT,0644,1);
    //if(crearMemoria(LLAVE_SEGMENTO_DATOS,2) && crearMemoria(LLAVE_SEGMENTO,lineas)){
    if(crearMemoria(LLAVE_SEGMENTO_DATOS,sizeof(datos)) && crearMemoria(LLAVE_SEGMENTO,lineas)){
        setCantidadLineas(lineas);
        FILE *fp = fopen("bitacora.txt", "w");
        fprintf(fp, "Se inicializo el programa a las: %s.\n\n", getTime());
        fclose(fp);
        printf(MENSAJE_CREACION_EXITOSA);
    }
    else{
        printf(MENSAJE_CREACION_FALLIDA);
    }
    sem_close(mutex);
    sem_close(semLog);
    sem_close(semDatos);
}

// Finaliza todos los procesos
void finalizar(){
    printEstado();

    sem_t *mutex,*semLog,*semDatos;
    mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
    semLog = sem_open(SEM_LOG_NAME,0,0644,1);
    semDatos = sem_open(SEM_DATOS_NAME,0,0644,1);
    sem_wait(mutex);
    if(liberarMemoria(LLAVE_SEGMENTO) && liberarMemoria(LLAVE_SEGMENTO_DATOS)){
        //falta finalizar demás procesos
        if(!liberarMemoria(LLAVE_SEGMENTO_WRITERS)){
            printf(MENSAJE_ERROR_WRITERS);
            }
        if(!liberarMemoria(LLAVE_SEGMENTO_READERS)){
            printf(MENSAJE_ERROR_READERS);
            }
        if(!liberarMemoria(LLAVE_SEGMENTO_READERS_EGOISTAS)){
            printf(MENSAJE_ERROR_READERS_EGOISTAS);
            }
        printf(MENSAJE_FINALIZACION_EXITOSA);
        FILE *fp = fopen("bitacora.txt", "a");
        fprintf(fp, "\nSe finalizo el programa a las: %s.", getTime());
        fclose(fp);
        printf(MENSAJE_CREACION_EXITOSA);
    }
    else{
        printf(MENSAJE_FINALIZACION_FALLIDA);
    }
    sem_post(mutex);
    sem_close(mutex);
    sem_close(semLog);
    sem_close(semDatos);
    sem_unlink(SEM_NAME);
    sem_unlink(SEM_LOG_NAME);
    sem_unlink(SEM_DATOS_NAME);
}
