#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stdexcept>
#include<string>
#include<sstream>
#include<fstream>

///////////////////////////////////////////
//                                       //
//        German Gonzalez Almagro        //
//                                       //
/////////////////////////////////////////// 

using namespace std;
typedef int TipoBase;

//////////////////
//Clase Conjunto//
//////////////////
class Conjunto {
private:
	TipoBase *conjunto;
	int num_elementos;
	int tamanio_fisico;
	
	//Metodos privados
	void AumentaVector(int num_nuevos);
	void Ordena();
	void EliminaRepetidos();
	int PrimeraOcurrenciaEntre(int pos1, int pos2, TipoBase dato) const;

public:
	//Constructores Simples
	Conjunto();
	//Constructor de copia
	Conjunto(const Conjunto &a_copiar);
	//Destructor
	~Conjunto();
	//Metodos Publicos
	bool Vacio();
	TipoBase GetElemento(int indice);
	int Cardinal();
	bool Pertenece(TipoBase elemento) const;
	void Borrar();
	
	//Sobrecarga de operadores binarios
	Conjunto& operator =(const Conjunto &a_copiar);
	Conjunto operator *(const Conjunto &otro);
	bool operator ==(const Conjunto &a_comparar); 
	bool operator !=(const Conjunto &a_comparar);

	//Sobrecarga con funciones amigas
	friend istream& operator>>(istream &is, Conjunto &conjunto);
	friend ostream& operator<<(ostream &os, const Conjunto &conjunto);

};

//Genera un numero aleatorio comprendido entre 1 y "tope"
int NumeroAleatorio (const int tope) {
	if (tope > 0) {
		srand(time(NULL));
		return 1+rand()%(tope);
	}
	else {
		throw logic_error ("No se permite generar numeros aleatorios menores que 0");
	}
}

void Redimensiona(Conjunto* &vector_S, int &tamanio, const int num_nuevas = 5) {
	Conjunto *temporal = new Conjunto[tamanio + num_nuevas];
	
	for (int i=0; i<tamanio; i++) 
		temporal[i] = vector_S[i];
	
	tamanio += num_nuevas;
	delete[] vector_S;
	vector_S = temporal;
}

//Devuelve true en caso de que dato se encuentre en vector,
//false en otro caso
bool Pertenece(int dato, int *vector, int util) {
	bool pertenece = false;
	
	for (int i=0; i<util; i++)
		if (vector[i] == dato)
			pertenece = true;
	
	return pertenece;
}

