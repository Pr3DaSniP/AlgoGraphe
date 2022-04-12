#include <iostream>
#include <vector>

#include "Graphe.h"

using namespace std;

void afficher(vector<int> tab) {
	for (int i = 0; i < tab.size(); ++i) {
		cout << tab[i] << " ";
	}
	cout << endl;
}
void afficher(vector<vector<int>> tab) {
	for (int i = 0; i < tab.size(); ++i) {
		for (int j = 0; j < tab[i].size(); ++j) {
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
}

void main() {
	vector<vector<int>> mat =
	{
		{5,8,0,0,0,0},
		{0,0,1,1,1,0},
		{0,0,1,1,1,0},
		{0,0,0,0,0,1},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0}
	};

	vector<int> fs = { 13,2,3,4,0,2,3,4,0,5,0,0,4,0 };
	vector<int> aps = { 5,1,5,9,11,12 };

	Graphe* G1 = new Graphe{ mat };
	Graphe* G2 = new Graphe{ fs,aps };

	afficher(G1->getFS());
	afficher(G1->getAPS());
	cout << "====================================" << endl;
	afficher(G2->getADJACENCE());
	cout << "====================================" << endl;
	afficher(G1->getRANG());
	afficher(G2->getRANG());
	cout << "====================================" << endl;
	afficher(G1->getDDI());
	afficher(G2->getDDI());
	cout << "====================================" << endl;
	afficher(G1->getDDE());
	afficher(G2->getDDE());
	cout << "====================================" << endl;
	afficher(G1->getDISTANCE());
	cout << "====================================" << endl;
	afficher(G2->getDISTANCE());
}