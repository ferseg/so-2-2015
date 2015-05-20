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
    char *buffer = malloc(sizeof(char)*100);clearString(&buffer,100);
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", tm_info);
    char *fecha= malloc(sizeof(char)*100);clearString(&fecha,100);
    sprintf(fecha,"%s",buffer);
    return fecha;
}

// Crea un mensaje valido para el segmento
// a partir de un id, el estado del proceso
// y la linea q modifico
char *crearMensaje(char *prefijo,char *extra,int linea){
    char *mensaje = (char*)malloc(TAMANIO_LINEAS+2);
    char *str = (char*)malloc(TAMANIO_LINEAS+2);
    sprintf(str,"%s",extra);
    sprintf(mensaje,"|%s|%3d|%s|\n",prefijo,linea,str);
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
    sprintf(mensaje,"%s","|_____________________________________|\n");
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

        //Se ingresan datos al segmento
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
    /*
    * Obtenemos el segmento 
    * creado por el inicializador.
    */
    int shmid;
    // Comprobamos que exista
    if(shmid = getMemID(key,NULL)){
        char *shm = getMem(shmid);

        /*
        * Se quita el segmento del espacio de datos en memoria
        */
        if (shmdt(shm) == -1){
            fprintf(stderr, "shmdt failed\n");
            return FRACASO;
        }

        /*
        * Se libera el segmento de memoria
        */   
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
int escribir(char *prefijo,int tamanioMem,char *s){
    int punteroSegmento,contadorLinea;
    contadorLinea = 1;
    for(punteroSegmento = 1; punteroSegmento < tamanioMem; ){
        if(s[punteroSegmento] == LINEA_VACIA){
            int punteroMensaje;
            char *mensaje = (char*)malloc(TAMANIO_LINEAS);
            mensaje = crearMensaje(prefijo,getTime(),contadorLinea);
            for(punteroMensaje = 0; punteroMensaje < TAMANIO_LINEAS ; punteroMensaje++){
                s[punteroSegmento-1] = mensaje[punteroMensaje];
                punteroSegmento++;
                }
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
int borrar(int tamanioMem,char *s){
    int punteroSegmento,contadorLinea;
    contadorLinea = getRandomNumber(0,(tamanioMem/TAMANIO_LINEAS)-1);
    punteroSegmento = 1 + (contadorLinea * TAMANIO_LINEAS);
    if(s[punteroSegmento] == LINEA_LLENA){
        int punteroMensaje;
        char *mensaje = (char*)malloc(TAMANIO_LINEAS);
        mensaje = crearMensajeVacio();
        for(punteroMensaje = 0; punteroMensaje < TAMANIO_LINEAS; punteroMensaje++){
            s[punteroSegmento-1] = mensaje[punteroMensaje];
            punteroSegmento++;
            }
        free(mensaje);
        return contadorLinea+1;
    }
    return FRACASO;
}


int leer(int tamanioMem,char *s,proceso *procesoActual){
    //proceso *procesoActual;

    int punteroSegmento,contadorLinea;
    contadorLinea  = procesoActual->lineaActual;
    punteroSegmento = 1 + ((contadorLinea-1)*TAMANIO_LINEAS);

    if(s[punteroSegmento] == LINEA_LLENA){
        int punteroMensaje;
        char *mensaje = (char*)malloc(TAMANIO_LINEAS+2);

        for(punteroMensaje = 0; punteroMensaje < TAMANIO_LINEAS ; punteroMensaje++){
            mensaje[punteroMensaje] = s[punteroSegmento-1];
            punteroSegmento++;
            }

        //sprintf(prefijoLog,"%s|%3d",READER,procesoActual->id);
        //registrar(LLAVE_SEGMENTO_READERS,prefijoLog,procesoActual);
        registrar(LLAVE_SEGMENTO_READERS,mensaje,procesoActual);
        sleep(procesoActual->escritura);
        free(mensaje);
        procesoActual->lineaActual += 1;
        return contadorLinea;
        }
    procesoActual->lineaActual = 1;
    return FRACASO;
}

// Inicializa el ambiente para que los demás procesos
// encuentren todo listo para ejecutarse
// recibe la cantidad de lineas que tendrá el segmento
void init(int lineas){
    sem_t *mutex,*semLog;
    mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
    semLog = sem_open(SEM_LOG_NAME,O_CREAT,0644,1);
    if(crearMemoria(LLAVE_SEGMENTO_DATOS,2) && crearMemoria(LLAVE_SEGMENTO,lineas)){
        setCantidadLineas(lineas);
        printf(MENSAJE_CREACION_EXITOSA);
    }
    else{
        printf(MENSAJE_CREACION_FALLIDA);
    }
    sem_close(mutex);
    sem_close(semLog);
}

// Finaliza todos los procesos
void finalizar(){
    printEstado();

    sem_t *mutex,*semLog;
    mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
    semLog = sem_open(SEM_LOG_NAME,0,0644,1);
    
    // mutex = sem_open(SEM_NAME,0,0644,1);
    // semLog = sem_open(SEM_LOG_NAME,O_CREAT,0644,1);
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
    }
    else{
        printf(MENSAJE_FINALIZACION_FALLIDA);
    }
    sem_post(mutex);
    sem_close(mutex);
    sem_close(semLog);
    sem_unlink(SEM_NAME);
    sem_unlink(SEM_LOG_NAME);
}
