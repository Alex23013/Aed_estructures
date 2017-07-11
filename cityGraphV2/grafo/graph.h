#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "nodoedge.h"

template <typename N, typename E>
class Graph{
public:
    typedef Graph<N,E> self ;
    typedef N Nn; // Nn es el tipo del nodo, Nodo es el Nodo en sí
    typedef E Ee;
    typedef CNode<self> Node;
    typedef CEdge<self> Edge;
    typedef typename vector<Node*>::iterator vecIt;

    vector<Node*> nodes;

    //void recorrerGrafo();
    bool insNode(N n);
    bool insEdge(Node *ini, Node *fin, E data, bool dir);
    bool findNode(N n, vecIt &it);
    bool remNode(N n);
    bool remNode(vecIt it);
    bool remEdge(Node *ini, Node *fin, E data, bool dir);
    bool remEdge(Edge* e);
    ~Graph();
};


template <typename N, typename E>
bool Graph<N,E>::insNode(N n){
    Node *p = new Node(n);
    nodes.push_back(p);
    return 1;
}

template <typename N, typename E>
bool Graph<N,E>::insEdge(Node *ini, Node *fin, E data, bool dir){
    Edge *p = new Edge(ini, fin, data, dir);
    ini->edges.push_back(p);
    fin->edges.push_back(p);
    return 1;
}

template<typename N, typename E>
bool Graph<N,E>::findNode(N n, vecIt &it) {
    it = nodes.begin();
    while (it != nodes.end() ){
        if ( (*it)->data == n )
            return true;
        it++;
    }
    return false;
}

template <typename N, typename E>
bool Graph<N,E>::remNode(N n){
    vecIt it;
    if(!findNode(n,it)) return false;
    delete (*it);
    nodes.erase(it);
    return true;
}

template <typename N, typename E>
bool Graph<N,E>::remNode(vecIt it){
    delete (*it);
    nodes.erase(it);
    return true;
}


template <typename N, typename E>
bool Graph<N,E>::remEdge(Node *ini, Node *fin, E dato, bool dir){
    return false;
}

template <typename N, typename E>
bool Graph<N,E>::remEdge(Edge* e){
    delete e;
    return 1;
}


template <typename N, typename E>
Graph<N,E>::~Graph(){
    while(!nodes.empty()){
        delete nodes.back();
        nodes.pop_back();
    }
}

#endif // GRAPH_H
