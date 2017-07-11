#ifndef EDGE_NODO_CHAR_INT_H
#define EDGE_NODO_CHAR_INT_H

#include <iostream>
#include <list>
//#include "lista.h"
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template <typename G>
class cNodo{
 public:
    typedef typename G::Nn N; // cambié G::N por G::Nn motivo: dentro de G no existe N pero si existe Nn
    typedef typename G::Edge Edge;


    N m_data;//info del nodo
    vector <Edge*> m_edges;//el profe puso list

    cNodo(N x){
    m_data=x;
    }

    void print_aristas(){
        if(m_edges.size()>0){
            //cout<<"aris:";
            for(int i=0;i<m_edges.size();i++){

                if(m_edges[i]->m_dir == 0){//bidireccion
                    cout<<m_edges[i]->m_peso<<"(";
                    if(m_edges[i]->m_nodos[0]->m_data==m_data){
                       cout<< m_edges[i]->m_nodos[1]->m_data<<")-";
                    }else{
                       cout<< m_edges[i]->m_nodos[0]->m_data<<")-";
                    }

                }else{//de 0 a 1
                    if(m_edges[i]->m_nodos[0]->m_data==m_data){
                       cout<<m_edges[i]->m_peso<<"(";
                       cout<< m_edges[i]->m_nodos[1]->m_data<<")-";
                    }

                }
             }
            cout<<"\n";
        }else{
        cout<<"--\n";}
    }

};

template <typename G>
class cEdge{
public:
    typedef typename G::Ee E;// cambié G::E por G::Ee motivo: dentro de G no existe E pero si existe Ee
    typedef typename G::Nodo Nodo;

    E m_peso;
    Nodo* m_nodos[2];
    bool m_dir; // 0:bidireccional  1:de nodos[0] a nodos[1] en una direccion

    cEdge(E peso, bool dir){
        this->m_peso=peso;
        this->m_dir=dir;
        m_nodos[0]=m_nodos[1]=0;
    }
    void print_aris(){
        cout<<m_dir<<"("<<m_nodos[0]<<","<<m_nodos[1]<<")\n";
    }
};

template <typename N, typename E>
class cGraph{
public:
    typedef cGraph<N,E> self ;
    typedef N Nn;
    typedef E Ee;
    typedef cNodo<self> Nodo;
    typedef cEdge<self> Edge;

    vector<Nodo*> mis_nodos;
    //cambié cNodo<N>* por Nodo* motivo:
    // Nodo es tu nuevo tipo de dato, con typedef definiste que Nodo
    //es un cNodo<self> y ese self esta definido como un cGraph<N,E>
    //yyy no olvides que tanto nodo como arista necesitan
    //recibir todo el tipo de dato grafo

    void recorrer_grafo(){
        cout<<"\nMis nodos: \n";
        for(int i=0;i<mis_nodos.size();i++){
            cout<<mis_nodos[i]->m_data<<" : ";
            mis_nodos[i]->print_aristas();
            //cout<<*(((mis_nodos[i])->m_edges).begin());
        }
    }


    bool insert_nodo(Nn n_info){

        if(find_nodo_almost_pro(n_info)){return 0;}

        Nodo* new_nodo=new Nodo(n_info);
        mis_nodos.push_back(new_nodo);
        //std::sort(mis_nodos.begin(),mis_nodos.end());
        return 1;
    }

    bool find_nodo_almost_pro(Nn n_info){
        for(int i=0;i<mis_nodos.size();i++){
            if(mis_nodos[i]->m_data == n_info){
                return true;
            }
        }
        return false;
     }

    bool find_nodo(Nn n_info, Nodo* &p){
            int i=0;
            p=mis_nodos[i];
            while(p && n_info != p->m_data){
               p=mis_nodos[++i];
            }
            return p && p->m_data == n_info;
        }

    bool insert_edge(Ee n_peso, Nn inicio, Nn llegada, bool dir){
        Edge* new_edge = new Edge(n_peso,dir);
        Nodo* n_inicio;
        find_nodo(inicio,n_inicio);
        n_inicio->m_edges.push_back(new_edge);
        Nodo* n_llegada;
        find_nodo(llegada,n_llegada);
        n_llegada->m_edges.push_back(new_edge);
        (*new_edge).m_nodos[0]=n_inicio;
        (*new_edge).m_nodos[1]=n_llegada;
        //(*new_edge).print_aris();
        return 1;
    }
    bool delete_nodo(Nn n_info);
    bool delete_edge(Ee n_peso, Nn inicio, Nn llegada);

};
#endif // EDGE_NODO_CHAR_INT_H
