#include <map>
#include <iostream>

using namespace std;

class Mapa{
	private:
  		map<int, bool> contenedor;
        int n_pisos;
  
	public:
  		Mapa(int m);
  		
        int buscaMayor();
  		int buscaMenor();
  		bool verifica(int piso);
  		void solicitaPisos(int q); 
        void muestra(); 
};

Mapa::Mapa(int m){
    this->n_pisos = m;
    for(int i = 0; i < m; i++)
        (this->contenedor)[i] = false;
}

int Mapa::buscaMayor(){
    int c = this->n_pisos;
    while(!(this->contenedor)[--c] && c >= 0);
    if(c >= 0)
        return c;
    return this->n_pisos - 1;
}

int Mapa::buscaMenor(){
    int c = -1;
    while(!(this->contenedor)[++c] && c < this->n_pisos);
    if(c >= 0)
        return c;
    return 0;
}

bool Mapa::verifica(int piso){
    if((this->contenedor)[piso]){
        (this->contenedor)[piso] = false;
        return true;
    }
    return false;
}

void Mapa::solicitaPisos(int q){
    for(int i = 0; i < q; i++)
        (this->contenedor)[rand()%(this->n_pisos)] = true;
}

void Mapa::muestra(){
    for(int i = 0; i < this->n_pisos; i++)
        cout << (this->contenedor)[i] << " ";
    cout << endl;
}