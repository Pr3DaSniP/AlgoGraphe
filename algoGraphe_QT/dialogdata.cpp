#include "dialogdata.h"

#include <sstream>
#include <QBoxLayout>
#include <QLabel>

dialogData::dialogData() {
    vue_cree();
}

void dialogData::vue_cree() {
    auto layout_un = new QVBoxLayout;

    layout_un->addWidget(new QLabel{"FS :"});
    layout_un->addWidget(d_fs = new QLabel{""});
    layout_un->addWidget(new QLabel{"APS :"});
    layout_un->addWidget(d_aps = new QLabel{""});
    layout_un->addWidget(new QLabel{"DDI :"});
    layout_un->addWidget(d_ddi = new QLabel{""});
    layout_un->addWidget(new QLabel{"DDE :"});
    layout_un->addWidget(d_dde = new QLabel{""});
    layout_un->addWidget(new QLabel{"Matrice d'adjacence :"});
    layout_un->addWidget(d_matAdj = new QLabel{""});

    auto layout_deux = new QVBoxLayout;

    layout_deux->addWidget(new QLabel{"Matrice des distances :"});
    layout_deux->addWidget(d_matDist = new QLabel{""});
    layout_deux->addWidget(new QLabel{"FP :"});
    layout_deux->addWidget(d_fp = new QLabel{""});
    layout_deux->addWidget(new QLabel{"APP :"});
    layout_deux->addWidget(d_app = new QLabel{""});
    layout_deux->addWidget(new QLabel{"RANG : "});
    layout_deux->addWidget(d_rang = new QLabel{""});

    auto layout_trois = new QVBoxLayout;

    layout_trois->addWidget(new QLabel{"Tarjan NUM :"});
    layout_trois->addWidget(d_tarjan_num = new QLabel{""});
    layout_trois->addWidget(new QLabel{"Tarjan PREM :"});
    layout_trois->addWidget(d_tarjan_prem = new QLabel{""});
    layout_trois->addWidget(new QLabel{"Tarjan PILCH :"});
    layout_trois->addWidget(d_tarjan_pilch = new QLabel{""});
    layout_trois->addWidget(new QLabel{"Tarjan CFC :"});
    layout_trois->addWidget(d_tarjan_cfc = new QLabel{""});

    auto layout_quatre = new QVBoxLayout;

    layout_quatre->addWidget(new QLabel{"FSR :"});
    layout_quatre->addWidget(d_fsr = new QLabel{""});
    layout_quatre->addWidget(new QLabel{"APSR :"});
    layout_quatre->addWidget(d_apsr = new QLabel{""});
    layout_quatre->addWidget(new QLabel{"BR :"});
    layout_quatre->addWidget(d_br = new QLabel{""});
    layout_quatre->addWidget(new QLabel{"Prufer :"});
    layout_quatre->addWidget(d_prufer_code = new QLabel{""});

    auto layout_cinq = new QVBoxLayout;

    layout_cinq->addWidget(new QLabel{"COUT :"});
    layout_cinq->addWidget(d_cost = new QLabel{""});
    layout_cinq->addWidget(new QLabel{"Kruskal PREM :"});
    layout_cinq->addWidget(d_kruskal_prem = new QLabel{""});
    layout_cinq->addWidget(new QLabel{"Kruskal PILCH :"});
    layout_cinq->addWidget(d_kruskal_pilch = new QLabel{""});
    layout_cinq->addWidget(new QLabel{"Kruskal CFC :"});
    layout_cinq->addWidget(d_kruskal_cfc = new QLabel{""});

    auto layout_six = new QVBoxLayout;

    layout_six->addWidget(new QLabel{"FPC : "});
    layout_six->addWidget(d_fpc = new QLabel{""});
    layout_six->addWidget(new QLabel{"APPC : "});
    layout_six->addWidget(d_appc = new QLabel{""});
    layout_six->addWidget(new QLabel{"LC : "});
    layout_six->addWidget(d_lc = new QLabel{""});

    auto layout_sept = new QVBoxLayout;

    layout_sept->addWidget(new QLabel{"Dijkstra D :"});
    layout_sept->addWidget(d_dijkstra_d = new QLabel{""});
    layout_sept->addWidget(new QLabel{"Dijkstra PRED :"});
    layout_sept->addWidget(d_dijkstra_pred = new QLabel{""});
    layout_sept->addWidget(new QLabel{"Dantzig COUT :"});
    layout_sept->addWidget(d_dantzig_cost = new QLabel{""});

    auto layoutPrincipal = new QHBoxLayout;

    layoutPrincipal->addLayout(layout_un);

    QFrame * line = new QFrame;
    line->setGeometry(QRect(160, 150, 3, 61));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    layoutPrincipal->addWidget(line);

    layoutPrincipal->addLayout(layout_deux);

    QFrame * line2 = new QFrame;
    line2->setGeometry(QRect(160, 150, 3, 61));
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);
    layoutPrincipal->addWidget(line2);

    layoutPrincipal->addLayout(layout_trois);

    QFrame * line3 = new QFrame;
    line3->setGeometry(QRect(160, 150, 3, 61));
    line3->setFrameShape(QFrame::VLine);
    line3->setFrameShadow(QFrame::Sunken);
    layoutPrincipal->addWidget(line3);

    layoutPrincipal->addLayout(layout_quatre);

    QFrame * line4 = new QFrame;
    line4->setGeometry(QRect(160, 150, 3, 61));
    line4->setFrameShape(QFrame::VLine);
    line4->setFrameShadow(QFrame::Sunken);
    layoutPrincipal->addWidget(line4);

    layoutPrincipal->addLayout(layout_cinq);

    QFrame * line5 = new QFrame;
    line5->setGeometry(QRect(160, 150, 3, 61));
    line5->setFrameShape(QFrame::VLine);
    line5->setFrameShadow(QFrame::Sunken);
    layoutPrincipal->addWidget(line5);

    layoutPrincipal->addLayout(layout_six);

    QFrame * line6 = new QFrame;
    line6->setGeometry(QRect(160, 150, 3, 61));
    line6->setFrameShape(QFrame::VLine);
    line6->setFrameShadow(QFrame::Sunken);
    layoutPrincipal->addWidget(line6);

    layoutPrincipal->addLayout(layout_sept);

    setLayout(layoutPrincipal);
}

