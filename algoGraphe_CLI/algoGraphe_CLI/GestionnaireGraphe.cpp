#include "GestionnaireGraphe.h"

#include "json.hpp"
#include <fstream>

#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

using nlohmann::json;

GestionnaireGraphe::GestionnaireGraphe() {
    d_grapheNonOriente = nullptr;
    d_grapheNonOrienteValue = nullptr;
    d_grapheOriente = nullptr;
    d_grapheOrienteValue = nullptr;
    d_arbre = nullptr;
    d_isOriente = false, d_isArbre = false, d_isValue = false;
}

void GestionnaireGraphe::execute() {

    bool created = false, loaded = false;
    int choix = -1;
    do {
        system("cls");
        cout << " +-------------------------------+ \n";
        cout << " | Projet Graphe Algorithme 2022 | \n";
        cout << " +-------------------------------+ \n\n";
        cout << "Que voulez vous faier : \n";

        cout << "(1) Creer un graphe" << '\n';
        cout << "(2) Charger un graphe" << '\n';
        cout << "(3) Quitter" << '\n';

        cin >> choix;
    } while (choix < 0 || choix > 3);

    switch (choix) {
        case 1:
            created = creerGraphe();
			break;
        case 2:
			cout << "Nom du fichier (sans extension) : ";
			string nomFichier;
			cin >> nomFichier;
            loaded = loadGraphe(nomFichier);
            break;
    }

    if (created || loaded) {
        menu();
    }
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

bool GestionnaireGraphe::loadGraphe(const string& nomFichier) {
    ifstream fIN(nomFichier + ".json");
    auto json = json::parse(fIN);
    d_isArbre = json["isArbre"].get<bool>(), d_isOriente = json["isOriente"].get<bool>(), d_isValue = json["isValue"].get<bool>();
	
    if (d_isArbre) {
        d_arbre = new Arbre{
            json["fs"].get<vector<int>>(),
            json["aps"].get<vector<int>>(),
        };
        return true;
    }
    else if (d_isValue) {
        if (d_isOriente) {
            d_grapheOrienteValue = new GrapheOrienteValue{
                json["fs"].get<vector<int>>(),
                json["aps"].get<vector<int>>(),
                json["cost"].get<vector<vector<int>>>()
            };
            return true;
        }
        else {
            d_grapheNonOrienteValue = new GrapheNonOrienteValue{
				json["fs"].get<vector<int>>(),
				json["aps"].get<vector<int>>(),
				json["cost"].get<vector<vector<int>>>()
			};
            return true;
        }
    }
    else {
        if (d_isOriente) {
            d_grapheOriente = new GrapheOriente{
                json["fs"].get<vector<int>>(),
                json["aps"].get<vector<int>>()
            };
            return true;
        }
        else {
            d_grapheNonOriente = new GrapheNonOriente{
				json["fs"].get<vector<int>>(),
				json["aps"].get<vector<int>>()
			};
            return true;
        }
    }
    return false;
}

void GestionnaireGraphe::saveGraphe(const string& nomFichier) {
    json j;
    j["isOriente"] = d_isOriente;
    j["isValue"] = d_isValue;
    j["isArbre"] = d_isArbre;
    if (d_isArbre) {
        j["fs"] = d_arbre->getFS();
		j["aps"] = d_arbre->getAPS();
    }
    else if (d_isValue) {
        if (d_isOriente) {
            j["fs"] = d_grapheOrienteValue->getFS();
            j["aps"] = d_grapheOrienteValue->getAPS();
            j["cost"] = d_grapheOrienteValue->get_COST();
        }
        else {
            j["fs"] = d_grapheNonOrienteValue->getFS();
            j["aps"] = d_grapheNonOrienteValue->getAPS();
            j["cost"] = d_grapheNonOrienteValue->get_COST();
        }
    }
    else {
        if (d_isOriente) {
            j["fs"] = d_grapheOriente->getFS();
            j["aps"] = d_grapheOriente->getAPS();
        }
        else {
            j["fs"] = d_grapheNonOriente->getFS();
            j["aps"] = d_grapheNonOriente->getAPS();
        }
    }
    ofstream fichier(nomFichier + ".json");
    fichier << j.dump(4);
    fichier.close();  
}

bool GestionnaireGraphe::creerGraphe() {
	system("cls");
	cout << " +----------------------------+ \n";
	cout << " | Creation d'un graphe       | \n";
	cout << " +----------------------------+ \n\n";
	cout << "Veuillez choisir le type de graphe : \n";
	cout << "(1) Graphe oriente" << '\n';
	cout << "(2) Graphe non oriente" << '\n';
	cout << "(3) Graphe oriente avec valeur" << '\n';
	cout << "(4) Graphe non oriente avec valeur" << '\n';
	cout << "(5) Arbre" << '\n';
	cout << "(6) Quitter" << '\n';
	int choix = -1;
	do {
		cin >> choix;
	} while (choix < 1 || choix > 6);
	
    bool isCreate = false;

    if (choix != 6) {
        switch (choix) {
            case 1: {
                d_isArbre = false, d_isOriente = true, d_isValue = false;

                int nbSommets = 0;
                do {
                    cout << "Veuillez entrer le nombre de sommets : ";
                    cin >> nbSommets;
                } while (nbSommets < 1);

                vector<vector<int>> mat(nbSommets + 1, vector<int>(nbSommets + 1));

                int nbArcs = 1;
                bool stop = false;
                do {
                    cout << "Ajouter un arc : \n";
                    cout << "Entrez le numero du sommet de depart : ";
                    int s1 = 0;
                    cin >> s1;
                    cout << "Entrez le numero du sommet d'arrivee : ";
                    int s2 = 0;
                    cin >> s2;
                    mat[s1][s2] = 1;
                    cout << "Voulez-vous ajouter un autre arc ? (1) oui (0) non : ";
                    int choix = 0;
                    cin >> choix;
                    if (choix == 0) {
                        stop = true;
                    }
                    nbArcs++;
                } while (!stop);

                mat[0][0] = nbSommets;
                mat[0][1] = nbArcs;

                d_grapheOriente = new GrapheOriente{ mat };
                isCreate = true;
            }
            break;
            case 2: {
                d_isArbre = false, d_isOriente = false, d_isValue = false;

                int nbSommets = 0;
                do {
                    cout << "Veuillez entrer le nombre de sommets : ";
                    cin >> nbSommets;
                } while (nbSommets < 1);

                vector<vector<int>> mat(nbSommets + 1, vector<int>(nbSommets + 1));

                int nbArcs = 2;
                bool stop = false;
                do {
                    cout << "Ajouter un arc : \n";
                    cout << "Entrez le numero du sommet de depart : ";
                    int s1 = 0;
                    cin >> s1;
                    cout << "Entrez le numero du sommet d'arrivee : ";
                    int s2 = 0;
                    cin >> s2;
                    mat[s1][s2] = 1;
                    mat[s2][s1] = 1;
                    cout << "Voulez-vous ajouter un autre arc ? (1) oui (0) non : ";
                    int choix = 0;
                    cin >> choix;
                    if (choix == 0) {
                        stop = true;
                    }
                    nbArcs += 2;
                } while (!stop);

                mat[0][0] = nbSommets;
                mat[0][1] = nbArcs;

                d_grapheNonOriente = new GrapheNonOriente{ mat };
                isCreate = true;
            }
            break;
            case 3: {
                d_isArbre = false, d_isOriente = true, d_isValue = true;

                int nbSommets = 0;
                do {
                    cout << "Veuillez entrer le nombre de sommets : ";
                    cin >> nbSommets;
                } while (nbSommets < 1);

                vector<vector<int>> mat(nbSommets + 1, vector<int>(nbSommets + 1));
                vector<vector<int>> cost(nbSommets + 1, vector<int>(nbSommets + 1));

                int nbArcs = 1;
                bool stop = false;
                do {
                    cout << "Ajouter un arc : \n";
                    cout << "Entrez le numero du sommet de depart : ";
                    int s1 = 0;
                    cin >> s1;
                    cout << "Entrez le numero du sommet d'arrivee : ";
                    int s2 = 0;
                    cin >> s2;
                    mat[s1][s2] = 1;
                    cout << "Entrez le cout de l'arc (999 pour INF) : ";
					int costArc = 0;
					cin >> costArc;
                    if (costArc == 999) {
                        cost[s1][s2] = INT_MAX;
                    }
                    else {
                        cost[s1][s2] = costArc;
                    }
                    cout << "Voulez-vous ajouter un autre arc ? (1) oui (0) non : ";
                    int choix = 0;
                    cin >> choix;
                    if (choix == 0) {
                        stop = true;
                    }
                    nbArcs++;
                } while (!stop);

                mat[0][0] = nbSommets;
                mat[0][1] = nbArcs;

                d_grapheOrienteValue = new GrapheOrienteValue{ mat, cost };
                isCreate = true;
            }
			break;
            case 4: {
                d_isArbre = false, d_isOriente = false, d_isValue = true;

                int nbSommets = 0;
                do {
                    cout << "Veuillez entrer le nombre de sommets : ";
                    cin >> nbSommets;
                } while (nbSommets < 1);

                vector<vector<int>> mat(nbSommets + 1, vector<int>(nbSommets + 1));
                vector<vector<int>> cost(nbSommets + 1, vector<int>(nbSommets + 1));

                int nbArcs = 2;
                bool stop = false;
                do {
                    cout << "Ajouter un arc : \n";
                    cout << "Entrez le numero du sommet de depart : ";
                    int s1 = 0;
                    cin >> s1;
                    cout << "Entrez le numero du sommet d'arrivee : ";
                    int s2 = 0;
                    cin >> s2;
                    mat[s1][s2] = 1;
                    mat[s2][s1] = 1;
                    cout << "Entrez le cout de l'arc (999 pour INF) : ";
                    int costArc = 0;
                    cin >> costArc;
                    if (costArc == 999) {
                        cost[s1][s2] = INT_MAX;
                        cost[s2][s1] = INT_MAX;
                    }
                    else {
                        cost[s1][s2] = costArc;
                        cost[s2][s1] = costArc;
                    }     
                    cout << "Voulez-vous ajouter un autre arc ? (1) oui (0) non : ";
                    int choix = 0;
                    cin >> choix;
                    if (choix == 0) {
                        stop = true;
                    }
                    nbArcs += 2;
                } while (!stop);

                mat[0][0] = nbSommets;
                mat[0][1] = nbArcs;

                d_grapheNonOrienteValue = new GrapheNonOrienteValue{ mat, cost };
                isCreate = true;
            }
            break;
            case 5: {
                d_isArbre = true, d_isOriente = false, d_isValue = false;

                int nbSommets = 0;
                do {
                    cout << "Veuillez entrer le nombre de sommets : ";
                    cin >> nbSommets;
                } while (nbSommets < 1);

                vector<vector<int>> mat(nbSommets + 1, vector<int>(nbSommets + 1));
                vector<bool> relier(nbSommets, false);

                int nbArcs = 2;
                bool stop = false;
                do {
                    cout << "Ajouter un arc : \n";
                    cout << "Entrez le numero du sommet de depart : ";
                    int s1 = 0;
                    cin >> s1;
                    cout << "Entrez le numero du sommet d'arrivee : ";
                    int s2 = 0;
                    cin >> s2;
                    mat[s1][s2] = 1;
                    mat[s2][s1] = 1;
                    relier[s1-1] = true;
					relier[s2-1] = true;
                    cout << "Voulez-vous ajouter un autre arc ? (1) oui (0) non : ";
                    int choix = 0;
                    cin >> choix;
                    if (choix == 0) {
                        stop = true;
                    }
                    nbArcs += 2;
                } while (!stop);

                mat[0][0] = nbSommets;
                mat[0][1] = nbArcs;

                bool isOk = true;
                for (int i = 0; i < nbSommets; i++) {
                    if (relier[i] == false) {
                        isOk = false;
                        break;
                    }
                }
				
                if (isOk) {
                    d_arbre = new Arbre{ mat };
                    isCreate = true;
                }
                else 
					cout << "Le graphe n'est pas un arbre" << endl;
            }
            break;
        }

        if (isCreate) {
            cout << "Nom du fichier de sauvegarde (sans extension): ";
			string nomFichier;
			cin >> nomFichier;
            saveGraphe(nomFichier);
            return true;
        }
    }
    return false;
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