#ifndef FUNCOES_H
#define FUNCOES_H

#include "local.h"
#include "veiculo.h"
#include "pedido.h"

/*Sistema de backup */

void backup(int *num_locais, int *num_veiculos, int *num_pedidos, 
	    Local *&locais, Veiculo *&veiculos, Pedido *&pedidos)
{
	FILE *arq;

	arq = fopen("Backup.bin", "wb");

	if (arq) {
		fwrite(num_locais, sizeof(int), 1, arq);
		fwrite(num_veiculos, sizeof(int), 1, arq);
		fwrite(num_pedidos, sizeof(int), 1, arq);

		fwrite(locais, sizeof(Local), *num_locais, arq);
		fwrite(veiculos, sizeof(Veiculo), *num_veiculos, arq);
		fwrite(pedidos, sizeof(Pedido), *num_pedidos, arq);

		fclose(arq);
	}
}

void restora(int *num_locais, int *num_veiculos, int *num_pedidos, 
	     Local *&locais, Veiculo *&veiculos, Pedido *&pedidos)
{
	FILE *arq;

	arq = fopen("Backup.bin", "rb");

	if (arq) {
		fread(num_locais, sizeof(int), 1, arq);
		fread(num_veiculos, sizeof(int), 1, arq);
		fread(num_pedidos, sizeof(int), 1, arq);
	
		locais = new Local[*num_locais];
		veiculos = new Veiculo[*num_veiculos];
		pedidos = new Pedido[*num_pedidos];

		fread(locais, sizeof(Local), *num_locais, arq);
		fread(veiculos, sizeof(Veiculo), *num_veiculos, arq);
		fread(pedidos, sizeof(Pedido), *num_pedidos, arq);
	}
}

/*Prototipo de listaLocais */

void listaLocais(int *num_locais, Local *&locais);

/*Calculos */

float calculaDistancia(float x1, float x2, float y1, float y2)
{
	float dis = std::sqrt((x2 - x1) * (x2 - x1) + (y2-y1) * (y2 - y1));
	
	return dis * 111.0;
}

int calculaVeiculoProximo(float x1, float y1, 
			  Veiculo *&veiculos, int *num_veiculos)
{
	int i, menor_distancia = 0;
	float dist_atual, dist_menor;

	for (i = 0; i < *num_veiculos; i++) {
		if(!veiculos[i].isDisponivel())
			continue;

		auto index_atual = veiculos[i].getPosicao();
		auto index_menor = veiculos[menor_distancia].getPosicao();

		dist_menor = calculaDistancia(x1, 
				index_menor.getX(), 
				y1, 
				index_menor.getY());

		dist_atual = calculaDistancia(x1, 
				index_atual.getX(), 
				y1, 
				index_atual.getY());

		if (dist_menor > dist_atual)
			menor_distancia=i;
	}

	return menor_distancia;
}

void simulaRota(float dis_total, int veiculo_index, int pedido_index, 
		Veiculo *&veiculos, Pedido *&pedidos)
{
	float cont = 0;

	while (cont < dis_total) {
		cont += 0.1;
		
		pedidos[pedido_index].setDistancia(cont);

		std::this_thread::sleep_for(std::chrono::milliseconds(850));
	}
	if(cont >= dis_total)
		veiculos[veiculo_index].setDisponivel(true);
}

/*Gera um Id de 4 digitos para a identificação única de um pedido. */

char *geraId(char id[TAM_ID])
{
	int i;

	for (i = 0; i < TAM_ID; i++)
		id[i] = 'A' + (std::rand() % 26);

	return id;
}

/*Reutilização de código */

void pausa()
{
	std::cout << "\n[Enter]...";
	std::cin.ignore();
	std::cin.get();
}

void limpaTela()
{
	std::system(LIMPA_TELA);
}

/*Insere dados a classe Local */

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

/*Insere dados a classe Veiculo */