void dialogData::setData(GrapheOriente* graphe) {
    d_grapheOriente = graphe; d_isOriente = true; d_isValue = false; d_isArbre = false;
}

void dialogData::setData(GrapheOrienteValue* graphe) {
    d_grapheOrienteValue = graphe; d_isOriente = true; d_isValue = true; d_isArbre = false;
}

void dialogData::setData(GrapheNonOriente* graphe) {
    d_grapheNonOriente = graphe; d_isOriente = false; d_isValue = false; d_isArbre = false;
}

void dialogData::setData(GrapheNonOrienteValue* graphe) {
    d_grapheNonOrienteValue = graphe; d_isOriente = false; d_isValue = true; d_isArbre = false;
}

void dialogData::setData(Arbre* arbre) {
    d_arbre = arbre; d_isOriente = false; d_isValue = false; d_isArbre = true;
}

QString dialogData::convertTabToQString(vector<int> tab) {
    std::stringstream s;
    for(int i = 1; i < tab.size(); ++i) {
        if(tab[i] > 2000000000)
            s << "INF ";
        else if(tab[i] < -2000000000)
            s << "-INF ";
        else
            s << tab[i] << " ";
    }
    return QString::fromStdString(s.str());
}

QString dialogData::convertTabToQString(vector<vector<int>> tab) {
    std::stringstream s;
    for(int i = 1; i < tab.size(); ++i) {
        for(int j = 1; j < tab[i].size(); ++j) {
            if(tab[i][j] > 2000000000)
                s << "INF\t";
            else if(tab[i][j] < -2000000000)
                s << "-INF\t";
            else
                s << tab[i][j] << "\t";
        }
        s << "\n";
    }
    return QString::fromStdString(s.str());
}