int main (int argc, char **argv) {
	
	if (argc != 4) {
		cout << "Numero de argumentos incorrecto: " << endl;
		cout << "Uso: ./constructivo <k> <fich-entrada> <fich-salida>" << endl;
	}
	
	int k;
	k = atoi(argv[1]);

	//Declaro el conjunto base y el conjunto solucion
	//Base:
	Conjunto *vector_S = new Conjunto[5];
	int util_S = 0, tamanio_S = 5;
	//Solucion:
	Conjunto *vector_Sol = new Conjunto[k];
	int util_Sol = 0, tamanio_Sol = k;
	//Declaro un vector auxiliar para gestionar el
	//borrado de las componentes de vector_S ya procesadas
	int *procesados = new int[k];
	int util_p = 0, tamanio_p = k;
	
	//Leo la instancia y declaro un vector de conjuntos que la almacena
	ifstream fi;
	Conjunto conjunto;
	int i = 0;
	
	fi.open(argv[2]);
	if (!fi) {
		cout << "Error: no se pudo abrir el fichero\n";
		exit(1);
	}
	
	cout << "Lectura de la instancia: \n\n";
	
	while (!fi.eof()) {
		if (tamanio_S == util_S)
			Redimensiona(vector_S,tamanio_S);
			
		fi >> conjunto;
		vector_S[i] = conjunto;
		conjunto.Borrar();
		i++;
		util_S++;
	}
	
	fi.close();
	
	try{
		
		//Busco el mayor cardinal dentro del vector_S y cuento el numero
		//de conjuntos con este cardinal
		int max_cardinal1;
		int num_max_cardinal1 = 0;
	
		max_cardinal1 = vector_S[0].Cardinal();
		for (int i=1; i<util_S; i++) {
			if (vector_S[i].Cardinal()>max_cardinal1) {
				max_cardinal1 = vector_S[i].Cardinal();
				num_max_cardinal1 = 1;
			}
			else if(vector_S[i].Cardinal()==max_cardinal1)
			 	num_max_cardinal1++;
			
		}
	
		//De entre los conjuntos con mayor cardinal seleccion uno de forma aleatoria
		int aleatorio1;
	
		aleatorio1 = NumeroAleatorio(num_max_cardinal1);
		for (int i=0; i<util_S; i++) 
			if (vector_S[i].Cardinal() == max_cardinal1) {
				if(aleatorio1 == 1) {
					vector_Sol[0] = vector_S[i];
					util_Sol++;
					procesados[0] = i;
					util_p++;
				}
				aleatorio1--;	
			}
			
		cout << "Ejecucion del greedy: \n";
	
		////Algoritmo principal (greedy)////
		int max_card_inter, aleatorio2;
		int num_max_cardinal2;
		bool aniadido;
		Conjunto interseccion_Sol;
		interseccion_Sol = vector_Sol[0];

		for (int i=1; i<k; i++) {
			cout << "La nueva interseccion es: ";
			interseccion_Sol = interseccion_Sol*vector_Sol[util_Sol-1];
			cout << interseccion_Sol << "\n\n";
			num_max_cardinal2 = 0;
			max_card_inter = 0;
		
			//Busco el maximo cardinal de intersecciones (max_card_inter)
			//Cuento el numero de intersecciones con esta (maxima) intereccion (num_max_cardinal2)
			for (int j=0; j<util_S; j++) 
				if (!Pertenece(j,procesados,util_p)) {
					if((interseccion_Sol*vector_S[j]).Cardinal() > max_card_inter) {
						max_card_inter = (interseccion_Sol*vector_S[j]).Cardinal();
						num_max_cardinal2 = 1;
					}
					else if ((interseccion_Sol*vector_S[j]).Cardinal() == max_card_inter)
						num_max_cardinal2++;	
				}
		
			//De entre los conjuntos con mayor interseccion con interseccion_Sol
			//selecciono uno aleatoriamente y lo añado a vector_Sol
			aleatorio2 = NumeroAleatorio(num_max_cardinal2);
			cout << "Numero aleatorio: " << aleatorio2 << endl;
			aniadido = false;
			for (int r=0; r<util_S && !aniadido; r++) 
				if(!Pertenece(r,procesados,util_p))
					if ((interseccion_Sol*vector_S[r]).Cardinal() == max_card_inter) {
						if(aleatorio2 == 1) {
							vector_Sol[util_Sol] = vector_S[r];
							util_Sol++;
							procesados[util_p] = r;
							util_p++;
							aniadido = true;
						}
						else
							aleatorio2--;	
					}
		}
	} 
	catch(logic_error excepcion) {
		cout << "Error Logico: " << excepcion.what() << "\n\n";
	}
	
	ofstream fo;
	fo.open(argv[3]);	
	
	for (int i=0; i<util_Sol; i++) {
		fo << vector_Sol[i] << "\n";
	}
	
	fo.close();
	
	cout <<"\n\nConjuntos ordenados y sin repetidos: \n";
	

	for (int i=0; i<util_S; i++) {
		cout << vector_S[i] << "--->" << vector_S[i].Cardinal() << endl;
	}
	cout <<"Numero total de conjuntos: " << util_S << "\n\n";
		
	cout << "\n\n";
}

////////////////////////////////////////////////////////
//Metodos Privados para modificar el tamaño del vector//
//      Eiliminar Repetidos, Ordenar y borrar         //
////////////////////////////////////////////////////////

void Conjunto::AumentaVector(int num_nuevos = 10) {
	if (num_nuevos >= 0) {

	  TipoBase *temporal = new TipoBase[tamanio_fisico + num_nuevos];
	
		for (int i=0; i<num_elementos; i++) 
			 temporal[i] = conjunto[i];
		
		if (tamanio_fisico != 0)	
			delete [] conjunto;
		
		conjunto = temporal;
		tamanio_fisico += num_nuevos;
	}
	else {
		throw logic_error("No se pudo modificar el vector (aumento negativo)");
	}
}

void Conjunto:: Borrar() {
	if (tamanio_fisico != 0)
		delete [] conjunto;
		
	num_elementos = 0;
	tamanio_fisico = 0;
}

int Conjunto::PrimeraOcurrenciaEntre(int pos1, int pos2, TipoBase dato) const {
	int i = pos1; 
	bool encontrado = false;

	while (i <= pos2  &&  !encontrado)
		if (conjunto[i] == dato)
			encontrado = true;
		else
			i++;

	if (encontrado)
		return i;
	else
		return -1;	
}

