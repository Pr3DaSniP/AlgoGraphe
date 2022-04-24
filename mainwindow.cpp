#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogdata.h"
#include <sstream>

#include <QDebug>

#include <QInputDialog>
#include <QMessageBox>

mainwindow::mainwindow(GrapheOriente* graphe,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainwindow)
{
    d_grapheOriente = graphe; d_isOriente = true; d_isValue = false; d_isArbre = false;
    init();
}

mainwindow::mainwindow(GrapheNonOriente* graphe,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainwindow)
{
    d_grapheNonOriente = graphe; d_isOriente = false; d_isValue = false; d_isArbre = false;
    init();
}

mainwindow::mainwindow(GrapheNonOrienteValue* graphe,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainwindow)
{
    d_grapheNonOrienteValue = graphe; d_isOriente = false; d_isValue = true; d_isArbre = false;
    init();
}

mainwindow::mainwindow(GrapheOrienteValue* graphe,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainwindow)
{
    d_grapheOrienteValue = graphe; d_isOriente = true; d_isValue = true; d_isArbre = false;
    init();
}

mainwindow::mainwindow(Arbre* arbre,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainwindow)
{
    d_arbre = arbre; d_isOriente = false; d_isValue = false; d_isArbre = true;
    init();
}

void mainwindow::desacBoutons() {
    ui->btnTarjan->setEnabled(false);
    ui->btnOrdonnancement->setEnabled(false);
    ui->btnDijkstra->setEnabled(false);
    ui->btnDantzig->setEnabled(false);
    ui->btnKruskal->setEnabled(false);
    ui->btnPrufer->setEnabled(false);
}

void mainwindow::init() {
    ui->setupUi(this);

    desacBoutons();

    d_dialog = new dialogData{};

    if(d_isArbre) {
        d_scene = new GrapheScene{d_arbre};
        d_dialog->setData(d_arbre);
        ui->btnPrufer->setEnabled(true);
        ui->lblType->setText("Arbre");
    } else if (d_isValue) {
        if(d_isOriente) {
            d_scene = new GrapheScene{d_grapheOrienteValue};
            d_dialog->setData(d_grapheOrienteValue);
            ui->btnDijkstra->setEnabled(true);
            ui->btnDantzig->setEnabled(true);
            ui->btnOrdonnancement->setEnabled(true);
            ui->btnTarjan->setEnabled(true);
            ui->lblType->setText("Graphe Orienté Valué");
        } else {
            d_scene = new GrapheScene{d_grapheNonOrienteValue};
            d_dialog->setData(d_grapheNonOrienteValue);
            ui->btnKruskal->setEnabled(true);
            ui->lblType->setText("Graphe Non Orienté Valué");
        }
    } else {
        if(d_isOriente) {
            d_scene = new GrapheScene{d_grapheOriente};
            d_dialog->setData(d_grapheOriente);
            ui->btnTarjan->setEnabled(true);
            ui->lblType->setText("Graphe Orienté");
        } else {
            d_scene = new GrapheScene{d_grapheNonOriente};
            d_dialog->setData(d_grapheNonOriente);
            ui->lblType->setText("Graphe Non Orienté");
        }
    }

    ui->graphicsViewGraphe->setScene(d_scene);
    ui->graphicsViewGraphe->centerOn(0,0);
    ui->graphicsViewGraphe->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    auto list = d_scene->getArcs();
    std::stringstream s_t;
    s_t << "|";
    for(int i = 0; i < list.size(); ++i) {
        s_t << list[i]->getParent()->getId() << " --> " << list[i]->getEnfant()->getId() << " | ";
    }
    ui->lblArcs->setText(QString::fromStdString(s_t.str()));

    connect(ui->btnData, &QPushButton::clicked, this, &mainwindow::onDonnee);
    connect(ui->btnTarjan, &QPushButton::clicked, this, &mainwindow::onTarjan);
    connect(ui->btnOrdonnancement, &QPushButton::clicked, this, &mainwindow::onOrdonnancement);
    connect(ui->btnDijkstra, &QPushButton::clicked, this, &mainwindow::onDijkstra);
    connect(ui->btnDantzig, &QPushButton::clicked, this, &mainwindow::onDantzig);
    connect(ui->btnKruskal, &QPushButton::clicked, this, &mainwindow::onKruskal);
    connect(ui->btnPrufer, &QPushButton::clicked, this, &mainwindow::onPrufer);
    connect(ui->btnCreate, &QPushButton::clicked, this, &mainwindow::onCreate);
    connect(ui->btnAPropos, &QPushButton::clicked, this, &mainwindow::onAPropos);
    connect(ui->btnLoad, &QPushButton::clicked, this, &mainwindow::onLoad);
    connect(ui->btnReset, &QPushButton::clicked, this, &mainwindow::onReset);
}

