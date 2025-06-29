/*3. Cadastro de Pedidos:
○ Atributos: Identificador único, local de origem (referência a um Local
cadastrado), destino (referência a um Local cadastrado), peso do item (em kg).
○ Operações: Permitir a criação, listagem, atualização e exclusão de pedidos. */
#ifndef PEDIDO_H
#define PEDIDO_H

#include "local.h"

class Pedido
{
private:
	/*Atributos */

	char id[TAM_ID];
	float peso;
	Local origem;
	Local destino;
public:
	/*Construtor padrão */

	Pedido()
	{
		strcpy(id, "VAZIO");
		peso=0.0;
	}

	//~Pedido(){/*Destrutor */}

	/*Setters */

	void setPedido(char nv_id[TAM_ID], float nv_peso)
	{
		strcpy(id, nv_id);

		peso=nv_peso;
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

	char *getId(){ return id; }
	float getPeso(){ return peso; }
	Local getOrigem(){ return origem; }
	Local getDestino(){ return destino; }
};

#endif		
