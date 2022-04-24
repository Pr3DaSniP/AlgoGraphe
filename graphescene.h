#ifndef GRAPHESCENE_H
#define GRAPHESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QList>

#include "sommetgraphics.h"
#include "aretegraphics.h"

#include "GrapheOriente.h"
#include "GrapheOrienteValue.h"
#include "GrapheNonOriente.h"
#include "GrapheNonOrienteValue.h"
#include "Arbre.h"


class GrapheScene : public QGraphicsScene
{
public:
    GrapheScene(GrapheOriente* graph, QObject *parent = nullptr);
    GrapheScene(GrapheOrienteValue* graph, QObject *parent = nullptr);
    GrapheScene(GrapheNonOriente* graph, QObject *parent = nullptr);
    GrapheScene(GrapheNonOrienteValue* graph, QObject *parent = nullptr);
    GrapheScene(Arbre* graph, QObject *parent = nullptr);

    QList<AreteGraphics*> getArcs();
    QList<SommetGraphics*> getSommets();
    QList<QColor> getColors();
private:
    void createNode();
    void ajouteNodes();
    void createArc();
    void ajouteArcs();
    void ajouteNumero();

    QPoint creePointAleatoireEntre(int x1, int y1, int x2, int y2, int n);

    GrapheOriente* d_grapheOriente;
    GrapheOrienteValue* d_grapheOrienteValue;
    GrapheNonOriente* d_grapheNonOriente;
    GrapheNonOrienteValue* d_grapheNonOrienteValue;
    Arbre* d_arbre;
    bool d_isValue, d_isOriente, d_isArbre;

    QList<SommetGraphics*> d_listeSommets;
    QList<AreteGraphics*> d_listeAretes;

    QList<QColor> d_colors = {
        Qt::cyan, Qt::darkCyan,
        Qt::red, Qt::darkRed, Qt::magenta, Qt::darkMagenta,
        Qt::green, Qt::darkGreen, Qt::yellow, Qt::darkYellow,
        Qt::blue, Qt::darkBlue, Qt::gray, Qt::darkGray,
        Qt::lightGray, Qt::white, Qt::black
    };
};

#endif // GRAPHESCENE_H
