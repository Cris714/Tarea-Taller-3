#include <iostream>
#include <stack> // solo para mostrar los pisos

using namespace std;

// Declaración estructura BST

struct nodoBinario{
	int piso; // Variable donde se almacena el piso
	nodoBinario* izq;
	nodoBinario* der;
}; 

typedef struct nodoBinario nodoBST;


class BST{
  	private:
  		nodoBST *raiz;
        int n_pisos;
        int n_nodos;
  
  	public:
        int max_nodos;

  		BST(int m);
  
  		int buscaMayor();
  		int buscaMenor();
  		bool verifica(int piso);
  		void solicitaPisos(int q);

        void muestraPreOrden();
        void printPreorder(nodoBST *t);
};

// Definicion de métodos

BST::BST(int m){
    this->n_nodos = 0;
    this->max_nodos = 0;
    this->n_pisos = m;
    this->raiz = NULL; 
}

int BST::buscaMayor(){ // Sin recursividad, ya que se devuelve un entero
    if(this->raiz == nullptr)
        return this->n_pisos - 1;
    nodoBST *p = this->raiz;
    while(p->der != nullptr)
        p = p->der;
    return p->piso;
}

int BST::buscaMenor(){ // Similar a buscar mayor
    if(this->raiz == nullptr)
        return 0;

    nodoBST *p = this->raiz;
    while(p->izq != nullptr)
        p = p->izq;
    return p->piso;
}

bool BST::verifica(int piso){
    /* Búsqueda y eliminacion del nodo que tenga el valor piso, usar recursividad
    presenta resultados lentos*/

    if(this->raiz == nullptr)
        return false;

    nodoBST *p = this->raiz;
    nodoBST *q = p; // puntero al padre de p
    while(p != nullptr && p->piso != piso){
        q = p;
        if(p->piso < piso)
            p = p->der;
        else  
            p = p->izq;
    }

    if(p == nullptr)
        return false;
    
    // ELIMINACION
    this->n_nodos--;

    // intercambio de nodos, en caso que haya un hijo null
    if(p->izq == nullptr){
        if(this->raiz == p) this->raiz = p->der;
        else if(q->der == p) q->der = p->der;
        else q->izq = p->der;
        delete p;
        return true;
    }
    if(p->der == nullptr){
        if(this->raiz == p) this->raiz = p->izq;
        else if(q->der == p) q->der = p->izq;
        else q->izq = p->izq;
        delete p;
        return true;
    }

    // doble intercambio, en caso que no haya hijos null
    bool from_izq = (q->izq == p);
    bool from_root = (this->raiz == p);
    nodoBST *r = p; // puntero al padre de p
    // búsqueda del menor nodo mayor a q
    p = p->der;
    while(p->izq != nullptr){
        r = p;
        p = p->izq;
    }
    // reemplazamos el piso del nodo q por el del nodo p
    if(from_root) this->raiz->piso = p->piso;
    else if(from_izq) q->izq->piso = p->piso;
    else q->der->piso = p->piso;

    // eliminacion del menor nodo mayor a q, que siempre tiene hijo izq null
    if(r->der == p) r->der = p->der;
    else r->izq = p->der;
    delete p;
    return true;
}

void BST::solicitaPisos(int q){
    // Esta es la funcion que probablemente usa la mayor cantidad de procesamiento
    int nuevoPiso;
    nodoBST *p, *s;
    for(int i = 0; i < q; i++){
        nuevoPiso = rand()%(this->n_pisos);
        if(this->raiz == nullptr){
            if(this->n_nodos++ > this->max_nodos) this->max_nodos++;
            nodoBST *r = new nodoBST;
            r->piso = nuevoPiso;
            this->raiz = r;
            continue;
        }
        p = this->raiz;
        while(p != nullptr && p->piso != nuevoPiso){
            s = p; 
            if(p->piso < nuevoPiso)
                p = p->der;
            else
                p = p->izq;
        }
        if(p == nullptr){
            if(this->n_nodos++ > this->max_nodos) this->max_nodos++;
            nodoBST *r = new nodoBST;
            r->piso = nuevoPiso;
            r->izq = r->der = NULL;
            if(s->piso < nuevoPiso)
                s->der = r;
            else
                s->izq = r;                    
        }
    }
}

void BST::muestraPreOrden(){
    cout << "BST: ";
    stack<nodoBST> S;
    nodoBST p = *(this->raiz);
    S.push(p);
    while(!S.empty()){
        p = S.top();
        S.pop();
        cout << p.piso << " ";
        if(p.der != nullptr)
            S.push(*(p.der));
        if(p.izq != nullptr)
            S.push(*(p.izq));
    }
    cout << endl;
}
