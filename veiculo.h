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
