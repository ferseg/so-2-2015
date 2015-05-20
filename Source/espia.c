#include "../Headers/espia.h"

// Guarda un mensaje en el log
void registrar(proceso *procesoActual){
    FILE *fp;
    fp=fopen("bitacora.txt", "a");
    switch(procesoActual->tipo){
        case TIPO_WRITER:
            fprintf(fp, "El writer %d escribio el mensaje %s, en la linea %d, a las %s.\n\n", procesoActual->id,procesoActual->mensaje,procesoActual->lineaActual,getTime());
            break;
        case TIPO_READER:
            fprintf(fp,"El lector %d leyo el mensaje...\n",procesoActual->id);
            break;
        case TIPO_READER_EGOISTA:
            fprintf(fp, "El reader egoista %d borro el mensaje %s, en la linea %d, a las %s.\n\n",procesoActual->id,procesoActual->mensaje,procesoActual->lineaActual,getTime());
            break;
        default:
            break;
    }
    fclose(fp);
}

// Registra en el log
// aun falta escribir en el archivo, por el momento
// el finalizador imprime el estado d los segmentos
void actualizar(int key,char *prefijo, proceso *procesoActual){
    sem_t *semLog;
    int punteroMensaje,punteroSegmento;
	char *mensaje = (char*)malloc(TAMANIO_LINEAS+2);
    semLog = sem_open(SEM_LOG_NAME,O_CREAT,0644,1);
    sem_wait(semLog);
    if(getMemID(key,NULL)){
        punteroSegmento = (procesoActual->id-1) * TAMANIO_LINEAS;
        mensaje = crearMensaje(prefijo,procesoActual->estado,procesoActual->lineaActual);
        for(punteroMensaje = 0; punteroMensaje < TAMANIO_LINEAS ; punteroMensaje++){
            procesoActual->segmentoDatos[punteroSegmento] = mensaje[punteroMensaje];
            punteroSegmento++;
        }
	}
    free(mensaje);
    sem_post(semLog);
    sem_close(semLog);
}

// Imprime un segmento a partir de su llave
void printEstado(){
    int segmentoID,writersID,readersID,readersEID,datosID;
    char *segmento,*writers,*readers,*readersE,*datos;
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
}