#include "../Headers/espia.h"


// Registra en el log
// aun falta escribir en el archivo, por el momento
// el finalizador imprime el estado d los segmentos
void registrar(int segmentoDatosID,int id,int linea,char *prefijo,char *estado){
	int punteroMensaje,punteroSegmento;
	char *segmentoDatos;
    char *mensaje = malloc(sizeof(char)*TAMANIO_LINEAS);clearString(&mensaje,TAMANIO_LINEAS);
	if(segmentoDatosID > 0){
		segmentoDatos = getMem(segmentoDatosID);
		punteroSegmento = id * TAMANIO_LINEAS;
        mensaje = crearMensaje(prefijo,estado,linea);
        for(punteroMensaje = 0; punteroMensaje < TAMANIO_LINEAS; punteroMensaje++){
            segmentoDatos[punteroSegmento] = mensaje[punteroMensaje];
            punteroSegmento++;
        }
	}
}

// Imprime un segmento a partir de su llave
void printEstado(){

    sem_t *mutex;
    mutex = sem_open(SEM_NAME,0,0644,1);
    int segmentoID,writersID,readersID,readersEID;
    char *segmento,*writers,*readers,*readersE;
    //sem_wait(mutex);
    if(segmentoID = getMemID(LLAVE_SEGMENTO,NULL)){
        segmento = getMem(segmentoID);
        printf("%s%s%s%s%s\n",BORDE, TITULO_DATOS, BORDE, segmento, BORDE);
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