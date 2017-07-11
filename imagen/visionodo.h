#ifndef VISIONODO_H
#define VISIONODO_H


#include <QGraphicsItem>
#include<list>
#include <QPainter>
#include <QDebug>

#include "ccitygraph.h"

class VisualNode : public QGraphicsItem{

public:
    QPointF &punto;
    CCityGraph:: Node * realNode;
    bool pressed;

    VisualNode(CCityGraph::Node *node): punto(node->m_data) {
        realNode = node;
    }

    QRectF boundingRect() const{
        return QRectF(punto.x()-4,punto.y()-4, 6,6);
  }

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget ){
        painter->setBrush(Qt::red);
        QPen pen(Qt::black, 1);
        painter->setPen(pen);
        painter->drawEllipse(punto,4,4);
    }


};


#endif // VISIONODO_H
