#include "aretegraphics.h"

#include <QDebug>
#include <QPainter>
#include <cmath>

#include <QPainter>

AreteGraphics::AreteGraphics(SommetGraphics* parent, SommetGraphics* enfant, int poids)
{
    d_parent = parent; d_enfant = enfant; d_poids = poids;
    d_xMilieuParent = d_parent->x()+(d_parent->boundingRect().width()/2);
    d_yMilieuParent = d_parent->y()+(d_parent->boundingRect().height()/2);

    d_xMilieuEnfant = d_enfant->x()+(d_enfant->boundingRect().width()/2);
    d_yMilieuEnfant = d_enfant->y()+(d_enfant->boundingRect().height()/2);
}

int AreteGraphics::getPoids() {
    return d_poids;
}

SommetGraphics* AreteGraphics::getParent() {
    return d_parent;
}

SommetGraphics* AreteGraphics::getEnfant() {
    return d_enfant;
}

int AreteGraphics::getxMilieuParent() {
    return d_xMilieuParent;
}

int AreteGraphics::getyMilieuParent() {
    return d_yMilieuParent;
}

int AreteGraphics::getxMilieuEnfant() {
    return d_xMilieuEnfant;
}

int AreteGraphics::getyMilieuEnfant() {
    return d_yMilieuEnfant;
}
