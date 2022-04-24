#include "GestionnaireGraphe.h"

#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

GestionnaireGraphe::GestionnaireGraphe() {
    d_grapheNonOriente = nullptr;
    d_grapheNonOrienteValue = nullptr;
    d_grapheOriente = nullptr;
    d_grapheOrienteValue = nullptr;
    d_arbre = nullptr;
    d_isOriente = false, d_isArbre = false, d_isValue = false;
}

void GestionnaireGraphe::execute() {
    auto load = charger();
    if (load)
        menu();
    else
        cout << "Chargement annule" << '\n';
}

void GestionnaireGraphe::menu() {
    auto choix = choixMenu();
    while (choix != 9) {
        system("cls");
        switch (choix)
        {
        case 1: {
            if (d_isArbre) {
                cout << "Vous ne pouvez pas lancer l'algorithme du rang sur un arbre.\n";
            }
            else if (d_isValue) {
                if (d_isOriente) {
                    afficherSommet();
                    afficher("Rang : ", d_grapheOrienteValue->getRANG());
                }
                else {
                    cout << "Vous ne pouvez pas lancer l'algorithme du rang sur un graphe non oriente value.\n";
                }
            }
            else {
                if (d_isOriente) {
                    afficherSommet();
                    afficher("Rang : ", d_grapheOriente->getRANG());
                }
                else {
                    cout << "Vous ne pouvez pas lancer l'algorithme du rang sur un graphe non oriente.\n";
                }
                break;
            }
        }
        case 2: {
            if (d_isArbre) {
                cout << "Vous ne pouvez pas lancer l'algorithme de distance sur un arbre.\n";
            }
            else if (d_isValue) {
                if (d_isOriente) {
                    afficherSommet();
                    afficher("Distance : ", d_grapheOrienteValue->getMATRICE_DISTANCE());
                }
                else {
                    cout << "Vous ne pouvez pas lancer l'algorithme de distance sur un graphe non oriente value.\n";
                }
            }
            else {
                if (d_isOriente) {
                    afficherSommet();
                    afficher("Distance : ", d_grapheOriente->getMATRICE_DISTANCE());
                }
                else {
                    cout << "Vous ne pouvez pas lancer l'algorithme de distance sur un graphe non oriente.\n";
                }
            }
            break;
        }
        case 3: {
            if (d_isArbre) {
                cout << "Vous ne pouvez pas lancer l'algorithme de Tarjan sur un arbre.\n";
            }
            else if (d_isValue) {
                if (d_isOriente) {
                    afficherSommet();
                    afficher("Tarjan prem : ", d_grapheOrienteValue->getTARJAN_PREM());
                    afficher("Tarjan cfc : ", d_grapheOrienteValue->getTARJAN_CFC());
                    afficher("Tarjan pilch : ", d_grapheOrienteValue->getTARJAN_PILCH());
                    afficher("Tarjan num : ", d_grapheOrienteValue->getTARJAN_NUM());

                    auto prem = d_grapheOrienteValue->getTARJAN_PREM();
                    auto pilch = d_grapheOrienteValue->getTARJAN_PILCH();

                    seperator();
                    for (int i = 1; i <= prem[0]; ++i) {
                        int k = prem[i];
                        cout << k << " ";
                        while (pilch[k] != 0) {
                            k = pilch[k];
                            cout << k << " ";
                        }
                        cout << endl;
                    }
                }
                else {
                    cout << "Vous ne pouvez pas lancer l'algorithme de Tarjan sur un graphe non oriente value.\n";
                }
            }
            else {
                if (d_isOriente) {
                    afficherSommet();
                    afficher("Tarjan prem : ", d_grapheOriente->getTARJAN_PREM());
                    afficher("Tarjan cfc : ", d_grapheOriente->getTARJAN_CFC());
                    afficher("Tarjan pilch : ", d_grapheOriente->getTARJAN_PILCH());
                    afficher("Tarjan num : ", d_grapheOriente->getTARJAN_NUM());

                    auto prem = d_grapheOriente->getTARJAN_PREM();
                    auto pilch = d_grapheOriente->getTARJAN_PILCH();

                    seperator();
                    for (int i = 1; i <= prem[0]; ++i) {
                        int k = prem[i];
                        cout << k << " ";
                        while (pilch[k] != 0) {
                            k = pilch[k];
                            cout << k << " ";
                        }
                        cout << endl;
                    }
                }
                else {
                    cout << "Vous ne pouvez pas lancer l'algorithme de Tarjan sur un graphe non oriente.\n";
                }
            }
            break;
        }
        case 4: {
            cout << "Pas encore implementer !" << '\n';
            break;
        }
        case 5: {
            if (d_isOriente && d_isValue) {
                if (d_grapheOrienteValue->verifDijkstra()) {
                    system("cls");
                    cout << "Sommet de depart : ";
                    int sommetDepart;
                    cin >> sommetDepart;
                    system("cls");
                    cout << "Sommet d'arrive : ";
                    int sommetArrive;
                    cin >> sommetArrive;
                    d_grapheOrienteValue->dijkstra(sommetDepart);
                    afficher("Dijkstra distance : ", d_grapheOrienteValue->getDIJKSTRA_D());
                    afficher("Dijkstra pred : ", d_grapheOrienteValue->getDIJKSTRA_PRED());					
                    seperator();			
                    auto tmp = d_grapheOrienteValue->getDIJKSTRA_D();
                    vector<bool> visited(tmp[0] + 1, false);
                    visited[0] = true;
                    visited[sommetDepart] = true;
                    int a = sommetDepart;
                    cout << a << " ";
                    while (a != sommetArrive) {
                        int min = INT_MAX;
                        int index = -1;
                        for (unsigned int i = 0; i < tmp.size(); i++) {
                            if (!visited[i] && tmp[i] < min) {
                                min = tmp[i];
                                index = i;
                            }
                        }
                        a = index;
                        visited[a] = true;
                        cout << a << " ";
                    }
                }
                cout << endl;
            }
            else {
                cout << "Vous ne pouvez pas lancer l'algorithme de Dijkstra.\n";
            }
            break;
        }
        case 6: {
            cout << "Pas encore implementer !" << '\n';
            break;
        }
        case 7: {
            if (!d_isOriente && d_isValue) {
                Arbre* result = d_grapheNonOrienteValue->kruskal();

                afficherSommet();
                afficher("Kruskal cfc :", d_grapheNonOrienteValue->getKRUSKAL_CFC());
                afficher("Kruskal prem :", d_grapheNonOrienteValue->getKRUSKAL_PREM());
                afficher("Kruskal pilch :", d_grapheNonOrienteValue->getKRUSKAL_PILCH());
                seperator();
                int n = result->getNBSOMMETS();
                auto fs = result->getFS();
                auto aps = result->getAPS();
                int t;
                for (int u = 1; u < n; ++u) {
                    for (int k = aps[u]; (t = fs[k]) != 0; ++k) {
                        cout << u << " ---> " << t << endl;
                    }
                }
            }
            else {
                cout << "Vous ne pouvez pas lancer l'algorithme de Kruskal.\n";
            }
            break;
        }
        case 8: {
            if (d_isArbre) {
                system("cls");
                afficher("Prufer : ", d_arbre->getPRUFER_CODE());
            }
            else {
                cout << "Ce n'est pas un arbre.\n";
            }
            break;
        }
        case 9: break;
        }
        system("pause");
        choix = choixMenu();
    }
}

