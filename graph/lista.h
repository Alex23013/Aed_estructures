#ifndef LISTA_H
#define LISTA_H

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
    while(*p && (*p)->info < x){
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
        cout<<cent->info;

        cout<<"-> ";
            (cent) =(cent)->sig;
            }
    cout<<endl;
    }
};

#endif // LISTA_H
