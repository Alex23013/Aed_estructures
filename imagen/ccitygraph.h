#ifndef CCITYGRAPH_H
#define CCITYGRAPH_H
#include "cgraph.h"
#include<ctime>
#include<cstdlib>
#include <QPoint>
#include<vector>
#include<stack>
#include<list>
#include<algorithm>
#include<iostream>
using namespace std;

class CCityGraph :public c_graph<QPointF, int>
{
public:

    void generadorNodos(int numero){
        vector<int> xs;
        vector<int> ys;
        srand(unsigned(time(0)));


        for(int i= 0; i < numero; i++){
            int rndm = rand()% 5 ;
            for(int j = 0; j < rndm; j++)
                xs.push_back(i);
            ys.push_back(i);
        }

        auto randomFun =[] (int i) { return rand()%i;};
        random_shuffle(xs.begin(), xs.end(), randomFun);
        random_shuffle(ys.begin(), ys.end(), randomFun);

        for(uint i=0; i < ys.size(); i++){
            insert_node(QPoint(xs[i], ys[rand()%(ys.size())]));
        }
    }


    /*int distanciaCuad(Node a, Node b) {
        return pow(a.m_data.x() - b.m_data.x(), 2) + pow(a.m_data.y() - b.m_data.y(), 2);
    }*/

    void generadorEdges(int radio, int numero){
        int contador = 0;
        int dist;

        auto distanciaCuad = [](Node *a, Node *b) {
            return pow(a->m_data.x() - b->m_data.x(), 2) +
                   pow(a->m_data.y() - b->m_data.y(), 2);
        };

        for (uint i = 0; i < m_nodes.size(); i++) {
            contador = 0;
            for (uint j = 0; (contador <= numero) and (j < m_nodes.size()); j++) {
                if (i != j){
                    dist = distanciaCuad(m_nodes[i], m_nodes[j]);
                    if (dist <= radio) {
                        insert_edge(dist,m_nodes[i]->m_data,m_nodes[j]->m_data,0);
                        contador++;
                    }
                }
            }
        }
    }

    inline void borrarNodes(int x1, int y1, int x2, int y2){
        for(vecIt it = m_nodes.begin(); it != m_nodes.end();){
            if((*it)->m_data.x() >= x1 and (*it)->m_data.x() <= x2 and
               (*it)->m_data.y() >= y1 and (*it)->m_data.y() <= y2){
                remo_node(it);
            }
            else it++;
        }

    }

    inline void borrarNodes(QPoint *top, QPoint *bot){
        int x1, y1, x2, y2;
        if(top->x() <= bot->x()){
            x1 = top->x();
            x2 = bot->x();
        }
        else {
            x1 = bot->x();
            x2 = top->x();
            //Para imprimir correctamente el rectángulo:
            top->setX(x1);
            bot->setX(x2);
        }
        if(top->y() <= bot->y()){
            y1 = top->y();
            y2 = bot->y();
        }
        else {
            y1 = bot->y();
            y2 = top->y();
            //Para imprimir correctamente el rectángulo:
            top->setY(y1);
            bot->setY(y2);
        }

        for(vecIt it = m_nodes.begin(); it != m_nodes.end();){
            if((*it)->m_data.x() >= x1 and (*it)->m_data.x() <= x2 and
               (*it)->m_data.y() >= y1 and (*it)->m_data.y() <= y2){
                remo_node(it);
            }
            else it++;
        }

    }

    Node* calcular_next(Node* actual,list<Node*> &camino){
        vector <Node* > no_visitados;
        Node* sig=nullptr;
        for(int i=0;i<actual->m_nedges.size();i++){

            if(actual->m_nedges[i]->m_node[0]->m_data == actual->m_data){
                sig=actual->m_nedges[i]->m_node[1];
            }else{
                sig=actual->m_nedges[i]->m_node[0];
            }

            if(sig->d_visitado !=false && (sig->d_dist == -1 || sig->d_dist > actual->m_nedges[i]->m_data ) ){
                sig->nodo_ant=actual;
                sig->d_dist=actual->m_nedges[i]->m_data+ actual->d_dist;
                no_visitados.push_back(sig);
            }
        }
        actual->d_visitado=true;
        if(no_visitados.size()>1){camino.push_back(sig);}
        else{camino.pop_back();}
        return camino.back();
    }

    void dijstra2(Node* inicio, Node* final, list<Node*> &camino){
    Node* tmp;
    camino.push_back(inicio);
    while(tmp != final){
            tmp=calcular_next(tmp,camino);
        }
    }


     bool dijkstra(Node* inicio, Node* final, list<Node*> &ruta);
};

//DIJKSTRA

extern CCityGraph::Node* FINAL;
extern CCityGraph::Node* ACTUAL;
//-------------------

//DIJKSTRA


inline bool CCityGraph::dijkstra(Node* inicio, Node* final, list<Node*> &camino) {
    Node* actual = inicio;
    list<Node*> ruta;
    ruta.push_back(inicio);
    FINAL = final;

    inicio->d_visitado = true;//...xD
    inicio->d_dist = 0;

    while (actual != final) {
        ACTUAL = actual;
        if (!actual->d_visitado) {
            actual->d_visitado = true;
            //actual->m_nedges.sort(MinDest);
            //vector<Edge*> aa =actual->m_nedges;
            //std::sort(aa.begin(),aa.end(),MinDest);
        }
        Node* next = nullptr; //siguiente nodo en la ruta
        vector<Edge*>::iterator it = actual->m_nedges.begin();

        while (it != actual->m_nedges.end()) {
            if (!(*it)->utilizado) {
                //actualizar distancia a origen
                Node* check = ((*it)->m_node[0] != actual) ? (*it)->m_node[0] : (*it)->m_node[1];
                if (!check->d_visitado) {
                    if (!next) {
                        next = check;
                    }
                    if (check->d_dist < 0 || check->d_dist > actual->d_dist + (*it)->m_data) {
                        check->d_dist = actual->d_dist + (*it)->m_data;
                        check->nodo_ant = actual;
                    }

                }
                cout << "";
            }
            it++;
        }
        if (next)
        {
            actual = next;
            ruta.push_back(actual);
        }
        else
        {
            if (ruta.size() > 1)
            {
                ruta.pop_back();
                actual = ruta.back();
            }
            else
            {
                return false;
            }
        }
    }
    camino =ruta;
    return true;
}



 #endif // CCITYGRAPH_H
