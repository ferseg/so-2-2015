#include "../Headers/espia.h"


// Registra en el log
// aun falta escribir en el archivo, por el momento
// el finalizador imprime el estado d los segmentos
void registrar(int key,int id,int linea,char *prefijo,char *estado){
	int segmentoDatosID,punteroMensaje,punteroSegmento;
	char *segmentoDatos,*mensaje;
	if(segmentoDatosID = getMemID(key,NULL)){
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
void printSegmento(int key){
    int shmid;
    char *shm;
    if(shmid = getMemID(key,NULL)){
        shm = getMem(shmid);
        printf("%s",shm);
        }
}