#include "../Headers/inicializador.h"

int getMemID(int key){
    return shmget(key, NULL, IPC_CREAT | 0666);
}

char *getMem(int shmid){
    return shmat(shmid, NULL, 0);
}

int crearMemoria(int key, int cantidadLineas)
{
    int shmid;
    char *shm, *s;
    int tamanio_mem = cantidadLineas*TAMANIO_LINEAS;
    
    //Se crea el segmento.
    if ((shmid = shmget(key, tamanio_mem, IPC_CREAT | 0666)) < 0) {
        perror(ERROR_CREACION);
        return -1;
    }
    
    //Se adjunta el segmento al espacio de memoria de datos.
	
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror(ERROR_LOCALIZACION);
        return -1;
    }

    //Se ingresan datos al segmento

    s = shm;
    int i;
    for (i = 1; i <= tamanio_mem; i++){
        if(i % TAMANIO_LINEAS == 1)
            *s++ = '0';
        else if(i % TAMANIO_LINEAS == 0)
            *s++ = '\n';
        else
            *s++ = '_';
    }
}

