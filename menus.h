/*Menus para exibição, e realização de operações como: Criação, Listagem,
Ataulização, Exclusão, e Cálculo da rota */
#ifndef MENUS_H
#define MENUS_H

#include "funcoes.h"

/*Menu para Pedidos */

void menuPedidos(int *num_pedidos, int *num_locais,
		 Pedido *&pedidos, Local *&locais)
{
	int opcao;

	limpaTela();

	std::cout << "[1] Cadastrar pedidos\n"
		  << "[2] Listar    pedidos\n"
		  << "[3] Atualizar pedidos\n"
		  << "[4] Excluir   pedidos\n\n"
		  << "[5] Fazer     pedido\n"
		  << "[6] Voltar\n\n";
	std::cin >> opcao;

	switch (opcao){
		case 1:
			limpaTela();

			cadastraPedidos(num_pedidos, num_locais,
						pedidos, locais);
			break;
		case 2:
			limpaTela();

			listaPedidos(num_pedidos, pedidos);
			break;
		case 3:
			limpaTela();

			atualizaPedido(num_pedidos, num_locais,
						pedidos, locais);
			break;
		case 4:
			limpaTela();

			excluiPedidos(num_pedidos, pedidos);
			break;
		case 5:
			//fazPedido()
			break;
		case 6:
			break;
	}
}

/*Menu para veiculos */

void menuVeiculos(int *num_veiculos, int *num_locais,
		  Veiculo *&veiculos, Local *&locais)
{
	int opcao;

	limpaTela();

	std::cout << "[1] Cadastrar veiculos\n"
		  << "[2] Listar    veiculos\n"
		  << "[3] Atualizar veiculos\n"
		  << "[4] Excluir   veiculos\n"
		  << "[5] Voltar\n\n";
	std::cin >> opcao;

	switch (opcao){
		case 1:
			limpaTela();

			cadastraVeiculos(num_veiculos, num_locais,
						veiculos, locais);
			break;
		case 2:
			limpaTela();

			listaVeiculos(num_veiculos, veiculos);
			break;
		case 3:
			limpaTela();

			atualizaVeiculo(num_veiculos, num_locais,
						veiculos, locais);
			break;
		case 4:
			limpaTela();

			excluiVeiculos(num_veiculos, veiculos);
			break;
		case 5:
			break;
	}
}

/*Menu para locais */

void menuLocais(int *num_locais, Local *&locais)
{
	int opcao;

	limpaTela();
	
	std::cout << "[1] Cadastrar locais\n"
		  << "[2] Listar    locais\n"
		  << "[3] Atualizar locais\n"
		  << "[4] Excluir   locais\n\n"
		  << "[5] Voltar\n\n";
	std::cin >> opcao;
	
	switch (opcao){
		case 1:	
			limpaTela();

			cadastraLocais(num_locais, locais);
			break;
		case 2:
			limpaTela();

			listaLocais(num_locais, locais);
			break;
		case 3:
			limpaTela();

			atualizaLocal(num_locais, locais);
			break;
		case 4:
			limpaTela();

			excluiLocais(num_locais, locais);
			break;
		case 5:
			break;
	}
}

/*Menu que chama os outros */

void menuPrincipal(Local *&locais, Veiculo *&veiculos, Pedido *&pedidos, 
		   int *num_locais, int *num_veiculos, int *num_pedidos)
{
	int opcao;

	while (true){
		limpaTela();

		std::cout << "\n---| Bem Vindo ao Localize++ |---\n\n"
			  << "Escolha entre:\n\n"
			  << "[1] Locais\n"
			  << "[2] Veiculos\n"
			  << "[3] Pedidos\n\n"
			  << "[4] Sair\n\n";
		std::cin >> opcao;
	
		switch (opcao){
			case 1:
				menuLocais(num_locais, locais);
				break;
			case 2:
				menuVeiculos(num_veiculos, num_locais,
							veiculos, locais);
				break;
			case 3:
				menuPedidos(num_pedidos, num_locais,
							pedidos, locais);
				break;
			case 4:
				limpaTela();

				excluiLocais(num_locais, locais);
				excluiVeiculos(num_veiculos, veiculos);
				excluiPedidos(num_pedidos, pedidos);
				return;
		}
	}
}

#endif
