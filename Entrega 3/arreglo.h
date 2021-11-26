#include <iostream>

using namespace std;

// Declaración estructura arreglo

class Arreglo{ 
  	private:
  		bool *A; //Puntero hacia booleano, apuntara al inicio del arreglo 
  		int n_pisos; // m
  
  	public:
  		Arreglo(int m); // Constructor
  
  		int buscaMayor(); // Metodo que busca el piso mas alto solicitado
      	int buscaMenor(); // Metodo que busca el piso mas bajo solicitado
  		bool verifica(int piso); // Verifica si el piso está solicitado
  		void solicitaPisos(int q); // añade q nuevos pisos al arreglo
        void muestra(); // SOLO DEPURACION
};


// Definición de métodos

Arreglo::Arreglo(int m){
    (this->A) = new bool[m];
    this->n_pisos = m;
    for(int i = 0; i < m; i++){
        (this->A)[i] = false;
    }
}

int Arreglo::buscaMayor(){
    int c = this->n_pisos;
    while(!(this->A)[--c] && c >= 0); // Busca el primer true desde el final del arreglo
    if(c >= 0) 
        return c;
    return this->n_pisos-1; // no hay pisos requeridos, el ascensor sube al ultimo piso
}

int Arreglo::buscaMenor(){
    int c = -1;
    while(!(this->A)[++c] && c < this->n_pisos);
    if(c < this->n_pisos)
        return c;
    return 0; // no hay pisos requeridos, el ascensor baja al piso 0
}

bool Arreglo::verifica(int piso){
    if((this->A)[piso]){
        (this->A)[piso] = false;
        return true;
    }
    return false;
}

void Arreglo::solicitaPisos(int q){
    for(int i = 0; i < q; i++)
        A[rand()%(this->n_pisos)] = true; 
}

void Arreglo::muestra(){
    for(int i = 0; i < this->n_pisos; i++)
        cout << (this->A)[i] << " ";
    cout << endl;
}
