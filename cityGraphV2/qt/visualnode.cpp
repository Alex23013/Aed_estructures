#include "visualnode.h"
#include <QPainter>
#include <QDebug>
VisualNode::VisualNode(CityGraph::Node *node): punto(node->data) {
    realNode = node;
}

QRectF VisualNode::boundingRect() const{
    return QRectF(punto.x()-3,punto.y()-3, 6,6);
}

void VisualNode::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget ){
    QRectF rect = boundingRect();

    painter->setBrush(Qt::red);
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    painter->drawEllipse(punto,3,3);

}
