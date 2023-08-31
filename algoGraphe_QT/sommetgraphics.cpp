#include "sommetgraphics.h"
#include <QBrush>
#include <QPen>

SommetGraphics::SommetGraphics(int id)
{
    d_id = id;
    setRect(0,0,25,25);
    setPen(QPen(Qt::black));
    setZValue(90);
    setBrush(QBrush(Qt::white));
}

int SommetGraphics::getId() {
    return d_id;
}

int SommetGraphics::getX() {
    return QGraphicsEllipseItem::x();
}

int SommetGraphics::getY() {
    return QGraphicsEllipseItem::x();
}

QRectF SommetGraphics::boundingRect() const {
    return QGraphicsEllipseItem::boundingRect();
}

QPointF SommetGraphics::getPos() const {
    return {QGraphicsEllipseItem::pos().x(), QGraphicsEllipseItem::pos().y()};
}