void mainwindow::onDonnee() {
    d_dialog->setWindowTitle("Donnée du graphe");

    if(d_isArbre) {
        d_dialog->setFS(d_arbre->getFS());
        d_dialog->setAPS(d_arbre->getAPS());
        d_dialog->setMatriceAdjacence(d_arbre->getMATRICEADJACENCE());
    } else if (d_isValue) {
        if(d_isOriente) {
            d_dialog->setFS(d_grapheOrienteValue->getFS());
            d_dialog->setAPS(d_grapheOrienteValue->getAPS());
            d_dialog->setMatriceAdjacence(d_grapheOrienteValue->getMATRICEADJACENCE());
            d_dialog->setFP(d_grapheOrienteValue->getFP());
            d_dialog->setAPP(d_grapheOrienteValue->getAPP());
            d_dialog->setDDI(d_grapheOrienteValue->getDDI());
            d_dialog->setDDE(d_grapheOrienteValue->getDDE());
            d_dialog->setMatriceDistance(d_grapheOrienteValue->getMATRICE_DISTANCE());
            d_dialog->setRang(d_grapheOrienteValue->getRANG());
            d_dialog->setTarjan_NUM(d_grapheOrienteValue->getTARJAN_NUM());
            d_dialog->setTarjan_PREM(d_grapheOrienteValue->getTARJAN_PREM());
            d_dialog->setTarjan_PILCH(d_grapheOrienteValue->getTARJAN_PILCH());
            d_dialog->setTarjan_CFC(d_grapheOrienteValue->getTARJAN_CFC());
            d_dialog->setAPSR(d_grapheOrienteValue->getAPSR());
            d_dialog->setBR(d_grapheOrienteValue->getBR());
            d_dialog->setFPC(d_grapheOrienteValue->getORDONNANCEMENT_FPC());
            d_dialog->setAPPC(d_grapheOrienteValue->getORDONNANCEMENT_APPC());
            d_dialog->setLC(d_grapheOrienteValue->getORDONNANCEMENT_LC());
            d_dialog->setDijkstra_D(d_grapheOrienteValue->getDIJKSTRA_D());
            d_dialog->setDijkstra_PRED(d_grapheOrienteValue->getDIJKSTRA_PRED());
            d_dialog->setCOST(d_grapheOrienteValue->get_COST());
            d_dialog->setDantzig_COST(d_grapheOrienteValue->getDANTZIG_COST());
        } else {
            d_dialog->setFS(d_grapheNonOrienteValue->getFS());
            d_dialog->setAPS(d_grapheNonOrienteValue->getAPS());
            d_dialog->setMatriceAdjacence(d_grapheNonOrienteValue->getMATRICEADJACENCE());
            d_dialog->setCOST(d_grapheNonOrienteValue->get_COST());
            d_dialog->setKruskal_PREM(d_grapheNonOrienteValue->getKRUSKAL_PREM());
            d_dialog->setKruskal_CFC(d_grapheNonOrienteValue->getKRUSKAL_CFC());
            d_dialog->setKruskal_PILCH(d_grapheNonOrienteValue->getKRUSKAL_PILCH());
        }
    } else {
        if(d_isOriente) {
            d_dialog->setFS(d_grapheOriente->getFS());
            d_dialog->setAPS(d_grapheOriente->getAPS());
            d_dialog->setMatriceAdjacence(d_grapheOriente->getMATRICEADJACENCE());
            d_dialog->setFP(d_grapheOriente->getFP());
            d_dialog->setAPP(d_grapheOriente->getAPP());
            d_dialog->setDDI(d_grapheOriente->getDDI());
            d_dialog->setDDE(d_grapheOriente->getDDE());
            d_dialog->setMatriceDistance(d_grapheOriente->getMATRICE_DISTANCE());
            d_dialog->setRang(d_grapheOriente->getRANG());
            d_dialog->setTarjan_NUM(d_grapheOriente->getTARJAN_NUM());
            d_dialog->setTarjan_PREM(d_grapheOriente->getTARJAN_PREM());
            d_dialog->setTarjan_PILCH(d_grapheOriente->getTARJAN_PILCH());
            d_dialog->setTarjan_CFC(d_grapheOriente->getTARJAN_CFC());
            d_dialog->setFSR(d_grapheOriente->getFSR());
            d_dialog->setAPSR(d_grapheOriente->getAPSR());
            d_dialog->setBR(d_grapheOriente->getBR());
        } else {
            d_dialog->setFS(d_grapheNonOriente->getFS());
            d_dialog->setAPS(d_grapheNonOriente->getAPS());
            d_dialog->setMatriceAdjacence(d_grapheNonOriente->getMATRICEADJACENCE());
        }
    }

    d_dialog->exec();
}

