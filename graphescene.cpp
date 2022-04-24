#include "graphescene.h"
#include <QDebug>
#include <sstream>
#include <time.h>

GrapheScene::GrapheScene(GrapheOriente* graph, QObject *parent)
    : QGraphicsScene(parent)
{
    d_grapheOriente = graph; d_isOriente = true; d_isValue = false; d_isArbre = false;
    createNode();
    ajouteNodes();
    createArc();
    ajouteArcs();
    ajouteNumero();
}

GrapheScene::GrapheScene(GrapheOrienteValue* graph, QObject *parent)
    : QGraphicsScene(parent)
{
    d_grapheOrienteValue = graph; d_isOriente = true; d_isValue = true; d_isArbre = false;
    createNode();
    ajouteNodes();
    createArc();
    ajouteArcs();
    ajouteNumero();
}

GrapheScene::GrapheScene(GrapheNonOriente* graph, QObject *parent)
    : QGraphicsScene(parent)
{
    d_grapheNonOriente = graph; d_isOriente = false; d_isValue = false; d_isArbre = false;
    createNode();
    ajouteNodes();
    createArc();
    ajouteArcs();
    ajouteNumero();
}

GrapheScene::GrapheScene(GrapheNonOrienteValue* graph, QObject *parent)
    : QGraphicsScene(parent)
{
    d_grapheNonOrienteValue = graph; d_isOriente = false; d_isValue = true; d_isArbre = false;
    createNode();
    ajouteNodes();
    createArc();
    ajouteArcs();
    ajouteNumero();
}

GrapheScene::GrapheScene(Arbre* graph, QObject *parent)
    : QGraphicsScene(parent)
{
    d_arbre = graph; d_isOriente = false; d_isValue = false; d_isArbre = true;
    createNode();
    ajouteNodes();
    createArc();
    ajouteArcs();
    ajouteNumero();
}

QPoint GrapheScene::creePointAleatoireEntre(int x1, int y1, int x2, int y2, int n) {
    int incrementationX = (x2 / n) * 1.5 + 100;
    int incrementationY = (y2 / n) * 1.5 + 100;
    int x = x1 + (int) ((float)rand() * (x2+incrementationX - x1+incrementationX+1) / (RAND_MAX-1));
    int y = y1 + (int) ((float)rand() * (y2+incrementationY - y1+incrementationY+1) / (RAND_MAX-1));

    return QPoint(x,y);
}

QList<AreteGraphics*> GrapheScene::getArcs() {
    return d_listeAretes;
}

QList<SommetGraphics*> GrapheScene::getSommets() {
    return d_listeSommets;
}

QList<QColor> GrapheScene::getColors() {
    return d_colors;
}

void GrapheScene::createNode() {

    int x1 = 0;
    int y1 = 0;
    int x2 = 300;
    int y2 = 300;

    if(d_isArbre) {
        int n = d_arbre->getNBSOMMETS();
        for(int i = 1; i <= n; ++i) {
            auto *t = new SommetGraphics(i);
            t->setPos(creePointAleatoireEntre(x1,y1,x2,y2,n));
            d_listeSommets.append(t);
        }
    } else if (d_isValue) {
        if(d_isOriente) {
            int n = d_grapheOrienteValue->getNBSOMMETS();
            for(int i = 1; i <= n ; ++i) {
                auto *t = new SommetGraphics(i);
                t->setPos(creePointAleatoireEntre(x1,y1,x2,y2,n));
                d_listeSommets.append(t);
            }
        } else {
            int n = d_grapheNonOrienteValue->getNBSOMMETS();
            for(int i = 1; i <= n; ++i) {
                auto *t = new SommetGraphics(i);
                t->setPos(creePointAleatoireEntre(x1,y1,x2,y2,n));
                d_listeSommets.append(t);
            }
        }
    } else {
        if(d_isOriente) {
            int n = d_grapheOriente->getNBSOMMETS();
            for(int i = 1; i <= n; ++i) {
                auto *t = new SommetGraphics(i);
                t->setPos(creePointAleatoireEntre(x1,y1,x2,y2,n));
                d_listeSommets.append(t);
            }
        } else {
            int n = d_grapheNonOriente->getNBSOMMETS();
            for(int i = 1; i <= n; ++i) {
                auto *t = new SommetGraphics(i);
                t->setPos(creePointAleatoireEntre(x1,y1,x2,y2,n));
                d_listeSommets.append(t);
            }
        }
    }
}

void GrapheScene::ajouteNodes() {
    for(int i = 0; i < d_listeSommets.size(); ++i) {
        addItem(d_listeSommets[i]);
    }
}

void GrapheScene::createArc() {
    vector<vector<int>> matrice, cost;

    if(d_isArbre) {
        matrice = d_arbre->getMATRICEADJACENCE();
    } else if (d_isValue) {
        if(d_isOriente) {
            matrice = d_grapheOrienteValue->getMATRICEADJACENCE();
            cost = d_grapheOrienteValue->get_COST();
        } else {
            matrice = d_grapheNonOrienteValue->getMATRICEADJACENCE();
            cost = d_grapheNonOrienteValue->get_COST();
        }
    } else {
        if(d_isOriente) {
            matrice = d_grapheOriente->getMATRICEADJACENCE();
        } else {
            matrice = d_grapheNonOriente->getMATRICEADJACENCE();
        }
    }

    for(unsigned int i = 1; i < matrice.size(); ++i) {
        for(unsigned int j = 1; j < matrice[i].size(); ++j) {
            if(matrice[i][j] == 1) {
                int cout = d_isValue ? cost[i][j] : 0;
                AreteGraphics* A = new AreteGraphics{d_listeSommets[i-1], d_listeSommets[j-1], cout};
                d_listeAretes.append(A);
            }
        }
    }
}

void GrapheScene::ajouteArcs() {
    for(int i = 0; i < d_listeAretes.size(); ++i) {
        int x1 = d_listeAretes[i]->getxMilieuParent();
        int y1 = d_listeAretes[i]->getyMilieuParent();
        int x2 = d_listeAretes[i]->getxMilieuEnfant();
        int y2 = d_listeAretes[i]->getyMilieuEnfant();
        addLine(x1,y1,x2,y2,{Qt::black});
        int mx = (x1+x2)/2;
        int my = (y1+y2)/2;
        if(d_isValue) {
            auto* ctext = new QGraphicsTextItem(QString::number(d_listeAretes[i]->getPoids()));
            ctext->setPos(mx, my);
            ctext->setDefaultTextColor(Qt::blue);
            addItem(ctext);
        }
    }
}

void GrapheScene::ajouteNumero() {
    for(int i = 0; i < d_listeSommets.size(); ++i){
        auto *text = new QGraphicsTextItem{QString::number((i + 1))};
        text->setPos(d_listeSommets[i]->getX()-10, d_listeSommets[i]->y()+15);
        text->setZValue(91);
        text->setDefaultTextColor(Qt::red);
        addItem(text);
    }
}
