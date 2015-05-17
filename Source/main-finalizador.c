#include "../Headers/inicializador.h"
#include "../Headers/llaves.h"

int main()
{
	printf("%d\n",getCantidadLineas());
    liberar_memoria(LLAVE_SEGMENTO);
    liberar_memoria(LLAVE_SEGMENTO_DATOS);
}