void mainwindow::onTarjan() {
    int nbCfc = d_isValue ? d_grapheOrienteValue->getTARJAN_PREM()[0] : d_grapheOriente->getTARJAN_PREM()[0];
    auto prem = d_isValue ? d_grapheOrienteValue->getTARJAN_PREM() : d_grapheOriente->getTARJAN_PREM();
    auto pilch = d_isValue ? d_grapheOrienteValue->getTARJAN_PILCH() : d_grapheOriente->getTARJAN_PILCH();;

    auto sommets = d_scene->getSommets();
    auto colors = d_scene->getColors();

    for (int i = 1; i <= nbCfc; ++i) {
        QPen pen{colors[i]};
        pen.setWidth(3);
        QList<QPointF> arcs;

        int k;
        k = prem[i];
        sommets[k-1]->setBrush(QBrush{colors[i]});
        arcs.append(sommets[k-1]->getPos());
        while (pilch[k] != 0) {
            k = pilch[k];
            sommets[k-1]->setBrush(QBrush{colors[i]});
            arcs.append(sommets[k-1]->getPos());
        }

        for(int j = 0; j < arcs.size() - 1; ++j) {
            QPointF P1{
                arcs[j].x() + 12.5,
                arcs[j].y() + 12.5
            };
            QPointF P2{
                arcs[j+1].x() + 12.5,
                arcs[j+1].y() + 12.5
            };

            d_scene->addLine(P1.x(), P1.y(), P2.x(), P2.y(), pen);
        }
        QPointF P1{
            arcs[arcs.size()-1].x() + 12.5,
            arcs[arcs.size()-1].y() + 12.5
        };
        QPointF P2{
            arcs[0].x() + 12.5,
            arcs[0].y() + 12.5
        };

        d_scene->addLine(P1.x(), P1.y(), P2.x(), P2.y(), pen);
    }
}

void mainwindow::onOrdonnancement() {

}

