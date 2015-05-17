#include "../Headers/finalizador.h"


int main()
{
	//getCantidadLineas();
    liberar_memoria();

	/*Se borran archivos usados durante el proceso*/
	remove("cantidadLineas.txt");
}