#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<typename T>
class nodo_a{
public:
T info;
nodo_a<T>* hijos[2];

nodo_a(T info){
    this->info=info;
    hijos[0] =NULL;
    hijos[1] =NULL;
    }

};

template<typename T>
class Arbol{
public:
  nodo_a<T> *root;
  typedef T value_type;

    Arbol(){root=NULL;}

      bool find(T x,nodo_a<T>**&p){
        p=&root;
        while(*p && (*p)->info != x){
            p=&((*p)->hijos[(*p)->info < x]);
            }
        return *p;
        }

      bool insertar(T x){
        //cout<<"nodo_in:"<<x<<endl;
        nodo_a<T>** p;
        if(find(x,p)){
            return 0;}
        *p=new nodo_a<T>(x);
        return 1;
        }



    nodo_a<T>** Intercambio(nodo_a<T>** q ){
        q = &(*q)->hijos[0];
        while ((*q)->hijos[1])
        {
            q = &((*q)->hijos[1]);
        }
        return q;
    }

     bool eliminar(T x){
        nodo_a<T>**p, **q;
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
        nodo_a<T>* t = *p;
        *p = (*p)->hijos[(*p)->hijos[1]!=0];
        delete t;
        return 1;
    }

    void print_(){
        if(root == NULL)
            {cout<<"\nEl arbol esta vacio"<<endl;}
        else{
            //cout<<"\nEl arbol impreso  inorden es: "<<endl;
            print_inorden(root);
        }
    }

    void print_inorden(nodo_a<T>* yop){
        if(!yop){return;}
            print_inorden(yop->hijos[0]);
        cout<<yop->info<<" - ";
            print_inorden(yop->hijos[1]);
     }
    void print_preorden(nodo_a<T>* yop){
        if(!yop){return;}
        cout<<yop->info<<" - ";
        print_preorden(yop->hijos[0]);
        print_preorden(yop->hijos[1]);
     }
    void print_postorden(nodo_a<T>* yop){
        if(!yop){return;}
            print_postorden(yop->hijos[0]);
        print_postorden(yop->hijos[1]);
        cout<<yop->info<<" - ";
     }
};

#endif // TREE_H
