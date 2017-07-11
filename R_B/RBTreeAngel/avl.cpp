#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
using namespace std;

template <typename T>
class Node {
public:
    T val;
    Node *nodes[2];
    int  altura;
    Node() {
	nodes[0] = nodes[1] = nullptr;
	altura = 1;
    }
    Node(T x) {
        val = x;
	nodes[0] = nodes[1] = nullptr;
	altura = 1;
    }
};

template <typename T>
class AVLTree {
private:
    Node<T> *raiz;
public:
    typedef pair<Node<T>**, bool> pairPtrLado;
    AVLTree();
    //~AVLTree();
    bool find(T x, Node<T> **&ptr, stack<pairPtrLado> &camino);
    bool insert(T x);
    bool remove(T x);
    void print(int orden[3]);
    void recorrido(Node<T> *ptr, int orden[3]);
    void printAmplitud();
    void printBonito();

    int difAltura(Node<T>* nodo);
    void balanceo(stack<pairPtrLado > &camino);
    void cambioLRyRL(pairPtrLado hijo, pairPtrLado &padre, pairPtrLado abuelo);
    void cambioLLyRR(pairPtrLado padre, pairPtrLado abuelo);
       
    int size(Node<T> *ptr);
    int size();
};


template <typename T>
AVLTree<T>::AVLTree() {
    raiz = nullptr;
}

template<typename T>
bool AVLTree<T>::find(T x, Node<T>** &ptr, stack<pairPtrLado> &camino){
    ptr = &raiz;
    bool lrPos = 0;
    camino.push(make_pair(ptr, lrPos));
    while(*ptr and (*ptr)->val != x){
	lrPos = (*ptr)->val < x;
	ptr = &((*ptr)->nodes[lrPos]);
	camino.push(make_pair(ptr, lrPos));
    }
    return *ptr;
}

template<typename T>
void AVLTree<T>::cambioLLyRR(pairPtrLado padre, pairPtrLado abuelo){
    (*abuelo.first)->altura--;
    
    Node<T> *tmp = *abuelo.first;
    *abuelo.first = *padre.first;
    *padre.first = (*padre.first)->nodes[!padre.second];
    (*abuelo.first)->nodes[!padre.second] = tmp;
}

template<typename T>
void AVLTree<T>::cambioLRyRL(pairPtrLado hijo, pairPtrLado &padre, pairPtrLado abuelo){
    (*abuelo.first)->altura--;
    (*padre.first)->altura--;
    (*hijo.first)->altura++;
    
    Node<T> *tmpA = *abuelo.first;
    Node<T> *tmpB = *padre.first;
    *abuelo.first = *hijo.first;

    *padre.first = (*abuelo.first)->nodes[hijo.second];
    *hijo.first = (*abuelo.first)->nodes[padre.second]; 
    
    (*abuelo.first)->nodes[padre.second] = tmpB;
    (*abuelo.first)->nodes[hijo.second] = tmpA;

    // Arreglo el doble ptr del pair
    padre.first = &((*abuelo.first)->nodes[padre.second]);
}

template<typename T>
int AVLTree<T>::difAltura(Node<T>* nodo){
    if(nodo->nodes[0] and nodo->nodes[1])
	return nodo->nodes[0]->altura - nodo->nodes[1]->altura;
    return nodo->nodes[nodo->nodes[1] != nullptr]->altura;
}

template<typename T>
void AVLTree<T>::balanceo(stack<pairPtrLado > &camino){
    pairPtrLado hijo, padre;
    int diferencia;
    while(camino.size() > 1){
	padre = camino.top();
	camino.pop();

	diferencia = difAltura(*camino.top().first);
	if(diferencia == 0) return;
	
	if(diferencia == 1 or diferencia == -1){
	    if((*padre.first)->altura + 1 > (*camino.top().first)->altura)
		(*camino.top().first)->altura++;
	    hijo = padre;
	}	
	else if(diferencia == 2 or diferencia == -2){
	    if(hijo.second == padre.second)
		cambioLLyRR(padre, camino.top());
	    else{
		cambioLRyRL(hijo, padre, camino.top());
		hijo = padre;
	    }
	}	
    }
}

template<typename T>
int AVLTree<T>::size(Node<T> *ptr){
    if(!ptr) return 0;
    return max(size(ptr->nodes[0])+1, size(ptr->nodes[1])+1);
}


template<typename T>
int AVLTree<T>::size(){
    return size(raiz);
}

template<typename T>
bool AVLTree<T>::insert(T x){
    Node<T> **ptr;
    stack<pairPtrLado > camino;
    
    if(find(x,ptr,camino)) return 0;
    *ptr = new Node<T>(x);
    if(camino.size() > 1) balanceo(camino);
    return 1;
}

template<typename T>
bool AVLTree<T>::remove(T x){
    Node<T> **ptr;
    stack<pairPtrLado> camino; 
    if(!find(x,ptr,camino)) return 0;
    if((*ptr)->nodes[0] and (*ptr)->nodes[1]){
	srand(time(NULL));
	bool random  = rand()%2;
	Node<T> *tmp = *ptr;
	tmp = tmp->nodes[random];
	while(tmp->nodes[!random])
	    tmp = tmp->nodes[!random];
	(*ptr)->val = tmp->val; 
    }
    Node<T> *tmp = *ptr;
    *ptr = (*ptr)->nodes[(*ptr)->nodes[1] != nullptr];
    delete tmp;
    return 1;    
}

template <typename T>
void AVLTree<T>::recorrido(Node<T> *ptr, int orden[3]) {
    //Orden: 0 = Izquierda , 1 = Derecha, 2 = Raiz
    if(!ptr) return;
    for(int i=0; i < 3; i++){
	if(orden[i] < 2)
	    recorrido(ptr->nodes[orden[i]], orden);
	else
	    cout<< ptr->val << " ";
    } 
}

template<typename T>
void AVLTree<T>::print(int orden[3]){
    recorrido(raiz, orden);
    cout << endl;
}

template <typename T>
void AVLTree<T>::printAmplitud() {
    queue<Node<T>* > cola;
    cola.push(raiz);
    while(!cola.empty()){
	if(cola.front()){
	    cout << cola.front()->val << " ";
	    cola.push(cola.front()->nodes[0]);
	    cola.push(cola.front()->nodes[1]);
	}
	cola.pop();	
    }
    cout << endl;
}

template <typename T>
void AVLTree<T>::printBonito(){
    vector <Node<T>* > c;
    c.push_back(raiz);
    int len;
    while(c.size()!=0){
        len=c.size();
        for(int i=0;i<len;i++){
	    if(c[i]){
		cout<<c[i]->val<<" ";
		c.push_back(c[i]->nodes[0]);
		c.push_back(c[i]->nodes[1]);
	    }
	    else
		cout << ". ";
	    
	    }
        cout<<endl;
        c.erase(c.begin(),c.begin()+len);
    }
}

int main() {
    AVLTree<int> arbol;
    srand(time(NULL));
    for(int i=0; i<50; i++){
	int random = rand()%100;
	arbol.insert(random);
    }
    sdsdasdads
    cout << endl;
    int orden[] = {0,2,1};
    cout << "Orden: ";
    arbol.print(orden);
    cout << "Amplitud: ";
    arbol.printAmplitud();
    cout << "Size: " << arbol.size() << endl;
    cout << "Bonito: " << endl;
    arbol.printBonito();
    cout << endl;
}


//nombre direccion, carpeta, resolución
// un ptr a imagen que se llena cuando busco la image ny quiero mostrarla 