void Conjunto:: EliminaRepetidos() {
	int pos_escritura, pos_lectura;
	int pos_encontrado;

	if (num_elementos > 0){
		pos_escritura = 1;

		for(pos_lectura = 1; pos_lectura < num_elementos; pos_lectura++){
			pos_encontrado = PrimeraOcurrenciaEntre(0, pos_escritura-1, conjunto[pos_lectura]);

			if (pos_encontrado == -1){      
				conjunto[pos_escritura] = conjunto[pos_lectura];
				pos_escritura++;
			}
		}
		num_elementos = pos_escritura;
	}
}

void Conjunto::Ordena() {
	int izquierda, i;
	TipoBase a_desplazar;
	
	for (izquierda = 1; izquierda < num_elementos; izquierda++) {
		a_desplazar = conjunto[izquierda];
		
		for (i = izquierda; i>0 && a_desplazar < conjunto[i-1]; i--)
			 conjunto[i] = conjunto[i-1];
			 
		conjunto[i] = a_desplazar;	 
	}
}

//////////////////////////////
//Constructores y Destructor//
//////////////////////////////

Conjunto::Conjunto(): num_elementos(0), tamanio_fisico(0){};

Conjunto::Conjunto(const Conjunto &a_copiar) {
	AumentaVector(a_copiar.num_elementos);
	for (int i=0; i<tamanio_fisico; i++)
		conjunto[i] = a_copiar.conjunto[i];
}

Conjunto::~Conjunto() {
	if (tamanio_fisico != 0)
		delete [] conjunto;

	tamanio_fisico = 0;
	num_elementos = 0;
}

////////////////////
//Metodos Publicos//
////////////////////

bool Conjunto::Vacio() {
	return num_elementos == 0;
}

int Conjunto::Cardinal() {
	return num_elementos;
}

TipoBase Conjunto::GetElemento(int indice) {
	if (indice < num_elementos)	
		return conjunto[indice];
}

bool Conjunto::Pertenece(TipoBase elemento) const {
	return PrimeraOcurrenciaEntre(0,num_elementos-1,elemento) != -1;
}

//////////////////////////////////////
//Sobrecarga de operadores (metodos)//
//////////////////////////////////////
Conjunto& Conjunto::operator=(const Conjunto &a_copiar) {
	if ( this != &a_copiar) {
		Borrar();
		AumentaVector(a_copiar.num_elementos);
		for (int i=0; i<tamanio_fisico; i++)
			conjunto[i] = a_copiar.conjunto[i];
	}
	num_elementos = a_copiar.num_elementos;
	tamanio_fisico = a_copiar.num_elementos;
	return (*this);
}

Conjunto Conjunto::operator*(const Conjunto &otro) {
	Conjunto interseccion;
	int j=0;
	
	for (int i=0; i<num_elementos; i++) {
		if (interseccion.num_elementos == interseccion.tamanio_fisico)
			interseccion.AumentaVector();
		
		if (otro.Pertenece(this->conjunto[i] ) )     {
			interseccion.conjunto[j] = conjunto[i];
			interseccion.num_elementos++;
			j++;
		}
	}
	
	return interseccion;
	
}

bool Conjunto::operator ==(const Conjunto &a_comparar) {
	bool son_iguales = true;
	if (this != &a_comparar) {
		if (num_elementos != a_comparar.num_elementos)
			son_iguales = false;
		else {
			for (int i=0; i<num_elementos && son_iguales; i++){
				if (conjunto[i] != a_comparar.conjunto[i])
					son_iguales = false;
			}
		}
	}
	else
		son_iguales = false;
		
	return son_iguales;
}

bool Conjunto::operator !=(const Conjunto &a_comparar) {
	return !(*this == a_comparar);
}

///////////////////////////////////////////////
//Sobrecarga de Operadores (Funciones amigas)//
///////////////////////////////////////////////

istream& operator>>(istream &is, Conjunto &conjunto1) {
	
	string cad;
	istringstream iss;
	int x;
	
	getline(is, cad);
	iss.str(cad);
	iss.clear();
	
	cout << "--------------------------------------------"<<endl;
	while(iss >> x) {
		if (conjunto1.num_elementos == conjunto1.tamanio_fisico)
			conjunto1.AumentaVector();	
			
		conjunto1.conjunto[conjunto1.num_elementos] = x;
		conjunto1.num_elementos++;
	}
	
	cout << conjunto1 << "--->" << conjunto1.num_elementos << endl;

	conjunto1.EliminaRepetidos();
	conjunto1.Ordena();
	return is;
}

ostream& operator<<(ostream &os, const Conjunto &conjunto1) {
	
	for (int i=0; i<conjunto1.num_elementos; i++)
		os << conjunto1.conjunto[i] << " ";
		
	return os;
}

