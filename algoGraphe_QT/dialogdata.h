#ifndef DIALOGDATA_H
#define DIALOGDATA_H

#include <QDialog>
#include <QLabel>

#include "GrapheOriente.h"
#include "GrapheOrienteValue.h"
#include "GrapheNonOriente.h"
#include "GrapheNonOrienteValue.h"
#include "Arbre.h"

class dialogData : public QDialog
{
public:
    dialogData();

    void vue_cree();


    void setFS(vector<int> FS);
    void setAPS(vector<int> APS);
    void setDDI(vector<int> DDI);
    void setDDE(vector<int> DDE);
    void setMatriceAdjacence(vector<vector<int>> MatAdjacence);

    void setMatriceDistance(vector<vector<int>> MatDistance);
    void setFP(vector<int> FP);
    void setAPP(vector<int> APP);
    void setRang(vector<int> Rang);
    void setTarjan_NUM(vector<int> Tarjan_num);

    void setTarjan_PREM(vector<int> Tarjan_prem);
    void setTarjan_PILCH(vector<int> Tarjan_pilch);
    void setTarjan_CFC(vector<int> Tarjan_cfc);
    void setFSR(vector<int> FSR);
    void setAPSR(vector<int> APSR);

    void setBR(vector<int> BR);
    void setCOST(vector<vector<int>> Cost);
    void setKruskal_PREM(vector<int> Kruskal_prem);
    void setKruskal_PILCH(vector<int> Kruskal_pilch);
    void setKruskal_CFC(vector<int> Kruksal_cfc);

    void setFPC(vector<int> FPC);
    void setAPPC(vector<int> APPC);
    void setLC(vector<int> LC);
    void setDijkstra_D(vector<int> Dijkstra_d);
    void setDijkstra_PRED(vector<int> Dijkstra_pred);
    void setDantzig_COST(vector<vector<int>> Dantzig_Cost);

    void setPruferCode(vector<int> prufer_code);

    void setData(GrapheOriente* graphe);
    void setData(GrapheOrienteValue* graphe);
    void setData(GrapheNonOriente* graphe);
    void setData(GrapheNonOrienteValue* graphe);
    void setData(Arbre* arbre);
private:
    QString convertTabToQString(vector<int> tab);
    QString convertTabToQString(vector<vector<int>> tab);

    GrapheOriente* d_grapheOriente;
    GrapheOrienteValue* d_grapheOrienteValue;
    GrapheNonOriente* d_grapheNonOriente;
    GrapheNonOrienteValue* d_grapheNonOrienteValue;
    Arbre* d_arbre;
    bool d_isValue, d_isOriente, d_isArbre;

    QLabel* d_fs;
    QLabel* d_aps;
    QLabel* d_ddi;
    QLabel* d_dde;
    QLabel* d_matAdj;

    QLabel* d_matDist;
    QLabel* d_fp;
    QLabel* d_app;
    QLabel* d_rang;
    QLabel* d_tarjan_num;

    QLabel* d_tarjan_prem;
    QLabel* d_tarjan_pilch;
    QLabel* d_tarjan_cfc;
    QLabel* d_fsr;
    QLabel* d_apsr;

    QLabel* d_br;
    QLabel* d_cost;
    QLabel* d_kruskal_prem;
    QLabel* d_kruskal_pilch;
    QLabel* d_kruskal_cfc;

    QLabel* d_fpc;
    QLabel* d_appc;
    QLabel* d_lc;
    QLabel* d_dijkstra_d;
    QLabel* d_dijkstra_pred;
    QLabel* d_dantzig_cost;

    QLabel* d_prufer_code;
};

#endif // DIALOGDATA_H