int GestionnaireGraphe::choixMenu() {
    int choix = -1;
    do {
        system("cls");
        cout << " +----------------------------+ \n";
        cout << " | Algorithme sur les graphes | \n";
        cout << " +----------------------------+ \n\n";
        cout << "Algorithme : \n";

        cout << "(1) Du rang" << '\n';
        cout << "(2) Des distances" << '\n';
        cout << "(3) Tarjan" << '\n';
        cout << "(4) Ordonnancement" << '\n';
        cout << "(5) Dijkstra" << '\n';
        cout << "(6) Dantzig" << '\n';
        cout << "(7) Kruskal" << '\n';
        cout << "(8) Prufer" << '\n';
        cout << "(9) Quitter" << '\n';

        cin >> choix;
    } while (choix < 0 || choix > 9);
    return choix;
}

void GestionnaireGraphe::chargerGrapheNonOriente() {
    d_isOriente = false, d_isArbre = false, d_isValue = false;
    vector<vector<int>> matrice =
    {
        {4,12,0,0,0},
        {0,0,1,1,1},
        {0,1,0,1,1},
        {0,1,1,0,1},
        {0,1,1,1,0}
    };

    d_grapheNonOriente = new GrapheNonOriente{ matrice };
}

void GestionnaireGraphe::chargerGrapheOriente() {
    d_isOriente = true, d_isArbre = false, d_isValue = false;

    vector<vector<int>> mat =
    {
        {8,13,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,1},
        {0,0,0,0,0,0,1,0,0},
        {0,1,0,0,0,0,0,1,0},
        {0,1,0,1,0,1,0,0,0},
        {0,0,0,0,1,0,1,0,0}
    };

    d_grapheOriente = new GrapheOriente{ mat };
}

