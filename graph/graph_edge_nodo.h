#ifndef GRAPH_EDGE_NODO_H
#define GRAPH_EDGE_NODO_H
#include <iostream>
#include <list>
using namespace std;

template <typename G>
class cNodo;
template <typename G>
class cEdge;


template <typename N, typename E>
class cGraph{
public:
    typedef cGraph<N,E> selfie ;
    typedef N Nn;
    typedef E Ee;
    typedef cNodo<selfie> Nodo;
    typedef cEdge<selfie> Edge;

    list<cNodo<N>*> mis_nodos;

    void recorrer_grafo(){
        cout<<"\nLos nodos del grafo son: \n";
        for(int i=0;i<mis_nodos.size();i++){
            cout<<mis_nodos[i];
        }
    }

    bool find(N n_info){
        for(int i=0;i<mis_nodos.size();i++){
            if(n_info == (mis_nodos[i])->info ){return 1;}
        }
        return 0;
    }
    bool insert_nodo(N n_info)
    {
        if(find(n_info)){
            return 0;
        }
        cNodo<N>* p=new cNodo<N>(n_info);
        mis_nodos.push_back(p);
        return 1;
    }
    bool insert_edge(E n_peso, cNodo<N>* inicio, cNodo<N>* llegada, bool dir);
    bool delete_nodo(N n_info);
    bool delete_edge(E n_peso, cNodo<N>* inicio, cNodo<N>* llegada);


};

template <typename G>
class cNodo{
 public:
    typedef typename G:: N N;
    typedef typename G:: Edge Edge;

    N info;
    list <Edge*> edges;
};

template <typename G>
class cEdge{
public:
    typedef typename G:: E E;
    typedef typename G:: Nodo Nodo;

    E peso;
    Nodo* nodos[2];
    bool dir; // 0:bidireccional  1:de nodos[0] a nodos[1] en una direccion
};

#endif // GRAPH_EDGE_NODO_H
