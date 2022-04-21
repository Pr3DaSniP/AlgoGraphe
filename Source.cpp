#include <iostream>

#include "Graphe.h"
#include "GrapheOriente.h"
#include "GrapheNonOriente.h"
#include "GrapheOrienteValue.h"
#include "GrapheNonOrienteValue.h"
#include "Arbre.h";

using namespace std;

// FONCTION UTILS //
void afficher(string s, vector<int> tab) {
	cout << s << endl;
	for (int i = 0; i < tab.size(); ++i) {
		cout << tab[i] << "\t";
	}
	cout << endl;
}
void afficher(string s, vector<vector<int>> tab) {
	cout << s << endl;
	for (int i = 0; i < tab.size(); ++i) {
		for (int j = 0; j < tab[i].size(); ++j) {
			cout << tab[i][j] << "\t";
		}
		cout << endl;
	}
}
void seperator() {
	cout << "\n===========================================================================\n";
}
void afficherSommet(Graphe& G) {
	seperator();
	cout << "\t";
	for (int i = 1; i <= G.getNBSOMMETS(); ++i) {
		cout << i << "\t";
	}
	seperator();
}
// FIN FONCTION UTILS //

void testRang() {
	vector<vector<int>> matrice =
	{
		{12,19,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,1,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,0,1,0},
		{0,0,0,1,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,10,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	GrapheOriente G{ matrice };

	afficherSommet(G);

	afficher("RANG : ", G.getRANG());
}

void testDantzig() {
	vector<int> fs = { 13,2,3,0,4,5,0,4,0,0,1,3,4,0 };
	vector<int> aps = { 5,1,4,7,9,10 };
	vector<vector<int>> c =
	{
		{5,8,0,0,0,0},
		{0,0,-2,4,99,99},
		{0,99,0,99,4,3},
		{0,99,99,0,1,99},
		{0,99,99,99,0,99},
		{0,0,99,-1,99,0}
	};

	GrapheOrienteValue G{ fs, aps, c };

	G.dantzig();

	afficher("COUT : ", G.get_COST());
	afficher("DANTZIG : ", G.getDANTZIG_COST());
}

void testDijkstra() {
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

	GrapheOrienteValue G{ matrice, c };

	G.dijkstra(1);
	afficherSommet(G);
	afficher("D : ", G.getDIJKSTRA_D());
	afficher("PRED : ", G.getDIJKSTRA_PRED());
}

void testKruskal() {
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

	GrapheNonOrienteValue G{ matrice, cost };

	G.kruskal();

	afficherSommet(G);

	afficher("PREM : ", G.getKRUSKAL_PREM());
	afficher("PILCH : ", G.getKRUSKAL_PILCH());
	afficher("CFC : ", G.getKRUSKAL_CFC());
}

void testPrufer() {
	vector<vector<int>> matrice =
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

	Arbre A{ matrice };

	A.encode_prufer();
	
	afficher("PRUF : ", A.getPRUFER_CODE());

	A.decode_prufer();
}

void main() {
	
}