void GestionnaireGraphe::chargerGrapheNonOrienteValue() {
    d_isOriente = false, d_isArbre = false, d_isValue = true;
    vector<vector<int>> matrice =
    {
        {4,12,0,0,0},
        {0,0,1,1,1},
        {0,1,0,1,1},
        {0,1,1,0,1},
        {0,1,1,1,0}
    };

    vector<vector<int>> cost =
    {
        {4,12,0,0,0},
        {0,0,1,1,2},
        {0,1,0,1,2},
        {0,1,1,0,2},
        {0,2,2,2,0}
    };

    d_grapheNonOrienteValue = new GrapheNonOrienteValue{ matrice, cost };
}

void GestionnaireGraphe::chargerGrapheOrienteValue() {
    d_isOriente = true, d_isArbre = false, d_isValue = true;
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

    d_grapheOrienteValue = new GrapheOrienteValue{ matrice, c };
}

void GestionnaireGraphe::chargerArbre() {
    d_isOriente = false, d_isArbre = true, d_isValue = false;
    vector<vector<int>> matriceA =
    {
        {8,15,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0},
        {0,1,1,0,1,1,1,0,0},
        {0,0,0,1,0,0,0,1,1},
        {0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0},
        {0,0,0,0,1,0,0,0,0}
    };

    d_arbre = new Arbre{ matriceA };
}

int GestionnaireGraphe::chargerGraphe() {
    int choix = -1;
    do {
        system("cls");
        cout << " +-------------------------------+ \n";
        cout << " | Projet Algorithme Graphe 2022 | \n";
        cout << " +-------------------------------+ \n\n";
        cout << "Que voulez-vous charger ? \n";
        cout << "(1) Graphe non oriente" << '\n';
        cout << "(2) Graphe oriente" << '\n';
        cout << "(3) Graphe non oriente value " << '\n';
        cout << "(4) Graphe oriente value" << '\n';
        cout << "(5) Arbre" << '\n';
        cout << "(6) Quitter" << '\n';
        cin >> choix;
    } while (choix < 0 || choix > 6);
    return choix;
}

bool GestionnaireGraphe::charger() {
    bool charged = false;
    auto choix = chargerGraphe();
    switch (choix)
    {
    case 1: chargerGrapheNonOriente(); charged = true; break;
    case 2: chargerGrapheOriente(); charged = true; break;
    case 3: chargerGrapheNonOrienteValue(); charged = true; break;
    case 4: chargerGrapheOrienteValue(); charged = true; break;
    case 5: chargerArbre(); charged = true; break;
    case 6: charged = false; break;
    }
    return charged;
}

void GestionnaireGraphe::afficher(string s, vector<int> t) {
    cout << s << '\n';
    for (int i = 0; i < t.size(); ++i) {
        cout << t[i] << '\t';
    }
    cout << '\n';
}

void GestionnaireGraphe::afficher(string s, vector<vector<int>> t) {
    cout << s << '\n';
    for (int i = 0; i < t.size(); ++i) {
        for (int j = 0; j < t[i].size(); ++j) {
            if (t[i][j] > 2000000000)
                cout << "INF" << '\t';
            else if (t[i][j] < -2000000000)
                cout << "-INF" << '\t';
            else
                cout << t[i][j] << '\t';
        }
        cout << '\n';
    }
    cout << '\n';
}

void GestionnaireGraphe::seperator() {
    cout << "\n===========================================================================\n";
}

void GestionnaireGraphe::afficherSommet() {
    seperator();
    cout << "\t";
    if (d_isArbre) {
        for (int i = 1; i <= d_arbre->getNBSOMMETS(); ++i) {
            cout << i << "\t";
        }
    }
    else if (d_isValue) {
        if (d_isOriente) {
            for (int i = 1; i <= d_grapheOrienteValue->getNBSOMMETS(); ++i) {
                cout << i << "\t";
            }
        }
        else {
            for (int i = 1; i <= d_grapheNonOrienteValue->getNBSOMMETS(); ++i) {
                cout << i << "\t";
            }
        }
    }
    else {
        if (d_isOriente) {
            for (int i = 1; i <= d_grapheOriente->getNBSOMMETS(); ++i) {
                cout << i << "\t";
            }
        }
        else {
            for (int i = 1; i <= d_grapheNonOriente->getNBSOMMETS(); ++i) {
                cout << i << "\t";
            }
        }
    }
    seperator();
}