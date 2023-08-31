#ifndef ARETEGRAPHICS_H
#define ARETEGRAPHICS_H

#include <QGraphicsLineItem>
#include "sommetgraphics.h"

class AreteGraphics : QGraphicsLineItem
{
public:
    AreteGraphics(SommetGraphics* parent, SommetGraphics* enfant, int poids);

    SommetGraphics* getParent();
    SommetGraphics* getEnfant();
    int getxMilieuParent();
    int getyMilieuParent();
    int getxMilieuEnfant();
    int getyMilieuEnfant();
    int getPoids();
private:
    int d_poids;
    int d_xMilieuParent;
    int d_yMilieuParent;
    int d_xMilieuEnfant;
    int d_yMilieuEnfant;
    SommetGraphics* d_parent;
    SommetGraphics* d_enfant;
};

#endif // ARETEGRAPHICS_H
