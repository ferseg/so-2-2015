#include "../Headers/finalizador.h"


int main()
{

    liberar_memoria();

	/*Se borran archivos usados durante el proceso*/
	remove("cantidadLineas.txt");
}