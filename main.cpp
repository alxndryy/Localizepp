#include <iostream>
#include <ctime>   /*Biblioteca pro srand */ 
#include <cstring> /*Biblioteca pras funções strcpy, strlen, ... */ 
#include <cstdlib> /*Biblioteca para usar system */ 
#include <cmath>   /*Biblioteca para usar sqrt */
#include <thread>  /*Biblioteca para usar sleep_for */
#include <chrono>  /*Bilioteca para usar temporizadores */

#define TAM 512
#define TAM_ID 4
#define TAM_PLACA 8

/*Para o comando system clear funcionar em ambos os sistemas (windows/linux) */

#if defined(_WIN32) || defined(_WIN64)
    #define LIMPA_TELA "cls"
#else
    #define LIMPA_TELA "clear"
#endif

#include "menus.h"

int main()
{
	int num_locais = 0;
	int num_veiculos = 0;
	int num_pedidos = 0;

	Local *locais = nullptr;
	Veiculo *veiculos = nullptr;
	Pedido *pedidos = nullptr;

	/*Seed para o srand */

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	
	menuPrincipal(&num_locais, &num_veiculos, &num_pedidos, 
	       locais, veiculos, pedidos);

	return 0;
}
