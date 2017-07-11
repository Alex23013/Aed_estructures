#include<iostream>
#include<string>
using namespace std;
template<typename T>
class nodoList{
public:
T info;
nodoList* sig;

nodoList(T info){
	this->info=info;
	sig =NULL;
	}

};
template<typename T>
class lista{
public:
  nodoList<T> *start;

  lista(){
	start=NULL;}

  bool find(T x,nodoList<T>**&p){
	p=&start;
	while(*p && (*p)->info<x){
		p=&((*p)->sig);
	}	
	return *p && (*p)->info ==x;
	}

  bool insertarDato(T x){
	nodoList<T>** p;
	if(find(x,p)){
		return 0;
		}
	nodoList<T> * w;
	w =new nodoList<T>(x);
	w->sig=*p;
	*p=w;
	return 1;
	}

  bool borrarUnDato(T x){
	nodoList<T>** p;
	if(!find(x,p)){
		return 0;
		}
	nodoList<T> * tmp;
	tmp = (*p)->sig;
	delete *p;
	*p=tmp;
	return 1;
	}
	
	void reemplazarUnDato(T x, T xNuevo,nodoList<T>**&p ){
	if(!find(x,p)){
		return;
		}
	(*p)->info = xNuevo;	
		
	}

  void contenido(){
	nodoList<T>* cent;
	cent =start;
	cout<<"\nLa lista es:\n";
	while(cent){
		cout<<(cent)->info;
		cout<<"-> ";
        	(cent) =(cent)->sig;
    		}
	cout<<endl;
	}  
};

