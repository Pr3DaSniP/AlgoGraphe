#include "dialogcreate.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

dialogCreate::dialogCreate()
{
    vue_cree();
}


void dialogCreate::vue_cree() {
    auto layout = new QHBoxLayout;

    auto *btnGO = new QPushButton{"Graphe Orienté"};
    auto *btnGOV = new QPushButton{"Graphe Orienté Valué"};
    auto *btnGNO = new QPushButton{"Graphe Non Orienté"};
    auto *btnGNOV = new QPushButton{"Graphe Non Orienté Valué"};

    layout->addWidget(btnGO);
    layout->addWidget(btnGOV);
    layout->addWidget(btnGNO);
    layout->addWidget(btnGNOV);

    connect(btnGO, &QPushButton::clicked, this, &dialogCreate::onGO);
    connect(btnGOV, &QPushButton::clicked, this, &dialogCreate::onGOV);
    connect(btnGNO, &QPushButton::clicked, this, &dialogCreate::onGNO);
    connect(btnGNOV, &QPushButton::clicked, this, &dialogCreate::onGNOV);

    setLayout(layout);
}

void dialogCreate::onGO() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Création d'un graphe orienté");
    msgBox.setText("GO pressed");
    msgBox.exec();
}

void dialogCreate::onGOV() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Création d'un graphe orienté valué");
    msgBox.setText("GOV pressed");
    msgBox.exec();
}

void dialogCreate::onGNO() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Création d'un graphe non orienté");
    msgBox.setText("GNO pressed");
    msgBox.exec();
}

void dialogCreate::onGNOV() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Création d'un graphe non orienté non valué");
    msgBox.setText("GNOV pressed");
    msgBox.exec();
}
