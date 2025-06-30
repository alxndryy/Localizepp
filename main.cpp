#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cmath>

#define TAM 512
#define TAM_ID 4
#define TAM_PLACA 7

/*Para o comando system clear funcionar em ambos os sistemas (windows/linux)*/
#if defined(_WIN32) || defined(_WIN64)
    #define LIMPA_TELA "cls"
#else
    #define LIMPA_TELA "clear"
#endif

#include "menus.h"

int main()
{
	Local *locais=nullptr;
	Veiculo *veiculos=nullptr;
	Pedido *pedidos=nullptr;

	int num_locais=0;
	int num_veiculos=0;
	int num_pedidos=0;

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	
	menuPrincipal(locais, veiculos, pedidos, &num_locais, 
				&num_veiculos, &num_pedidos);

	return 0;
}
