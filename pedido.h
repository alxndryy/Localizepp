#ifndef PEDIDO_H
#define PEDIDO_H

#include "local.h"

class Pedido
{
private:
	char id[TAM_ID];
	float peso;
	float dis_percorrida;
	bool enviado;
	Local origem;
	Local destino;
public:
	/*Construtor padrão */

	Pedido()
	{
		strcpy(id, "VAZIO");
		peso=0.0;
		enviado=false;
	}

	//~Pedido(){/*Destrutor */}

	/*Setters */

	void setPedido(char nv_id[TAM_ID], float nv_peso)
	{
		strcpy(id, nv_id);

		peso=nv_peso;
	}

	void setDistancia(float nv_dis)
	{
		dis_percorrida=nv_dis;
	}

	void setEnviado(bool status)
	{
		enviado=status;
	}

	void setOrigem(Local nv_origem)
	{
		origem=nv_origem;
	}

	void setDestino(Local nv_destino)
	{
		destino=nv_destino;
	}

	/*Getters */

	char *getId() { return id; }
	float getPeso() { return peso; }
	float getDistancia() { return dis_percorrida; }
	bool isEnviado() { return enviado; } 
	Local getOrigem() { return origem; }
	Local getDestino() { return destino; }
};

#endif		