void dialogData::setFS(vector<int> FS) {
    d_fs->setText(convertTabToQString(FS));
}

void dialogData::setAPS(vector<int> APS) {
    d_aps->setText(convertTabToQString(APS));
}

void dialogData::setDDI(vector<int> DDI) {
    d_ddi->setText(convertTabToQString(DDI));
}

void dialogData::setDDE(vector<int> DDE) {
    d_dde->setText(convertTabToQString(DDE));
}

void dialogData::setMatriceAdjacence(vector<vector<int>> MatAdjacence) {
    d_matAdj->setText(convertTabToQString(MatAdjacence));
}

void dialogData::setMatriceDistance(vector<vector<int>> MatDistance) {
    d_matDist->setText(convertTabToQString(MatDistance));
}

void dialogData::setFP(vector<int> FP) {
    d_fp->setText(convertTabToQString(FP));
}

void dialogData::setAPP(vector<int> APP) {
    d_app->setText(convertTabToQString(APP));
}

void dialogData::setRang(vector<int> Rang) {
    d_rang->setText(convertTabToQString(Rang));
}

void dialogData::setTarjan_NUM(vector<int> Tarjan_num) {
    d_tarjan_num->setText(convertTabToQString(Tarjan_num));
}

void dialogData::setTarjan_PREM(vector<int> Tarjan_prem) {
    d_tarjan_prem->setText(convertTabToQString(Tarjan_prem));
}

void dialogData::setTarjan_PILCH(vector<int> Tarjan_pilch) {
    d_tarjan_pilch->setText(convertTabToQString(Tarjan_pilch));
}

void dialogData::setTarjan_CFC(vector<int> Tarjan_cfc) {
    d_tarjan_cfc->setText(convertTabToQString(Tarjan_cfc));
}

void dialogData::setFSR(vector<int> FSR) {
    d_fsr->setText(convertTabToQString(FSR));
}

void dialogData::setAPSR(vector<int> APSR) {
    d_apsr->setText(convertTabToQString(APSR));
}

void dialogData::setBR(vector<int> BR) {
    d_br->setText(convertTabToQString(BR));
}

void dialogData::setCOST(vector<vector<int>> Cost) {
    d_cost->setText(convertTabToQString(Cost));
}

void dialogData::setKruskal_PREM(vector<int> Kruskal_prem) {
    d_kruskal_prem->setText(convertTabToQString(Kruskal_prem));
}

void dialogData::setKruskal_PILCH(vector<int> Kruskal_pilch) {
    d_kruskal_pilch->setText(convertTabToQString(Kruskal_pilch));
}

void dialogData::setKruskal_CFC(vector<int> Kruskal_cfc) {
    d_kruskal_cfc->setText(convertTabToQString(Kruskal_cfc));
}

void dialogData::setFPC(vector<int> FPC) {
    d_fpc->setText(convertTabToQString(FPC));
}

void dialogData::setAPPC(vector<int> APPC) {
    d_appc->setText(convertTabToQString(APPC));
}

void dialogData::setLC(vector<int> LC) {
    d_lc->setText(convertTabToQString(LC));
}

void dialogData::setDijkstra_D(vector<int> Dijkstra_d) {
    d_dijkstra_d->setText(convertTabToQString(Dijkstra_d));
}

void dialogData::setDijkstra_PRED(vector<int> Dijkstra_pred) {
    d_dijkstra_pred->setText(convertTabToQString(Dijkstra_pred));
}

void dialogData::setDantzig_COST(vector<vector<int>> Dantzig_Cost) {
    d_dantzig_cost->setText(convertTabToQString(Dantzig_Cost));
}


void dialogData::setPruferCode(vector<int> prufer_code) {
    d_prufer_code->setText(convertTabToQString(prufer_code));
}
