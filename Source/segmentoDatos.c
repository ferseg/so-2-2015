#include "../Headers/segmentoDatos.h"

int getCantidadLineas(){
    int shmid = getMemID(LLAVE_SEGMENTO_DATOS);
    char *shm = getMem(shmid);
    //printf("%d\n",shm);
    return atoi(shm);
}

void setCantidadLineas(int cantidadLineas){
    int shmid = getMemID(LLAVE_SEGMENTO_DATOS);
    char *shm = getMem(shmid);
    sprintf(shm,"%d",cantidadLineas);
}
