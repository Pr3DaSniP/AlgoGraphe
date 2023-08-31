#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogdata.h"
#include "dialogcreate.h"
#include <sstream>

#include <QInputDialog>
#include <QMessageBox>
#include <QFont>

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
    QMessageBox msgBox;
    msgBox.setWindowTitle("Ordonnancement");
    msgBox.setText("Pas encore implémenté");
    msgBox.exec();
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
    QMessageBox msgBox;
    msgBox.setWindowTitle("Dantzig");
    msgBox.setText("Pas encore implémenté");
    msgBox.exec();
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
    auto *dialog = new dialogCreate;
    dialog->setWindowTitle("Créer un graphe");
    dialog->exec();
}

void mainwindow::onAPropos() {
    QFont font("Calibri");
    auto *layout = new QVBoxLayout;

    // Label
    auto *Tarjan = new QLabel{"<h1><u><strong>Tarjan</strong></u></h1>"};
    Tarjan->setFont(font);
    auto *descTarjan = new QLabel{
            "L'algorithme de Tarjan permet de déterminer les composantes fortements connexes "
            "(Il existe un chemin de U vers V et de V vers U pour un couple de sommet (U,V)) "
            "d'un graphe orienté. \n"
            "Il permet de trouver le graphe réduit du graphe de base. "
            "\n ==> Pour l'utiliser, il nous faut un graphe orienté en entrée."
    };

    layout->addWidget(Tarjan);
    layout->addWidget(descTarjan);

    auto *Ordo = new QLabel{"<h1><u><strong>Ordonnancement</strong></u></h1>"};
    Ordo->setFont(font);
    auto *descOrdo = new QLabel{
            "Les problèmes d'ordonnancement de projet apparaissent généralement en gestion de production "
            "au niveau du long terme lorsque l'on veut planifier les tâches correspondant à un projet important \n"
            "qui va être réalisé sur une longue période. "
            "Ordonnancer les tâches consistent, en général, à prévoir à quel instant les tâches doivent être démarrées. "
            "\n ==> Pour l'utiliser, il faut donner un tableau de tâches avec leur durée respectives ainsi que les tâches antérieures."
    };

    layout->addWidget(Ordo);
    layout->addWidget(descOrdo);

    auto *Dijkstra = new QLabel{"<h1><u><strong>Dijkstra</strong></u></h1>"};
    Dijkstra->setFont(font);
    auto *descDijkstra = new QLabel{
            "L'algorithme de Dijkstra sert à résoudre un problème du plus court chemin. "
            "\nIl permet de calculer le chemin le plus court entre deux villes en connaissant le réseau routier."
            "\n ==> Pour l'utiliser, il faut donner un graphe orienté valué, un sommet de départ et un sommet d'arrivé. Il faut aucun poids négatif."
    };

    layout->addWidget(Dijkstra);
    layout->addWidget(descDijkstra);

    auto *Dantzig = new QLabel{"<h1><u><strong>Dantzig</strong></u></h1>"};
    Dantzig->setFont(font);
    auto *descDantzig = new QLabel{
            "L'algorithme de Dantzig sert à résoudre un problème du plus court chemin."
            "Il permet tout comme l'algorithme de Dijkstra, de trouver le chemin le plus court mais contrairement à Dijkstra, \non peut l'utiliser avec des poids négatifs."
            "Il permet aussi de trouver les chemins absorbants (Un chemin absorbant est un circuit de longueur négative.)"
            "\n ==> Pour l'utiliser, il faut donner un graphe orienté valué, un sommet de départ et un sommet d'arrivé."
    };

    layout->addWidget(Dantzig);
    layout->addWidget(descDantzig);

    auto *Kruskal = new QLabel{"<h1><u><strong>Kruskal</strong></u></h1>"};
    Kruskal->setFont(font);
    auto *descKruskal = new QLabel{
            "L'algorithme de Kruskal est un algorithme de recherche d'arbre recouvrant de poids minimal."
            "\n ==> Pour l'utiliser, il faut donner un graphe non orienté valué et connexe (Il existe un chemin entre U et V quels que soient U et V)."
    };

    layout->addWidget(Kruskal);
    layout->addWidget(descKruskal);

    auto *Prufer = new QLabel{"<h1><u><strong>Prüfer</strong></u></h1>"};
    Prufer->setFont(font);
    auto *descPrufer = new QLabel{
            "Le codage de Prüfer est une méthode pour décrire de façon compacte un arbre dont les sommets sont numérotés de 1 à N."
            "\nCe codage représente un arbre de N sommets avec une suite P = (x1,x2,x3,...,xn-2)."
            "\n ==> Pour l'utiliser, il faut donner un arbre (Un graphe acyclique (contient aucun cycle) et connexe)."
    };

    layout->addWidget(Prufer);
    layout->addWidget(descPrufer);


    QDialog *dialog = new QDialog{};
    dialog->setWindowTitle("À propos des algorithmes sur les graphes");
    dialog->setLayout(layout);

    dialog->exec();
}

void mainwindow::onLoad() {

}

mainwindow::~mainwindow()
{
    delete ui;
}

