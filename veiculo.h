/*2. Cadastro de Veículos:
○ Atributos: Placa (identificador único), modelo, status (disponível ou ocupado),
local atual (referência a um Local cadastrado, representando a posição do
veículo).
○ Operações: Permitir a criação, listagem, atualização e exclusão de veículos. A
atualização do status e do local atual será fundamental durante o
processo de entrega.*/
#ifndef VEICULO_H
#define VEICULO_H

#include "local.h"

class Veiculo
{
private:
	/*Atributos */

	char placa[TAM_PLACA];
	char modelo[TAM];
	bool disponivel;
	Local posicao;
public:
	/*Construtor padrão */

	Veiculo()
	{
		strcpy(placa, "XXX-XXX");
		strcpy(modelo, "VAZIO");
	}

	//~Veiculo(){/*Destrutor */}

	/*Setters */

	void setVeiculo(char nv_placa[TAM_PLACA], char nv_modelo[TAM])
	{
		strcpy(placa, nv_placa);

		strcpy(modelo, nv_modelo);
	}

	void setPosicao(Local nv_posicao)
	{
		posicao=nv_posicao;
	}

	void setDisponivel(bool status)
	{
		disponivel=status;
	}

	/*Getters */

	char *getPlaca(){ return placa; }
	char *getModelo(){ return modelo; }
	bool isDisponivel(){ return disponivel; }
	Local getPosicao(){ return posicao; }
};

#endif
