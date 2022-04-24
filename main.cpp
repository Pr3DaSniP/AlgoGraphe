#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    a.setStyle("fusion");

//    vector<vector<int>> matrice =
//    {
//        {12,19,0,0,0,0,0,0,0,0,0,0,0},
//        {0,0,1,1,0,0,0,0,0,0,0,0,0},
//        {0,0,0,0,1,0,0,0,0,1,0,0,0},
//        {0,0,0,0,1,0,1,0,1,0,0,0,0},
//        {0,0,0,0,0,0,0,0,1,1,0,1,0},
//        {0,0,0,1,0,0,1,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,1,1,0,0,0,0},
//        {0,0,0,0,0,0,0,0,1,0,0,0,0},
//        {0,0,0,0,0,0,0,0,0,0,1,0,0},
//        {0,0,0,0,0,0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0,0,0,0,1,0},
//        {0,0,0,0,0,0,0,0,0,0,1,0,1},
//        {0,0,0,0,0,0,0,0,0,0,0,0,0}
//    };
//    GrapheOriente *G = new GrapheOriente{matrice};

//    vector<vector<int>> matrice =
//    {
//        {4,12,0,0,0},
//        {0,0,1,1,1},
//        {0,1,0,1,1},
//        {0,1,1,0,1},
//        {0,1,1,1,0}
//    };

//    vector<vector<int>> cost =
//    {
//        {4,12,0,0,0},
//        {0,0,1,1,2},
//        {0,1,0,1,2},
//        {0,1,1,0,2},
//        {0,2,2,2,0}
//    };

//    GrapheNonOrienteValue *G = new GrapheNonOrienteValue{ matrice, cost };

//    vector<vector<int>> matriceA =
//    {
//        {8,15,0,0,0,0,0,0,0},
//        {0,0,0,1,0,0,0,0,0},
//        {0,0,0,1,0,0,0,0,0},
//        {0,1,1,0,1,1,1,0,0},
//        {0,0,0,1,0,0,0,1,1},
//        {0,0,0,1,0,0,0,0,0},
//        {0,0,0,1,0,0,0,0,0},
//        {0,0,0,0,1,0,0,0,0},
//        {0,0,0,0,1,0,0,0,0}
//    };

//    Arbre *A = new Arbre{ matriceA };

//    vector<vector<int>> mat =
//    {
//        {8,14,0,0,0,0,0,0,0},
//        {0,0,1,1,1,0,0,0,0},
//        {0,0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,1,0,0},
//        {0,0,0,0,0,0,0,1,0},
//        {0,1,1,0,0,0,1,0,0},
//        {0,0,0,1,1,0,0,1,1},
//        {0,0,0,0,1,0,0,0,0},
//        {0,0,0,0,0,0,0,1,0}
//    };

//    GrapheOriente *G = new GrapheOriente{ mat };

    vector<vector<int>> matrice =
    {
        {5,7,0,0,0,0},
        {0,0,0,1,0,1},
        {0,1,0,1,0,0},
        {0,0,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,1,0}
    };

    vector<vector<int>> c =
    {
        {5,7,0,0,0,0},
        {0,0,INT_MAX,18,INT_MAX,3},
        {0,8,0,4,INT_MAX,INT_MAX},
        {0,INT_MAX,INT_MAX,0,INT_MAX,INT_MAX},
        {0,INT_MAX,1,INT_MAX,0,INT_MAX},
        {0,INT_MAX,10,INT_MAX,2,0}
    };

    GrapheOrienteValue *G = new GrapheOrienteValue{ matrice, c };

//    vector<vector<int>> mat =
//    {
//        {8,13,0,0,0,0,0,0,0},
//        {0,0,1,0,0,0,0,0,0},
//        {0,0,0,1,0,0,0,0,0},
//        {0,1,0,0,0,0,0,0,0},
//        {0,0,0,0,0,1,0,0,1},
//        {0,0,0,0,0,0,1,0,0},
//        {0,1,0,0,0,0,0,1,0},
//        {0,1,0,1,0,1,0,0,0},
//        {0,0,0,0,1,0,1,0,0}
//    };

//    GrapheOriente *G = new GrapheOriente{ mat };

//    vector<vector<int>> matrice =
//    {
//        {5,7,0,0,0,0},
//        {0,0,0,1,0,1},
//        {0,1,0,1,0,0},
//        {0,0,0,0,0,0},
//        {0,0,1,0,0,0},
//        {0,0,1,0,1,0}
//    };

//    vector<vector<int>> c =
//    {
//        {5,7,0,0,0,0},
//        {0,0,INT_MAX,18,INT_MAX,3},
//        {0,8,0,4,INT_MAX,INT_MAX},
//        {0,INT_MAX,INT_MAX,0,INT_MAX,INT_MAX},
//        {0,INT_MAX,1,INT_MAX,0,INT_MAX},
//        {0,INT_MAX,10,INT_MAX,2,0}
//    };

//    GrapheOrienteValue *G = GrapheOrienteValue{ matrice, c };

//    vector<vector<int>> matrice =
//    {
//        {4,12,0,0,0},
//        {0,0,1,1,1},
//        {0,1,0,1,1},
//        {0,1,1,0,1},
//        {0,1,1,1,0}
//    };

//    vector<vector<int>> cost =
//    {
//        {4,12,0,0,0},
//        {0,0,1,1,2},
//        {0,1,0,1,2},
//        {0,1,1,0,2},
//        {0,2,2,2,0}
//    };

//    GrapheNonOrienteValue *G = new GrapheNonOrienteValue{ matrice, cost };

//    vector<vector<int>> matrice =
//    {
//        {6,16,0,0,0,0,0},
//        {0,0,1,1,0,0,1},
//        {0,1,0,1,0,0,0},
//        {0,1,1,0,1,1,1},
//        {0,0,0,1,0,1,0},
//        {0,0,0,1,1,0,0},
//        {0,1,0,1,0,0,0}
//    };

//    vector<vector<int>> cost =
//    {
//        {6,16,0,0,0,0,0},
//        {0,0,3,4,0,0,7},
//        {0,3,0,4,0,0,0},
//        {0,4,4,0,9,9,1},
//        {0,0,0,9,0,5,0},
//        {0,0,0,9,5,0,0},
//        {0,7,0,1,0,0,0}
//    };

//    GrapheNonOrienteValue *G = new GrapheNonOrienteValue{ matrice, cost };

    mainwindow w{G};
    w.setFixedSize(1200,800);
    w.show();
    return a.exec();
}
