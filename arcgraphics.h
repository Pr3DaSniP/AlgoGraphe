#ifndef ARCGRAPHICS_H
#define ARCGRAPHICS_H

#include <QGraphicsLineItem>
#include <sommetgraphics.h>

class ArcGraphics : public QGraphicsLineItem
{
    ArcGraphics(SommetGraphics *startItem, SommetGraphics *endItem, QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color) { myColor = color; }
    SommetGraphics *startItem() const { return myStartItem; }
    SommetGraphics *endItem() const { return myEndItem; }

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    SommetGraphics *myStartItem;
    SommetGraphics *myEndItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::black;
};

#endif // ARCGRAPHICS_H
