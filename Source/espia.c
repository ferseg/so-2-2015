#include "../Headers/espia.h"


// Registra en el log
// aun falta escribir en el archivo, por el momento
// el finalizador imprime el estado d los segmentos
void registrar(int key,int id,int linea,char *prefijo,char *estado,char *segmentoDatos){
    sem_t *semLog;
    int punteroMensaje,punteroSegmento;
    //char *mensaje = malloc(sizeof(char) * TAMANIO_LINEAS);//clearString(&mensaje,TAMANIO_LINEAS);
	char *mensaje = (char*)malloc(TAMANIO_LINEAS+2);
    semLog = sem_open(SEM_LOG_NAME,O_CREAT,0644,1);
    sem_wait(semLog);
    if(getMemID(key,NULL)){
		punteroSegmento = id * TAMANIO_LINEAS;
        mensaje = crearMensaje(prefijo,estado,linea);
        for(punteroMensaje = 0; punteroMensaje < TAMANIO_LINEAS; punteroMensaje++){
             segmentoDatos[punteroSegmento] = mensaje[punteroMensaje];
             punteroSegmento++;
        }
	}
    free(mensaje);
    sem_post(semLog);
    sem_close(semLog);
}

// Imprime un segmento a partir de su llave
void printEstado(){

    sem_t *mutex;
    mutex = sem_open(SEM_NAME,0,0644,1);
    int segmentoID,writersID,readersID,readersEID,datosID;
    char *segmento,*writers,*readers,*readersE,*datos;
    //sem_wait(mutex);
    if(segmentoID = getMemID(LLAVE_SEGMENTO,NULL)){
        segmento = getMem(segmentoID);
        printf("%s%s%s%s%s\n",BORDE, TITULO_DATOS, BORDE, segmento, BORDE);
        
        // ver datos
        // if(datosID = getMemID(LLAVE_SEGMENTO_DATOS,NULL)){
        //     datos = getMem(datosID);
        //     printf("%s%s%s%s\n%s\n",BORDE, "datos\n", BORDE, datos, BORDE);
        //     }

        // ver writers
        if(writersID = getMemID(LLAVE_SEGMENTO_WRITERS,NULL)){
            writers = getMem(writersID);
            printf("%s%s%s%s%s\n",BORDE, TITULO_WRITER, BORDE, writers, BORDE);
            }
        // ver readers
        if(readersID = getMemID(LLAVE_SEGMENTO_READERS,NULL)){
            readers = getMem(readersID);
            printf("%s%s%s%s%s\n",BORDE, TITULO_READER, BORDE, readers, BORDE);
            }
        // ver readers egoistas
        if(readersEID = getMemID(LLAVE_SEGMENTO_READERS_EGOISTAS,NULL)){
            readersE = getMem(readersEID);
            printf("%s%s%s%s%s\n",BORDE, TITULO_READER_EGOISTA, BORDE, readersE, BORDE);
            }
        }

    //sem_post(mutex);
    sem_close(mutex);
}