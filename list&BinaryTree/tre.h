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

	  bool insertarDato(T x){
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

	 bool borrarUnDato(T x){
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
	
	void reemplazarUnDato(T x, T xNuevo){
	 borrarUnDato(x);
	 insertarDato(xNuevo);
	}
	
	void contenido(){
	cout<<"\ncontenido del Arbol\n";
          vector <nodo<T>* > c;
          c.push_back(root);
          int len;
          while(c.size()!=0){
              len=c.size();
              for(int i=0;i<len;i++){
              if(c[i]){
		          cout<<c[i]->info<<" ";
		          c.push_back(c[i]->hijos[0]);
		          c.push_back(c[i]->hijos[1]);
              }
              else
              	cout << "- ";
              }
              cout<<endl;
              c.erase(c.begin(),c.begin()+len);
          }
      }
};
