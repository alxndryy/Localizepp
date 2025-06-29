#ifndef FUNCOES_H
#define FUNCOES_H

#include "local.h"
#include "veiculo.h"
#include "pedido.h"

/*Prototipo de listaLocais */

void listaLocais(int *num_locais, Local *&locais);

/*Gera um id de letras maiúsculas aleatório para Pedido */

char *geraId(char id[TAM_ID])
{
	int i;

	for (i=0; i<TAM_ID; i++)
		id[i]='A'+(std::rand()%26);

	return id;
}

/*Reultilização de código */

void pausa()
{
	std::cout << "\n[Enter]...\n";
	std::cin.ignore();
	std::cin.get();
}

void limpaTela()
{
	std::system(LIMPA_TELA);
}

void insereLocal(int local_index, Local *&locais)
{
	char cidade[TAM];
	float coord_x, coord_y;

	limpaTela();
	
	std::cout << "*Insira a cidade: ";
	std::cin.ignore();
	std::cin.getline(cidade, TAM);

	std::cout << "*Insira a posição em coordenadas (x, y): ";
	std::cin >> coord_x >> coord_y;
	
	locais[local_index].setLocal(cidade, coord_x, coord_y);
}

void insereVeiculo(int veiculo_index, Veiculo *&veiculos, 
				int *num_locais, Local *&locais)
{
	int local_index;
	char placa[TAM_PLACA], modelo[TAM];

	limpaTela();

	std::cout << "*Insira a placa: ";
		
	std::cin.ignore();
	std::cin.getline(placa, TAM_PLACA);

	std::cout << "*Insira o modelo: ";
	std::cin.getline(modelo, TAM);

	listaLocais(num_locais, locais);

	std::cout << "*Informe onde ele está localizado: ";
	std::cin >> local_index;

	veiculos[veiculo_index].setVeiculo(placa, modelo);
	veiculos[veiculo_index].setPosicao(locais[local_index]);
}

void inserePedido(int pedido_index, Pedido *&pedidos, 
			int *num_locais, Local *&locais)
{
	int i, local_index;
	float peso;
	char id[TAM_ID];

	limpaTela();

	std::cout << "*Insira o peso: ";
	std::cin >> peso;

	listaLocais(num_locais, locais);

	std::cout << "*Informe a origem: ";
	std::cin >> local_index;

	pedidos[i].setOrigem(locais[local_index]);

	std::cout << "*Informe o destino: ";
	std::cin >> local_index;

	pedidos[i].setDestino(locais[local_index]);
		
	pedidos[i].setPedido(geraId(id), peso); /*linha 6 */
}

/*Funções para CRUD de pedido */


/*Cadastro de pedidos */

void cadastraPedidos(int *num_pedidos, int *num_locais, 
			Pedido *&pedidos, Local *&locais)
{
	int i;

	std::cout << "Quantos pedidos serão cadastrados? ";
	std::cin >> *num_pedidos;

	/*Aloca dinamicamente um vetor de objetos de pedidos */

	pedidos=new Pedido[*num_pedidos];

	for (i=0; i<*num_pedidos; i++)
		inserePedido(i, pedidos, num_locais, locais);
}

/*Listagem de pedidos */

void listaPedidos(int *num_pedidos, Pedido *&pedidos)
{
	int i;

	for (i=0; i<*num_pedidos; i++) {
		std::cout << "\nPedido [" << i << "]\n";
		std::cout << "- Id: " << pedidos[i].getId() << "\n";
		std::cout << "- Peso: " << pedidos[i].getPeso() << " Kg" << "\n";
		std::cout << "- Origem: "
			  << pedidos[i].getOrigem().getLocal() << ", "
			  << pedidos[i].getOrigem().getX() << " "
			  << pedidos[i].getOrigem().getY() << "\n";
		std::cout << "- Destino: "
			  << pedidos[i].getOrigem().getLocal() << ", "
			  << pedidos[i].getOrigem().getX() << " "
			  << pedidos[i].getOrigem().getY() << "\n\n";
	}

	pausa();
}

/*Atualização de pedidos */