void insereVeiculo(int veiculo_index, int *num_locais, 
		   Local *&locais, Veiculo *&veiculos)
{
	int local_index;
	char placa[TAM_PLACA], modelo[TAM];

	limpaTela();

	std::cout << "*Insira a placa: ";
	std::cin.ignore();
	std::cin.getline(placa, TAM_PLACA);

	std::cout << "*Insira o modelo: ";
	std::cin.getline(modelo, TAM);

	veiculos[veiculo_index].setVeiculo(placa, modelo);
	veiculos[veiculo_index].setDisponivel(true);

	/*Se não há locais cadastrados, sai da função */

	if (*num_locais <= 0)
		return;

	listaLocais(num_locais, locais);

	std::cout << "*Informe o indice de onde ele está localizado: ";
	std::cin >> local_index;
	
	veiculos[veiculo_index].setPosicao(locais[local_index]);
}

/*Insere dados a classe Pedido */

void inserePedido(int pedido_index, int *num_locais, 
		  Local *&locais, Pedido *&pedidos)
{
	int local_index;
	float peso;
	char id[TAM_ID];

	limpaTela();

	std::cout << "*Insira o peso: ";
	std::cin >> peso;

	pedidos[pedido_index].setPedido(geraId(id), peso);

	/*Se não há locais cadastrados, sai da função */

	if (*num_locais <= 0)
		return;

	listaLocais(num_locais, locais);

	std::cout << "*Informe o indice da origem: ";
	std::cin >> local_index;

	pedidos[pedido_index].setOrigem(locais[local_index]);

	std::cout << "*Informe o indice do destino: ";
	std::cin >> local_index;

	pedidos[pedido_index].setDestino(locais[local_index]);
}

/*Funções para CRUD de pedido */

void cadastraPedidos(int *num_locais, int *num_pedidos, 
		     Local *&locais, Pedido *&pedidos)
{
	int i;

	std::cout << "Quantos pedidos serão cadastrados? ";
	std::cin >> *num_pedidos;

	pedidos = new Pedido[*num_pedidos];

	for (i = 0; i < *num_pedidos; i++)
		inserePedido(i, num_locais, locais, pedidos);
}

void listaPedidos(int *num_pedidos, Pedido *&pedidos)
{
	int i;

	for (i = 0; i < *num_pedidos; i++) {
		std::cout << "Pedido [" << i << "]\n";
		std::cout << "- Id: " << pedidos[i].getId() << "\n";
		std::cout << "- Peso: " << pedidos[i].getPeso() << " Kg" 
			  << "\n";

		auto origem = pedidos[i].getOrigem();
		auto destino = pedidos[i].getDestino();

		std::cout << "- Origem: " << origem.getLocal() << ", " 
			  << origem.getX() << " " << origem.getY() << "\n";
		std::cout << "- Destino: " << destino.getLocal() << ", "
			  << destino.getX() << " " << destino.getY() << "\n";
		std::cout << "- Status: ";

		if (pedidos[i].isEnviado())
			std::cout << "Enviado (" 
				  << pedidos[i].getDistancia() 
				  << "Km percorridos)\n\n";
		else
			std::cout << "Pendente\n\n";
	}

	pausa();
}

void atualizaPedido(int *num_locais, int *num_pedidos, 
		    Local *&locais, Pedido *&pedidos)
{
	int pedido_index;

	listaPedidos(num_pedidos, pedidos);
	
	std::cout << "\nInsira o indice do pedido a ser atualizado: ";
	std::cin >> pedido_index;

	if (pedidos[pedido_index].isEnviado())
		return;

	inserePedido(pedido_index, num_locais, locais, pedidos);
}

void excluiPedidos(int *num_pedidos, Pedido *&pedidos)
{
	delete[] pedidos;
	pedidos = nullptr;
	*num_pedidos = 0;
}

