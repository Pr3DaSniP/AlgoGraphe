#ifndef SOMMETGRAPHICS_H
#define SOMMETGRAPHICS_H

#include <QGraphicsEllipseItem>

class SommetGraphics : public QGraphicsEllipseItem
{
public:
    SommetGraphics(int id);

    int getX();
    int getY();
    int getId();
    QRectF boundingRect() const;
    QPointF getPos() const;

private:
    int d_id;
};

#endif // SOMMETGRAPHICS_H
