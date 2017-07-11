#include "graphview.h"

#include <iostream>
#include <QDebug>
using namespace std;

GraphView::GraphView(QWidget *parent) : QGraphicsView(parent) {
    setGeometry(10,0,parent->width(),parent->height());
    scene = new QGraphicsScene(this);
    setScene(scene);
    grafo = nullptr;
    borrar1 = borrar2 = nullptr;
    nodo1 = nodo2 = nullptr;

}


void GraphView::genGraph(){
    if(!grafo) delete grafo;
    grafo = new CityGraph;

    int numNodes = 500;
    int radioEdges = 4*numNodes;


    grafo->generadorNodos(numNodes);
    grafo->generadorEdges(radioEdges);
    qDebug() << "insercion terminada";
}

bool GraphView::printGraph(){
    if(!grafo) return 0;
    QPen pen(Qt::black, 1);

    for (uint i = 0; i < grafo->nodes.size(); i++){
        auto it = grafo->nodes[i]->edges.begin();
        for(uint j = 0; j < grafo->nodes[i]->edges.size(); j++){
            scene->addLine(QLine((*it)->nodes[0]->data.toPoint(),(*it)->nodes[1]->data.toPoint()),pen);
            it++;
        }
    }

    for (uint i = 0; i < grafo->nodes.size(); i++){
        VisualNode* tmp = new VisualNode(grafo->nodes[i]);
        scene->addItem(tmp);
    }
    return 1;
}

void GraphView::mousePressEvent(QMouseEvent *event){
    QPointF mousePoint = mapToScene(event->pos());
    QGraphicsItem* ptr = itemAt(mousePoint.toPoint());
    if(ptr) qDebug() << "PTR" << ptr ;
    VisualNode* pp = dynamic_cast<VisualNode*>(ptr);
    if(event->button() == Qt::RightButton){
        if(!borrar1){
            borrar1 = new QPoint();
            *borrar1 = mousePoint.toPoint();
        }
        else{
                borrar2 = new QPoint();
                *borrar2 = mousePoint.toPoint();
                grafo->borrarNodes(borrar1,borrar2);
                scene->clear();
                printGraph();
                update();
                scene->addRect(QRectF(QPointF(*borrar1),QPointF(*borrar2)));
                update();
                delete borrar1;
                delete borrar2;
                borrar1 = borrar2 = nullptr;
            }
        }

    else{
        if(pp){
            qDebug() << "XY NODO: "<<pp->punto.x() << ", " << pp->punto.y();
            qDebug() << "PTR NODO:" << pp->realNode;
            if(!nodo1){
                nodo1 = pp;
            }
            else{
                    nodo2 = pp;

                    list<CityGraph::Node*> ruta;
                    grafo->dijkstra(nodo1->realNode,nodo2->realNode, ruta);

                    scene->clear();

                    printGraph();
                    graficarRuta(ruta);
                    update();

                    nodo1 = nodo2 = nullptr;
                }
        }
    }
}


//DIJKSTRA

void GraphView::graficarRuta(list<CityGraph::Node*> ruta)
{
    if(ruta.empty()) return;
    list<CityGraph::Node*>::iterator it, itplus;
    it = itplus = ruta.begin();
    itplus++;
    QPen pen(Qt::blue, 2);
    while (itplus != ruta.end() )
    {
        scene->addLine((*it)->data.x(), (*it)->data.y(),
            (*itplus)->data.x(), (*itplus)->data.y(), pen);
        it = itplus;
        itplus++;
    }
}

