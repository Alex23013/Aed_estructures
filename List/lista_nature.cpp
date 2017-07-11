#include<iostream>
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
--------------	nodo<T>** p;
	if(!find(x,p)){
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
	nodo<T>* ant;
	nodo<T>* act;
	nodo<T>* next;
	
	ant=start;
	act=ant->sig;
	next=act->sig;
	ant->sig=NULL;
	while(next->sig){	
		act->sig=ant;
		ant=act;
		act=next;
		next=next->sig;
	}
	act->sig=ant;
	next->sig=act;
	start=next;
	
	}
	
	
  
};

int main(){

	
	lista<int> A;
	for(int i=0;i<10;i++){
		A.insertar(i);
	}
	A.print_lista();
	//nodo<int>** p;
	//cout<<"\nA.find(5,p) => "<<A.find(5,p)<<endl;
	//cout<<"\nA.find(3,p) => "<<A.find(3,p)<<endl;	
	/*for(int i=0;i<2;i++){
		A.eliminar(i);
	}*/
	//A.print_lista();
	A.inverso();
	A.print_lista();
	A.inverso();
	A.print_lista();
	A.inverso();
	A.print_lista();
	
	
}
