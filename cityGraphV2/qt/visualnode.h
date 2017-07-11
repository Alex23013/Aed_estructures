#ifndef VISUALNODE_H
#define VISUALNODE_H

#include <QGraphicsItem>
#include "grafo/citygraph.h"

class VisualNode : public QGraphicsItem{

public:
    QPointF &punto;
    CityGraph::Node * realNode;
    bool pressed;

    VisualNode(CityGraph::Node *node);

    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);


};

#endif // VISUALNODE_H
