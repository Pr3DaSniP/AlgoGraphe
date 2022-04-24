#ifndef GESTIONNAIREGRAPHE_H
#define GESTIONNAIREGRAPHE_H

#include "Graphe.h"
#include "GrapheNonOriente.h"
#include "GrapheOriente.h"
#include "GrapheNonOrienteValue.h"
#include "GrapheOrienteValue.h"
#include "Arbre.h"

#include <string>
using std::string;

class GestionnaireGraphe {
public:
    GestionnaireGraphe();

    void execute();
private:

    GrapheNonOriente* d_grapheNonOriente;
    GrapheOriente* d_grapheOriente;
    GrapheOrienteValue* d_grapheOrienteValue;
    GrapheNonOrienteValue* d_grapheNonOrienteValue;
    Arbre* d_arbre;
    bool d_isValue, d_isOriente, d_isArbre;

    void menu();

    int choixMenu();
	
    void chargerGrapheNonOriente();
    void chargerGrapheOriente();
    void chargerGrapheNonOrienteValue();
    void chargerGrapheOrienteValue();
    void chargerArbre();
	
    int chargerGraphe();

    bool charger();

    void afficher(string s, vector<int> t);
    void afficher(string s, vector<vector<int>> t);

    void seperator();
    void afficherSommet();
};

#endif // !GESTIONNAIREGRAPHE_H
