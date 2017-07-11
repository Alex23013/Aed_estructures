#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "visualnode.h"
#include "grafo/citygraph.h"

class GraphView : public QGraphicsView {
    Q_OBJECT
public:
    CityGraph *grafo;
    QGraphicsScene *scene;

    QPoint *borrar1;
    QPoint *borrar2;

    VisualNode* nodo1;
    VisualNode* nodo2;

    explicit GraphView(QWidget *parent);
    void genGraph();
    bool printGraph();

    void mousePressEvent(QMouseEvent *event);

    //DIJKSTRA
    void graficarRuta(list<CityGraph::Node*> ruta);

};

#endif // GRAPHVIEW_H
