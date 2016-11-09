#include <iostream>
#include <cmath>

using namespace std;
typedef double TIPO;

struct Celda {
	TIPO info;
	Celda *sig;
};

class Lista {
private:
	Celda *l;
	int num_celdas;
	bool Vacia();
	
public:
	Lista();
	~Lista();
	inline int NumElementos() const;
	inline int Elemento(int posicion) const;
	void Modifica(int posicion, TIPO info);
	void PushFirst(TIPO info);
	void Inserta(int posicion, TIPO info);
	void PushLast(TIPO info);
	void Elimina(int posicion);
	
};

int main () {
	system("pause");
}

Lista::Lista()
:l(0) {}

Lista::~Lista() {
	while (!Vacia())
		Elimina(1);
}

bool Lista::Vacia() {
	return l == 0;
}

inline int Lista::NumElementos() const {
	return num_celdas;
}

inline int Lista::Elemento(int posicion) const {
	int i = 1;
	Celda *p = l;
	
	while (p->sig != 0 && i<=posicion) {
		p = p->sig;
		i++;
	}
	
	return i;
}

void Lista::Modifica(int posicion, TIPO info) {
	int i = 1;
	Celda *p = l;
	
	while (p->sig != 0 && i <= posicion) {
		p = p->sig;
		i++;
	}
	
	p->info = info;
}

void Lista::PushFirst(TIPO info) {
	Celda *nuevo = new Celda;
	
	if (!Vacia()) {
		nuevo->info = info;
		nuevo->sig = l;
		l = nuevo;
	} else {
		l = nuevo;
		nuevo->sig = 0;
	}

}

void Lista::PushLast(TIPO info) {
	Celda *nuevo = new Celda;
	Celda *p = l;
	
	if (!Vacia()) {
		while(p->sig != 0)
			p = p->sig;
		
		p->sig = nuevo;
		nuevo->sig = 0;
	} else {
		l = nuevo;
		nuevo->sig = 0;
	}
}

void Lista::Inserta(int posicion, TIPO info) {
	Celda *nuevo = new Celda;
	Celda *p = l;
	int i = 1;
	
	if (!Vacia()) {
		while (p->sig != 0 && i <= posicion) {
			p = p->sig;
			i++;
		}
		
		nuevo->info = info;
		nuevo->sig = p->sig;
		p->sig = nuevo;
	}
}

void Lista::Elimina(int posicion) {
	Celda *anterior = l, *siguiente, *aux;
	int i = 1;
	
	if (!Vacia()) {
		while(anterior->sig != 0 && i <= posicion-1) {
			anterior = anterior->sig;
			i++;
		}
		
		aux = anterior->sig;
		siguiente = aux->sig;
		
		anterior->sig = siguiente;
		delete aux;
	}
}
