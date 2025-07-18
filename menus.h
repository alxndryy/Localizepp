#ifndef MENUS_H
#define MENUS_H

#include "funcoes.h"

void menuPedidos(int *num_locais, int *num_veiculos, int *num_pedidos, 
		 Local *&locais, Veiculo *&veiculos, Pedido *&pedidos)
{
	int opcao;

	limpaTela();

	std::cout << "[1] Cadastrar pedidos\n"
		  << "[2] Listar    pedidos\n"
		  << "[3] Atualizar pedidos\n"
		  << "[4] Excluir   pedidos\n\n"
		  << "[5] Enviar    pedido\n"
		  << "[6] Voltar\n\n";
	std::cin >> opcao;

	switch (opcao){
		case 1:
			limpaTela();

			cadastraPedidos(num_locais, 
		   		num_pedidos, locais, pedidos);
			break;
		case 2:
			limpaTela();

			listaPedidos(num_pedidos, pedidos);
			break;
		case 3:
			limpaTela();

			/*Apenas chama a função se houver pedidos para serem
			 atualizados */

			if (*num_pedidos>0)
				atualizaPedido(num_locais, 
		   			num_pedidos, locais, pedidos);
			break;
		case 4:
			limpaTela();

			excluiPedidos(num_pedidos, pedidos);
			break;
		case 5:
			limpaTela();

			if (*num_pedidos>0 && *num_veiculos>0)
				enviaPedido(num_locais, num_veiculos, 
					num_pedidos, locais, veiculos, pedidos);
			break;
		case 6:
			break;
	}
}

void menuVeiculos(int *num_locais, int *num_veiculos,
		  Local *&locais, Veiculo *&veiculos)
{
	int opcao;

	limpaTela();

	std::cout << "[1] Cadastrar veiculos\n"
		  << "[2] Listar    veiculos\n"
		  << "[3] Atualizar veiculos\n"
		  << "[4] Excluir   veiculos\n\n"
		  << "[5] Voltar\n\n";
	std::cin >> opcao;

	switch (opcao){
		case 1:
			limpaTela();

			cadastraVeiculos(num_locais, num_veiculos,
						locais, veiculos);
			break;
		case 2:
			limpaTela();

			listaVeiculos(num_veiculos, veiculos);
			break;
		case 3:
			limpaTela();

			/*Apenas chama a função se houver veiculos para serem
			 atualizados */

			if (*num_veiculos>0)
				atualizaVeiculo(num_locais, num_veiculos,
							locais, veiculos);
			break;
		case 4:
			limpaTela();

			excluiVeiculos(num_veiculos, veiculos);
			break;
		case 5:
			break;
	}
}

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

			/*Apenas chama a função se houver locais para serem
			 atualizados */

			if (*num_locais>0)
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

void menuBackup(int *num_locais, int *num_veiculos, int *num_pedidos, 
		Local *&locais, Veiculo *&veiculos, Pedido *&pedidos)
{
	int opcao;

	std::cout << "[1] Fazer Backup\n"
		  << "[2] Ler   Backup\n\n"
		  << "[3] Voltar\n\n";
	std::cin >> opcao;

	switch (opcao) {
		case 1:
			limpaTela();

			backup(num_locais, num_veiculos, num_pedidos, 
	  			locais, veiculos, pedidos);
			break;
		case 2:
			limpaTela();

			restora(num_locais, num_veiculos, num_pedidos, 
	   			locais, veiculos, pedidos); 
			break;
		case 3:
			break;
	}
}

void menuPrincipal(int *num_locais, int *num_veiculos, int *num_pedidos, 
		   Local *&locais, Veiculo *&veiculos, Pedido *&pedidos)
{
	int opcao;

	while (true){
		limpaTela();

		std::cout << "\n---| Bem Vindo ao Localize++ |---\n\n"
			  << "Escolha entre:\n\n"
			  << "[1] Locais\n"
			  << "[2] Veiculos\n"
			  << "[3] Pedidos\n"
			  << "[4] Backup\n\n"
			  << "[5] Sair\n\n";
		std::cin >> opcao;
	
		switch (opcao){
			case 1:
				menuLocais(num_locais, locais);
				break;
			case 2:
				menuVeiculos(num_locais, num_veiculos,
							locais, veiculos);
				break;
			case 3:
				menuPedidos(num_locais, num_veiculos, 
					num_pedidos, locais, veiculos, pedidos);
				break;
			case 4:
				limpaTela();

				menuBackup(num_locais, num_veiculos, 
	       				num_pedidos, locais, veiculos, pedidos);
				break;
			case 5:
				limpaTela();

				excluiLocais(num_locais, locais);
				excluiVeiculos(num_veiculos, veiculos);
				excluiPedidos(num_pedidos, pedidos);

				return;
		}
	}
}

#endif
