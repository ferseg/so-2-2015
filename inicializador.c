#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>


/* Memoria compartida */
int crearMemoria(int cantidadLineas);


void main(int argc, char *argv[])
{
	//Se esperan un parámetro para determinar la cantidad de líneas de memoria compartida.
	if(argc == 2) 
	{	
		int cantidadLineas = atoi(argv[1]);
		crearMemoria(cantidadLineas);			
	}
	else
	{
		printf("No indicó la cantidad de líneas que desea va a tener la memoria compartida\n");
	}
}

int crearMemoria(int cantidadLineas)
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    	//Se nombrará al segmento de memoria compartida "2015".
    key = 2015;

    int tamanio_mem = cantidadLineas*30 + 2;
    
    //Se crea el segmento.
    if ((shmid = shmget(key, tamanio_mem, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return -1;
    }

    //Se adjunta el segmento al espacio de memoria de datos.
	
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return -1;
    }

    //Se ingresan datos al segmento

    s = shm;
    *s = '0';
    s++;
    int i;
    for (i = 1; i <= tamanio_mem; i++){
        if( i == tamanio_mem)
    		*s++ = '\0';	
    	else
        	*s++ = 'X';
    }
    
    //Finalmente se guarda en un archivo la cantidad de procesos para que otros puedan saberlo
       
    FILE *fp;
	fp=fopen("cantidadLineas.txt", "w");
	fprintf(fp, "%d", cantidadLineas);
	fclose(fp);
}
