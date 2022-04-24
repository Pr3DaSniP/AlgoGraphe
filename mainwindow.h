#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "graphescene.h"

#include "GrapheOriente.h"
#include "GrapheOrienteValue.h"
#include "GrapheNonOriente.h"
#include "GrapheNonOrienteValue.h"
#include "Arbre.h"

#include "dialogdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QDialog
{
    Q_OBJECT

public:
    mainwindow(GrapheOriente* graphe, QWidget *parent = nullptr);
    mainwindow(GrapheOrienteValue* graphe, QWidget *parent = nullptr);
    mainwindow(GrapheNonOriente* graphe, QWidget *parent = nullptr);
    mainwindow(GrapheNonOrienteValue* graphe, QWidget *parent = nullptr);
    mainwindow(Arbre* arbre ,QWidget *parent = nullptr);
    ~mainwindow();

    void init();

private slots:
    void onDonnee();
    void onTarjan();
    void onOrdonnancement();
    void onDijkstra();
    void onDantzig();
    void onKruskal();
    void onPrufer();
    void onCreate();
    void onAppli();
    void onAPropos();
    void onLoad();
    void onReset();

private:
    void desacBoutons();
    int getMin(vector<int>& S, vector<bool>& visited);

    Ui::mainwindow *ui;
    GrapheScene* d_scene;
    dialogData* d_dialog;

    GrapheOriente* d_grapheOriente;
    GrapheOrienteValue* d_grapheOrienteValue;
    GrapheNonOriente* d_grapheNonOriente;
    GrapheNonOrienteValue* d_grapheNonOrienteValue;
    Arbre* d_arbre;
    bool d_isValue, d_isOriente, d_isArbre;
};
#endif // MAINWINDOW_H