void atualizaPedido(int *num_pedidos, int *num_locais, 
			Pedido *&pedidos, Local *&locais)
{
	int pedido_index;

	listaPedidos(num_pedidos, pedidos);
	
	std::cout << "\nInsira o pedido a ser atualizado: ";
	std::cin >> pedido_index;

	inserePedido(pedido_index, pedidos, num_locais, locais);
}

/*Exclusão de pedidos */

void excluiPedidos(int *num_pedidos, Pedido *&pedidos)
{
	delete[] pedidos;
	pedidos=nullptr;
	*num_pedidos=0;
}
	
/*Funções para CRUD de Veiculo */


/*Cadastro de veiculos */

void cadastraVeiculos(int *num_veiculos, int *num_locais, 
			Veiculo *&veiculos, Local *&locais)
{
	int i;

	std::cout << "Quantos veiculos serão cadastrados? ";
	std::cin >> *num_veiculos;

	/*Aloca dinamicamente um vetor de objetos de Veiculo */

	veiculos=new Veiculo[*num_veiculos];

	for (i=0; i<*num_veiculos; i++)
		insereVeiculo(i, veiculos, num_locais, locais); /*linha 27 */
}

/*Listagem de veiculos */

void listaVeiculos(int *num_veiculos, Veiculo *&veiculos)
{
	int i;

	for (i=0; i<*num_veiculos; i++){
		std::cout << "\nVeiculo [" << i << "]\n";
		std::cout << "- Placa: " << veiculos[i].getPlaca() << "\n";
		std::cout << "- Modelo: " << veiculos[i].getModelo() << "\n";
		std::cout << "- Localização: " 
			  << veiculos[i].getPosicao().getLocal() << ", "
			  << veiculos[i].getPosicao().getX() << " "
			  << veiculos[i].getPosicao().getY() << "\n";
		std::cout << "- Status: " 
			  << (veiculos[i].isDisponivel() ? "Disponivel\n" : "Ocupado\n\n");
	}

	pausa();
}

/*Atualização de veiculos */

void atualizaVeiculo(int *num_veiculos, int *num_locais, 
		     Veiculo *&veiculos, Local *&locais)
{
	int veiculo_index;

	listaVeiculos(num_veiculos, veiculos); /*linha */
	
	std::cout << "\nInsira o veiculo a ser atualizado: ";
	std::cin >> veiculo_index;

	insereVeiculo(veiculo_index, veiculos, num_locais, locais); /*Linha */
}

/*Exclusão de veiculos */

void excluiVeiculos(int *num_veiculos, Veiculo *&veiculos) 
{
	delete[] veiculos;
	veiculos=nullptr;
	*num_veiculos=0;
}

/*Funções para CRUD de Local */


/*Cadastro de locais */

void cadastraLocais(int *num_locais, Local *&locais)
{
	int i;

	std::cout << "Quantos locais serão cadastrados? ";
	std::cin >> *num_locais;

	/*Aloca dinâmaicamente um vetor de objetos de Local */ 

	locais=new Local[*num_locais];

	for (i=0; i<*num_locais; i++)
		insereLocal(i, locais); /*Linha */
}

/*Listagem de locais */

void listaLocais(int *num_locais, Local *&locais)
{
	int i;

	for (i=0; i<*num_locais; i++){
		std::cout << "\nLocal [" << i << "]\n";
		std::cout << "- Cidade: " << locais[i].getLocal() << "\n";
		std::cout << "- x: " << locais[i].getX();
		std::cout << " y: " << locais[i].getY() << "\n\n";
	}

	pausa();
}

/*Atualização de locais */

void atualizaLocal(int *num_locais, Local *&locais)
{
	int local_index;

	listaLocais(num_locais, locais); /*Linha */

	std::cout << "\nInsira o local a ser atualizado: ";
	std::cin >> local_index;

	insereLocal(local_index, locais); /*Linha */
}

/*Exclusão de locais */

void excluiLocais(int *num_locais, Local *&locais)
{
	delete[] locais;
	locais=nullptr;
	*num_locais=0;
}

#endif
