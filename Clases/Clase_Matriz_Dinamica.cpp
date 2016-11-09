#include <iostream>
#include <cmath>

using namespace std;

class MatrizDinamica {
private:
	int num_filas;
	int num_columnas;
	double **md;
	
public:
	MatrizDinamica(int filas = 0, int columnas = 0, double valor = 0);
	~MatrizDinamica();
	inline int Filas() const;
	inline int Columnas() const;
	inline double Elemento(int fila, int columna) const;
	void Modifica(int fila, int columna, double nuevo);
	void AniadeFila(double v[], int util_v);
	void AniadeColumna(double v[], int util_v);
};

MatrizDinamica::MatrizDinamica(int filas, int columnas, double valor)
:num_filas(filas), num_columnas(columnas)
{
	if (filas != 0 && columnas != 0) {
		m = new *double[filas];
		for (int i=0; i<columnas; i++)
			m[i] = new double[columnas];
			
		for (int j=0; j<num_filas; j++)
			for (int k=0; k<num_columnas; k++)
					m[j][k] = valor;
	}

}

MatrizDinamica::~MatrizDinamica() {
	for (int i=0; i<num_filas; i++)
		delete [] m[i];
		
	delete [] m;
}

inline int MatrizDinamica:Filas() const {
	return num_filas;
}

inline int MatrizDinamica:Columnas() const {
	return num_columnas;
}

double Elemento (int fila, int columna) const {
	if (fila <= num_filas && columnas <= num_columnas)
		return m[fila][columna];
}
