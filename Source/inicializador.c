#include "../Headers/inicializador.h"
#include "../Headers/llaves.h"

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
    char *buffer[100];
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", tm_info);
    char *fecha[100];
    sprintf(fecha,"%s",buffer);
    return fecha;
}

// Crea un mensaje valido para el segmento
char *crearMensaje(char *id,int linea){
    char *mensaje[TAMANIO_LINEAS];
    char *fecha = getTime();
    sprintf(mensaje,"|%s|%3d|%s|\n",id,linea,fecha);
    /*
    1 reader 003
                12
                 001
                    16
                     26|\n
                     */
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
            if(i % TAMANIO_LINEAS == 1)
                *s++ = '0';
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

int escribir(char *id){
    int punteroSegmento,contadorLinea, shmid, tamanioMem;
    char *shm, *s;

    shmid = getMemID(LLAVE_SEGMENTO,NULL);
    shm = getMem(shmid);
    tamanioMem = getCantidadLineas()*TAMANIO_LINEAS;

    s = shm;
    contadorLinea = 1;
    for(punteroSegmento = 1; punteroSegmento <= tamanioMem; ){
        if(s[punteroSegmento] == '0'){
            int punteroMensaje;
            char *mensaje;
            mensaje = crearMensaje(id,contadorLinea);
            for(punteroMensaje = 0; punteroMensaje < TAMANIO_LINEAS; punteroMensaje++){
                s[punteroSegmento-1] = mensaje[punteroMensaje];
                punteroSegmento++;
                }
            //falta escribir en bitácora
            return EXITO;
        }
        punteroSegmento += TAMANIO_LINEAS;
        contadorLinea++;
    }
    return FRACASO;
}

int borrar(){return EXITO;}
int leer(){return EXITO;}


void printSegmento(int key){
    int shmid;
    char *shm;
    shmid = getMemID(LLAVE_SEGMENTO,NULL);
    shm = getMem(shmid);
    printf("%s",shm);
}

// Inicializa el ambiente para que los demás procesos
// encuentren todo listo para ejecutarse
// recibe la cantidad de lineas que tendrá el segmento
void init(int lineas){
    if(crearMemoria(LLAVE_SEGMENTO_DATOS,2) && crearMemoria(LLAVE_SEGMENTO,lineas)){
        setCantidadLineas(lineas);
        printf(MENSAJE_CREACION_EXITOSA);
    }
    else{
        printf(MENSAJE_CREACION_FALLIDA);
    }
}

// Finaliza todos los procesos
void finalizar(){
    //impresion
    printSegmento(LLAVE_SEGMENTO);
    if(liberarMemoria(LLAVE_SEGMENTO) && liberarMemoria(LLAVE_SEGMENTO_DATOS)){
        //falta finalizar demás procesos
        printf(MENSAJE_FINALIZACION_EXITOSA);
    }
    else{
        printf(MENSAJE_FINALIZACION_FALLIDA);
    }
}