void enviaPedido(int *num_locais, int *num_veiculos, int *num_pedidos, 
		 Local *&locais, Veiculo *&veiculos, Pedido *&pedidos)
{
	int pedido_index;

	listaPedidos(num_pedidos, pedidos);

	std::cout << "\nQual o indice do pedido que será enviado? ";
	std::cin >> pedido_index;

	if (pedidos[pedido_index].isEnviado())
		return;

	auto origem = pedidos[pedido_index].getOrigem();
	auto destino = pedidos[pedido_index].getDestino();

	int veiculo_index = calculaVeiculoProximo(origem.getX(), origem.getY(), 
					  veiculos, num_veiculos);

	if (!veiculos[veiculo_index].isDisponivel())
		return;

	auto local_veiculo = veiculos[veiculo_index].getPosicao();
	
	std::cout << "\n\n*Veiculo mais proximo disponivel: " 
	          << veiculos[veiculo_index].getPlaca() << ", "
		  << veiculos[veiculo_index].getModelo() << ", " 
	          << local_veiculo.getLocal() << ", " 
	          << local_veiculo.getX() << ", "
		  << local_veiculo.getY() << "\n";

	float dis_veiculo = calculaDistancia(origem.getX(), local_veiculo.getX(),
				origem.getY(), local_veiculo.getY());

	float dis_destino = calculaDistancia(origem.getX(), destino.getX(),
				origem.getY(), destino.getY());

	std::cout << "\nDistancia total: " 
		  << dis_veiculo+dis_destino << "\n";

	veiculos[veiculo_index].setDisponivel(false);
	pedidos[pedido_index].setEnviado(true);

	std::thread rotaThread ([=, &veiculos, &pedidos]() { 
		simulaRota(dis_veiculo+dis_destino, veiculo_index, 
	     pedido_index, veiculos, pedidos); 
	} );

	rotaThread.detach();

	pausa();
}
	
/*Funções para CRUD de Veiculo */

void cadastraVeiculos(int *num_locais, int *num_veiculos, 
		      Local *&locais, Veiculo *&veiculos)
{
	int i;

	std::cout << "Quantos veiculos serão cadastrados? ";
	std::cin >> *num_veiculos;

	/*Aloca dinamicamente um vetor de objetos de Veiculo */

	veiculos = new Veiculo[*num_veiculos];

	for (i = 0; i < *num_veiculos; i++)
		insereVeiculo(i, num_locais, locais, veiculos);
}

void listaVeiculos(int *num_veiculos, Veiculo *&veiculos)
{
	int i;

	for (i = 0; i < *num_veiculos; i++) {
		std::cout << "Veiculo [" << i << "]\n";
		std::cout << "- Placa: " << veiculos[i].getPlaca() << "\n";
		std::cout << "- Modelo: " << veiculos[i].getModelo() << "\n";

		auto posicao = veiculos[i].getPosicao();

		std::cout << "- Localização: " 
			  << posicao.getLocal() << ", "<< posicao.getX() << " "
			  << posicao.getY() << "\n";

		std::cout << "- Status: " 
			  << (veiculos[i].isDisponivel() ? "Disponivel\n\n" : "Ocupado\n\n");
	}

	pausa();
}

void atualizaVeiculo(int *num_locais, int *num_veiculos, 
		     Local *&locais, Veiculo *&veiculos)
{
	int veiculo_index;

	listaVeiculos(num_veiculos, veiculos);
	
	std::cout << "\nInsira o indice do veiculo a ser atualizado: ";
	std::cin >> veiculo_index;

	if (!veiculos[veiculo_index].isDisponivel())
		return;

	insereVeiculo(veiculo_index, num_locais, locais, veiculos);
}

void excluiVeiculos(int *num_veiculos, Veiculo *&veiculos) 
{
	delete[] veiculos;
	veiculos = nullptr;
	*num_veiculos = 0;
}

/*Funções para CRUD de Local */

void cadastraLocais(int *num_locais, Local *&locais)
{
	int i;

	std::cout << "Quantos locais serão cadastrados? ";
	std::cin >> *num_locais;

	/*Aloca dinâmaicamente um vetor de objetos de Local */ 

	locais = new Local[*num_locais];

	for (i = 0; i < *num_locais; i++)
		insereLocal(i, locais); 
}

void listaLocais(int *num_locais, Local *&locais)
{
	int i;

	for (i = 0; i < *num_locais; i++) {
		std::cout << "Local [" << i << "]\n";
		std::cout << "- Cidade: " << locais[i].getLocal() << "\n";
		std::cout << "- x: " << locais[i].getX();
		std::cout << " y: " << locais[i].getY() << "\n\n";
	}

	pausa();
}

void atualizaLocal(int *num_locais, Local *&locais)
{
	int local_index;

	listaLocais(num_locais, locais);

	std::cout << "\nInsira o indice do local a ser atualizado: ";
	std::cin >> local_index;

	insereLocal(local_index, locais); 
}
		
void excluiLocais(int *num_locais, Local *&locais)
{
	delete[] locais;
	locais = nullptr;
	*num_locais = 0;
}

#endif
