#ifndef NODOEDGE_H
#define NODOEDGE_H

#include <iostream>
#include <list>
using namespace std;

template <typename G>
class CNode {
 public:
    typedef typename G::Nn N;
    typedef typename G::Edge Edge;

    N data;
    list <Edge*> edges;

    //--DIJKSTRA
    typedef typename G::Ee E;
    E d_dist; //distancia a nodo inicial
    bool d_visitado; // fue visitado
    CNode<G>* nodo_ant; //puntero a nodo anterior
    //-----------------------------

    CNode(N val) {
        data = val;

        //DIJKSTRA
        d_dist = -1; // iniciando a infinito
        d_visitado = false; // no visitado
        nodo_ant = nullptr;
        //--------------------------
    }
    ~CNode(){
        while(!edges.empty()){
            delete edges.front();
        }
    }

};

template <typename G>
class CEdge {
public:
    typedef typename G::Ee E;
    typedef typename G::Node Node;
    typedef typename G::Edge Edge;
    E data;
    Node* nodes[2];
    bool dir; // 0:bidireccional  1:nodos[0] a nodos[1]

    //DIJKSTRA
    bool utilizado;
    //-----

    CEdge(Node *ini, Node *fin, E val, bool d){
        data = val;
        nodes[0] = ini;
        nodes[1] = fin;
        dir = d;

        //DIJKSTRA
        utilizado = false;
        //-----

    }
    ~CEdge(){

        typename list<CEdge<G>*>::iterator it = nodes[0]->edges.begin();
        while (*it != this){
            it++;
        }
        nodes[0]->edges.erase(it);
        it = nodes[1]->edges.begin();
        while (*it != this){
            it++;
        }
        nodes[1]->edges.erase(it);

    }
};

#endif // NODOEDGE_H
