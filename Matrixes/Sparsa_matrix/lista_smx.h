#ifndef LISTA_SMX_H
#define LISTA_SMX_H
#include "nodos.h"

template<typename T>
class lista_smx {
public:
  nodo_smx<T> *head;

  lista_smx(){
    head=nullptr;}

  bool insert_x(int i,int j,T dato,nodo_smx<T> ** p);
  bool insert_y(nodo_smx<T> ** p);
  bool remove_x(nodo_smx<T> ** p);
  bool remove_y(nodo_smx<T> ** p);

};

template<typename T>
bool lista_smx<T>:: insert_x(int i,int j,T dato,nodo_smx<T> ** p){
    nodo_smx<T>* w;
    w=new nodo_smx<T>(i,j,dato);
    w->next=*p;
    *p=w;
    return 1;
}

template<typename T>
bool lista_smx<T>:: insert_y(nodo_smx<T> ** p){
    nodo_smx<T>* w;
    if(head == nullptr){
        head=w;
    }else{
        w->down=*p;
        *p=w;
        return 1;
    }
}

#endif // LISTA_SMX_H
