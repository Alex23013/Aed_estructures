#include <iostream>
#include <stack> 
#include <queue> 
 
using namespace std;

template<typename T>
class nodo{
public:
T info;
nodo<T>* hijos[2];

nodo(T info){
	this->info=info;
	hijos[0] =NULL;
	hijos[1] =NULL;
	}

};

template<typename T>
class Arbol{
public:
  nodo<T> *root;

	Arbol(){root=NULL;}

	  bool find(T x,nodo<T>**&p){
		p=&root;
		while(*p && (*p)->info != x){
			p=&((*p)->hijos[(*p)->info < x]);		
			}
		return *p;
		}

	  bool insertar(T x){
		//cout<<"nodo_in:"<<x<<endl;
		nodo<T>** p;
		if(find(x,p)){
			return 0;}
		*p=new nodo<T>(x);
		return 1;
		}

	  

	nodo<T>** Intercambio(nodo<T>** q ){
		q = &(*q)->hijos[0];
		while ((*q)->hijos[1])
		{
			q = &((*q)->hijos[1]);
		}
		return q;
	}

	 bool Remover(T x){
		nodo<T>**p, **q;
		if (!find(x, p))
		{
			return 0;
		}
		if ((*p)->hijos[0] && (*p)->hijos[1])
		{
			q = Intercambio(p);
			(*p)->info = (*q)->info;
			p = q;
		}
		nodo<T>* t = *p;
		*p = (*p)->hijos[(*p)->hijos[1]!=0];
		delete t;
		return 1;
	}
///funcion de arbol a lista solo con punteros
	void amplitud()
	{
	cout<<"\nRecorrdio en amplitud\n";
	queue <nodo<T>*> cola;
	cola.push(root);
	while(!cola.empty()){
		if(cola.front()){
			cout<<cola.front()->info<<" - ";
			cola.push(cola.front()->hijos[1]);
			cola.push(cola.front()->hijos[0]);
			}
			cola.pop();
		}
	}


	void profundidad(){
	stack<nodo<T>*> pila;
	nodo<T>* tmp;
	cout<<"\nRecorrdio en profundidad\n";
	pila.push(root);
	while(!pila.empty()){
		cout << pila.top()->info<< " - ";
		tmp=pila.top();
		pila.pop();
		if(tmp->hijos[0]){pila.push(tmp->hijos[0]);}
		if(tmp->hijos[1]){pila.push(tmp->hijos[1]);}		
		}

	}

void a_lista(){
		nodo<T>* fin,*p;
		fin=root;
		p=root;
		while(fin->hijos[1]){
			fin=fin->hijos[1];	
			}
		while(p->hijos[1]){
			if(p->hijos[0]){
				fin->hijos[1]=p->hijos[0];
				p->hijos[0]=NULL;
			}
		
			while(fin->hijos[1]){
				fin=fin->hijos[1];	
				}
			p=p->hijos[1];
		}
		
}



	/*void a_lista(){
		nodo<T>** p,**q,**t;
		
		q=&root;
		while((*q)->hijos[0] ){
			p=q;
			t=q;
			while((*p)->hijos[1]){
			p=&((*p)->hijos[1]);		
			}
			t=&((*t)->hijos[0]);
			cout<<"\nt: "<<(*t)->info<<endl;
			(*p)->hijos[1]=(*t);
			
			q=&((*q)->hijos[1]);
			}
			
	};*/

	void print_arbol(){
		if(root == NULL)
			{cout<<"\nEl arbol esta vacio"<<endl;}
		else{
		 	cout<<"\nEl arbol impreso  inorden es: "<<endl;
		 	print_inorden(root);
		}
	}

	void print_lista(){
	nodo<T>* cent;
	cent =root;
	cout<<"\nLa lista es:\n";
	while(cent){
		cout<<(cent)->info;
		cout<<"-> ";
        	(cent) =(cent)->hijos[1];
    		}
	cout<<endl;
	}

	void print_inorden(nodo<T>* yop){
	    if(!yop){return;}
	    	print_inorden(yop->hijos[0]);
		cout<<yop->info<<" - ";
	    	print_inorden(yop->hijos[1]);		
	 }
	void print_preorden(nodo<T>* yop){
	    if(!yop){return;}
		cout<<yop->info<<" - ";
		print_preorden(yop->hijos[0]);
		print_preorden(yop->hijos[1]);		
	 }
	void print_postorden(nodo<T>* yop){
	    if(!yop){return;}
	    	print_postorden(yop->hijos[0]);
		print_postorden(yop->hijos[1]);	
		cout<<yop->info<<" - ";	
	 }
};
