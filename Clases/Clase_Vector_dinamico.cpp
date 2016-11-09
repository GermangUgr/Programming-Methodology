#include <iostream>
#include <cmath>

using namespace std;
//Implementacion de la clase vector dinamico
class VectorDinamico {
private:
	int tamanio_fisico;
	int tamanio_logico;
	double *vd;
	
public:
	VectorDinamico(int num_casillas = 0, double dato = 0);
	~VectorDinamico();
	inline  int TamanioLogico() const;
	inline int TamanioFisico() const;
	inline double Elemento(int i) const;
	void Modifica(int indice, double nuevo);
	void Aumenta(int num_nuevos);
	
};

/*
Los siguientes tres constructores pueden ser implementados en uno solo utilizando valores
por defecto con la siguinte cabecera: VectorDinamico(int num_casillas = 0, double dato = 0)

VectorDinamico::VectorDinamico()
:tamanio_fisico(0), tamanio_logico(0), vd(0) {};

VectorDinamico::VectorDinamico(int num_casillas) 
:tamanio_fisico(num_casillas), tamanio_logico(num_casillas)
{
	vd = new double[num_casillas];
	
	for (int i=0; i<tamanio_logico; i++)
		vd[i] = 0;
};

VectorDinamico::VectorDinamico(int num_casillas, double dato) 
:tamanio_fisico(num_casillas), tamanio_logico(num_casillas)
{
	vd = new double[num_casillas];

	for (int i=0; i<tamanio_logico; i++)
		vd[i] = dato;
}
*/

VectorDinamico::VectorDinamico(int num_casillas, double dato)
:tamanio_fisico(num_casillas), tamanio_logico(num_casillas) 
{
	if (num_casillas == 0)
		vd = 0;
	else {
		vd = new double[num_casillas];
		
		for (int i=0; i<tamanio_logico; i++)
			vd[i] = dato;
	}		
}

VectorDinamico::~VectorDinamico() {
	delete [] vd;
}

inline int VectorDinamico::TamanioLogico() const {
	return tamanio_logico;
}

inline int VectorDinamico::TamanioFisico() const {
	return tamanio_fisico;
}

inline double VectorDinamico::Elemento(int i) const {
	return vd[i];
}

void VectorDinamico::Modifica(int indice, double nuevo) {
	if (indice <= tamanio_logico)
		vd[indice] = nuevo;
}

void VectorDinamico::Aumenta(int num_nuevos) {
	
	double *aux = new double[tamanio_fisico + num_nuevos];
	
	for (int i=0; i<tamanio_fisico; i++) {
		if (i <= tamanio_fisico)
			aux[i] = vd[i];
		else
			aux[i] = 0;
	}
		
	delete [] vd;
	vd = aux;
	tamanio_fisico += num_nuevos;
}

int main () {
	system("pause");
}
