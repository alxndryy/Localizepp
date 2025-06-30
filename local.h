#ifndef LOCAL_H
#define LOCAL_H

class Local 
{
private:
	/*Atributos */

	char cidade[TAM];
	float coord_x;
	float coord_y;
public:
	/*Construtor padrão */

	Local()
	{
		strcpy(cidade, "VAZIO");
		coord_x=coord_y=0.0;
	}

	//~Local() {/*Destrutor */}

	/*Setters */

	void setLocal(char nv_cidade[TAM], float nv_x, float nv_y)
	{
		if (strlen(nv_cidade)<=TAM)
			strcpy(cidade, nv_cidade);

		coord_x=nv_x;
		coord_y=nv_y;
	}

	/*Getters */

	char *getLocal() { return cidade; }
	float getX() { return coord_x; }
	float getY() { return coord_y; }
};

#endif
