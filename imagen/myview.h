#ifndef MYVIEW_H
#define MYVIEW_H

#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "visionodo.h"
#include "ccitygraph.h"
class GraphView : public QGraphicsView {
    Q_OBJECT
public:
    QGraphicsScene *scene;
    CCityGraph* AQP;
    QPoint *borrar1;
    QPoint *borrar2;

    VisualNode* nodo1;
    VisualNode* nodo2;
    int cont=0;

    explicit GraphView(QWidget *parent) : QGraphicsView(parent) {
        setGeometry(10,0,parent->width(),parent->height());
        scene = new QGraphicsScene(this);
        AQP = nullptr;
        setScene(scene);
        borrar1 = borrar2 = nullptr;
        nodo1 = nodo2 = nullptr;

    }

    void generate_graph(int nodos_){
        if(!AQP) delete AQP;
        AQP = new CCityGraph;

        AQP->generadorNodos(nodos_);
        AQP->generadorEdges(nodos_*4,3);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Holaa...");
        msgBox.setText("...generaste un grafo ");
        msgBox.exec();
    }

    void print_graph(){
        QPen pen;
        pen.setWidth(2);
        for(uint i=0;i<AQP->m_nodes.size();i++){
            VisualNode* tmp = new VisualNode(AQP->m_nodes[i]);
            scene->addItem(tmp);
        //scene->addEllipse(AQP->m_nodes[i]->m_data.x(),AQP->m_nodes[i]->m_data.y(),2,2,pen);
        /// scene.addEllipse(randInt(3,400),randInt(3,500),1,1,pen);
         pen.setBrush(Qt::blue);
         pen.setWidth(1);
         for(uint j=0;j<AQP->m_nodes[i]->m_nedges.size();j++){
             scene->addLine(QLineF(AQP->m_nodes[i]->m_nedges[j]->m_node[0]->m_data.x(),
                           AQP->m_nodes[i]->m_nedges[j]->m_node[0]->m_data.y(),
                           AQP->m_nodes[i]->m_nedges[j]->m_node[1]->m_data.x(),
                           AQP->m_nodes[i]->m_nedges[j]->m_node[1]->m_data.y()),pen);
         }
         pen.setWidth(2);
         pen.setBrush(Qt::black);
        }

    }


    void graficarRuta(list<CCityGraph::Node*> ruta)
    {
        if(ruta.empty()){qDebug()<<"ruta vacia"; return;}
        list<CCityGraph::Node*>::iterator it, itplus;
        it = itplus = ruta.begin();
        itplus++;
        QPen pen(Qt::red, 2);
        while (itplus != ruta.end() )
        {
            scene->addLine((*it)->m_data.x(), (*it)->m_data.y(),
                (*itplus)->m_data.x(), (*itplus)->m_data.y(), pen);
            it = itplus;
            itplus++;
        }
    }



    void mousePressEvent(QMouseEvent *event){

        QPointF mousePoint = mapToScene(event->pos());
        QGraphicsItem* ptr = itemAt(mousePoint.toPoint());
        if(ptr) qDebug() << "PTR" << ptr ;
        VisualNode* pp = dynamic_cast<VisualNode*>(ptr);
        if(event->button() == Qt::RightButton){
            qDebug() << "ri_button";
            if(!borrar1){
                borrar1 = new QPoint();
                *borrar1 = mousePoint.toPoint();
            }
            else{
                    borrar2 = new QPoint();
                    *borrar2 = mousePoint.toPoint();
                    AQP->borrarNodes(borrar1,borrar2);
                    scene->clear();
                    print_graph();
                    update();
                    scene->addRect(QRectF(QPointF(*borrar1),QPointF(*borrar2)));
                    update();
                    delete borrar1;
                    delete borrar2;
                    borrar1 = borrar2 = nullptr;
                }
            }

        if(event->button() == Qt::LeftButton){
            if(pp){
                qDebug() << "XY NODO: "<<pp->punto.x() << ", " << pp->punto.y();
                qDebug() << "PTR NODO:" << pp->realNode;
                if(!nodo1){
                    nodo1 = pp;
                }
                else{
                        nodo2 = pp;

                        list<CCityGraph::Node*> ruta;
                        qDebug()<< "Dijstra";
                        AQP->dijkstra(nodo1->realNode,nodo2->realNode, ruta);
                        //AQP->dijstra2(nodo1->realNode,nodo2->realNode, ruta);
                        qDebug()<< "... finish";
                        scene->clear();
                        print_graph();
                        graficarRuta(ruta);
                        update();
                        nodo1 = nodo2 = nullptr;
                    }
            }
        }
    }


};



#endif // MYVIEW_H