void mainwindow::onDijkstra() {
    if(d_grapheOrienteValue->verifDijkstra()) {

        int depart = QInputDialog::getInt(this, "Sommet de départ", "Donnez le sommet de départ pour Dijkstra", 1, 1, d_grapheOrienteValue->getNBSOMMETS());
        d_grapheOrienteValue->dijkstra(depart);
        int fin = QInputDialog::getInt(this, "Sommet de fin", "Donnez le sommet de fin pour Dijkstra", 1, 1, d_grapheOrienteValue->getNBSOMMETS());

        auto sommets = d_scene->getSommets();

        auto tmp = d_grapheOrienteValue->getDIJKSTRA_D();
        vector<bool> visited(tmp[0] + 1, false);
        visited[0] = true;
        visited[depart] = true;

        QList<QPointF> arcs;

        int a = depart;
        sommets[a-1]->setBrush(QBrush{Qt::red});
        arcs.append(sommets[a-1]->getPos());
        while (a != fin) {
            a = getMin(tmp, visited);
            visited[a] = true;
            sommets[a-1]->setBrush(QBrush{Qt::red});
            arcs.append(sommets[a-1]->getPos());
        }

        for(int i = 0; i < arcs.size() - 1; ++i) {
            QPointF P1{
                arcs[i].x() + 12.5,
                arcs[i].y() + 12.5
            };
            QPointF P2{
                arcs[i+1].x() + 12.5,
                arcs[i+1].y() + 12.5
            };
            QPen pen{Qt::red};
            pen.setWidth(3);
            d_scene->addLine(P1.x(), P1.y(), P2.x(), P2.y(), pen);

        }

        d_dialog->setDijkstra_D(d_grapheOrienteValue->getDIJKSTRA_D());
        d_dialog->setDijkstra_PRED(d_grapheOrienteValue->getDIJKSTRA_PRED());
    } else {
        QMessageBox msgBox;
        msgBox.setText("Impossible de lancer dijkstra car un poid est négatif");
        msgBox.exec();
    }
}

int mainwindow::getMin(vector<int>& S, vector<bool>& visited) {
    int min = INT_MAX;
    int index = -1;
    for (unsigned int i = 0; i < S.size(); i++) {
        if (!visited[i] && S[i] < min) {
            min = S[i];
            index = i;
        }
    }
    return index;
}

void mainwindow::onDantzig() {

}

void mainwindow::onKruskal() {

    Arbre* result = d_grapheNonOrienteValue->kruskal();

    QString s = "";

    int n = result->getNBSOMMETS();
    auto fs = result->getFS();
    auto aps = result->getAPS();
    auto sommets = d_scene->getSommets();

    QList<QPointF> arcs;
    int t;
    for (int u = 1; u < n; ++u) {
        for (int k = aps[u]; (t = fs[k]) != 0; ++k) {
            sommets[u-1]->setBrush({Qt::magenta});
            sommets[t-1]->setBrush({Qt::magenta});
            arcs.append(sommets[u-1]->getPos());
            arcs.append(sommets[t-1]->getPos());
        }
    }

    QPen pen{Qt::magenta};
    pen.setWidth(3);
    for(int i = 0; i < arcs.size()-1; i += 2) {
        QPointF P1{
            arcs[i].x() + 12.5,
            arcs[i].y() + 12.5
        };
        QPointF P2{
            arcs[i+1].x() + 12.5,
            arcs[i+1].y() + 12.5
        };
        d_scene->addLine(P1.x(), P1.y(), P2.x(), P2.y(), pen);
    }
}

void mainwindow::onPrufer() {
    d_arbre->encode_prufer();
    d_dialog->setPruferCode(d_arbre->getPRUFER_CODE());

    QString s = "";
    for(unsigned int i = 1; i < d_arbre->getPRUFER_CODE().size(); ++i) {
        s += QString::number(d_arbre->getPRUFER_CODE()[i]);
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Prufer");
    msgBox.setText("L'arbre est encodé.\nCode : " + s);
    msgBox.exec();
}

void mainwindow::onCreate() {

}

void mainwindow::onAppli() {

}

void mainwindow::onAPropos() {

}

void mainwindow::onLoad() {

}

void mainwindow::onReset() {
    auto sommets = d_scene->getSommets();

    for(auto s : sommets) {
        s->setBrush(QBrush{Qt::white});
    }
}

mainwindow::~mainwindow()
{
    delete ui;
}

