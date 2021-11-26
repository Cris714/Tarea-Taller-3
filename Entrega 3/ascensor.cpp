#include <iostream>	
#include <ctime>

#include "mapa.h"
#include "arreglo.h"
#include "BST.h"

using namespace std;


void ascensorArreglo(Arreglo &arreglo, int n, int k);
void ascensorBST(BST &bst, int n, int k);
void ascensorMapa(Mapa &mapa, int n, int k);


int main(int argc, char **argv){
	if(argc != 4){
		cout << "Debe ejecutar el programa como ./problema n m k" << endl;
		exit(EXIT_FAILURE);
	}  

  	int n=atoi(argv[1]);
  	int m=atoi(argv[2]);
  	int k=atoi(argv[3]);

  	while(k>m && k<=0){//*al inicio* k requerimientos aleatorios en el rango de [1...m] 
		cout << "K tiene que ser menor o igual a " << m << endl;
  	    cout << "Ingrese K valido:";
        cin >> k;
    }

    clock_t t, h, j;

    cout << " - Inicializando estructuras..." << endl;
    Arreglo arreglo(m);
    BST bst(m);
    Mapa mapa(m);

    cout << "1) Experimento utilizando un arreglo..." << endl;
    t = clock(); 
    ascensorArreglo(arreglo, n, k);
    cout << "TIEMPO TRANSCURRIDO: " << float(clock()-t)/CLOCKS_PER_SEC << " s" << endl;
    cout << "MEMORIA UTILIZADA: " << sizeof(bool)*m << " bytes" << endl << endl;

    cout << "2) Experimento utilizando un BST..." << endl;
    h = clock();
    ascensorBST(bst, n, k);
    cout << "TIEMPO TRANSCURRIDO: " << float(clock()-h)/CLOCKS_PER_SEC << " s" << endl;
    cout << "MEMORIA UTILIZADA: " << (sizeof(int) + 2*sizeof(nodoBST*)) * bst.max_nodos << " bytes" << endl << endl;

    cout << "3) Experimento utilizando std::map..." << endl;
    j = clock();
    ascensorMapa(mapa, n, k);
    cout << "TIEMPO TRANSCURRIDO: " << float(clock() - j)/CLOCKS_PER_SEC << " s" << endl;
    cout << "MEMORIA UTILIZADA: " << (sizeof(int) + sizeof(bool) + sizeof(_Rb_tree_node_base))*m << " bytes" << endl << endl;
  
    return EXIT_SUCCESS;
}



void ascensorArreglo(Arreglo &arreglo, int n, int k){
    // El ascensor comienza subiendo desde el piso 0
    int up, down, q, piso = 0;
    bool direccion = true; // true: sube | false: baja <- funcionalidades del ascensor

    arreglo.solicitaPisos(k); // solicita los k pisos iniciales
    //arreglo.muestra();
    up = arreglo.buscaMayor();
    down = -1; // piso invalido
    //cout << "Piso mayor: " << up << endl;

    for(int iter = 0; iter < n; iter++){
        //if(iter%10000 == 0) cout << "ITER " << iter << endl;
        //cout << "Piso " << piso << endl;
        if(arreglo.verifica(piso)){
            //cout << "El piso " << piso << " fue solicitado y eliminado" << endl;
            //arreglo.muestra();
        }
        q = rand()%(k+1); // Genera 0 <= q <= k nuevos requerimientos
        arreglo.solicitaPisos(q);
        //cout << q << " nuevos pisos solicitados" << endl;
        //arreglo.muestra();

        if(piso == up && direccion){ // se llego al piso mas alto solicitado up
            down = arreglo.buscaMenor();
            //cout << "Piso menor: " << down << endl;
            direccion = !direccion;
        }
        else if(piso == down && !direccion){// se llego al piso mas bajo solicitado down
            up = arreglo.buscaMayor();
            //cout << "Piso mayor: " << up << endl;
            direccion = !direccion;
        }
        direccion? piso++ : piso--; // iteracion completa: sube o baja dependiendo de su direccion
    }
}


void ascensorBST(BST &bst, int n, int k){
    // El ascensor comienza subiendo desde el piso 0
    int up, down, q, piso = 0;
    bool direccion = true; // true: sube | false: baja <- funcionalidades del ascensor

    bst.solicitaPisos(k); // solicita los k pisos iniciales
    //bst.muestraPreOrden();
    up = bst.buscaMayor();
    down = -1; // piso invalido
    //cout << "Piso mayor: " << up << endl;

    for(int iter = 0; iter < n; iter++){
        cout << "\r" << "["<< iter << " / " << n << "]";
        //if(iter%10000 == 0) cout << "ITER " << iter << endl;
        //cout << "Piso " << piso << endl;
        if(bst.verifica(piso)){
            //cout << "El piso " << piso << " fue solicitado y eliminado" << endl;
            //bst.muestraPreOrden();
        }
        q = rand()%(k+1); // Genera 0 <= q <= k nuevos requerimientos
        bst.solicitaPisos(q);
        //cout << q << " nuevos pisos solicitados" << endl;
        //bst.muestraPreOrden();

        if(piso == up && direccion){ // se llego al piso mas alto solicitado up
            down = bst.buscaMenor();
            //cout << "Piso menor: " << down << endl;
            direccion = !direccion;
        }
        else if(piso == down && !direccion){// se llego al piso mas bajo solicitado down
            up = bst.buscaMayor();
            //cout << "Piso mayor: " << up << endl;
            direccion = !direccion;
        }
        direccion? piso++ : piso--; // iteracion completa: sube o baja dependiendo de su direccion
    }
    cout << endl;
}

void ascensorMapa(Mapa &mapa, int n, int k){
    int up, down, q, piso = 0;
    bool direccion = true;

    mapa.solicitaPisos(k);
    up = mapa.buscaMayor();
    down = -1;

    for(int iter = 0; iter < n; iter++){
        cout << "\r" << "["<< iter << " / " << n << "]";
        mapa.verifica(piso);

        q = rand()%(k+1);
        mapa.solicitaPisos(q);

        if(piso == up && direccion){ 
            down = mapa.buscaMenor();
            direccion = !direccion;
        }
        else if(piso == down && !direccion){
            up = mapa.buscaMayor();
            direccion = !direccion;
        }
        
        direccion? piso++ : piso--;
    }
    cout << endl;
}

