#include<iostream>
#include <stdlib.h>
#include<string>
using namespace std;

template<typename T>
class nodo{
public:
T info;
nodo* sig;

nodo(T info){
	this->info=info;
	sig =NULL;
	}

};
template<typename T>
class lista{
public:
  nodo<T> *start;

  lista(){
	start=NULL;}

  bool find(T x,nodo<T>**&p){
	p=&start;
	while(*p && (*p)->info<x){
		p=&((*p)->sig);
		//cout<<".";
	}	
	return *p && (*p)->info ==x;
	}

  bool insertar(T x){
	nodo<T>** p;
	if(find(x,p)){
		return 0;
		}
	nodo<T> * w;
	w =new nodo<T>(x);
	w->sig=*p;
	*p=w;
	return 1;
	}

  bool eliminar(T x){
	nodo<T>** p;
	if(!find(x,p)){
		cout<<"no find "<<x<<"\n";
		return 0;
		}
	nodo<T> * tmp;
	tmp = (*p)->sig;
	delete *p;
	*p=tmp;
	return 1;
	}
	

  void print_lista(){
	nodo<T>* cent;
	cent =start;
	cout<<"\nLa lista es:\n";
	while(cent){
		cout<<(cent)->info;
		cout<<"-> ";
        	(cent) =(cent)->sig;
    		}
	cout<<endl;
	}

   void inverso(){
	nodo<T>* cent;
	nodo<T>* aux;
	cent =start;
	
	int cont =0; 
	while(cent->sig){
		(cent) =(cent)->sig;
		cont++;
    		}
	cout<<"c: "<<(cent)->info;
	cout<<(cent)->sig<<"---";
	
	for(int j=2;j<cont+1;j++){
		aux=start;
		for(int i=0;i<cont-j ;i++){
			aux=aux->sig;	
		}

		cout<<"\na: "<<(aux)->info;
		cout<<((aux)->sig)->info<<"---";	
		cent->sig =aux->sig;
		cout<<"c: "<<(cent)->info;
		cout<<((cent)->sig)->info<<"---";
		cent=cent->sig;
		}
	aux=start;
	cout<<"\na: "<<(aux)->info;
		cout<<((aux)->sig)->info<<"---";	
		cent->sig =aux;
		cout<<"c: "<<(cent)->info;
		cout<<((cent)->sig)->info<<"---";
		cent=cent->sig;
	}
	
	
  
};

int main(){

	
	lista<int> A;
	srand((unsigned)time(NULL));
	for(int i=0;i<10000;i++){
		//A.insertar(i);
		A.insertar( rand() % 1000);
	}
	A.print_lista();
	//nodo<int>** p;
	//cout<<"\nA.find(5,p) => "<<A.find(5,p)<<endl;
	//cout<<"\nA.find(3,p) => "<<A.find(3,p)<<endl;	
	for(int i=0;i<100;i++){
		A.eliminar(rand() % 1000);
	}
	A.print_lista();
	//A.inverso();

	
	
}
