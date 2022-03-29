#include <iostream>
#include <string>
#include <vector>

#include "VilleSommet.h"
#include "Graphe.h"

using namespace std;


/*
*
*																{0,1,1,1,0}
*  FS  = [13,2,3,4,0,2,3,4,0,5,0,0,4,0]							{0,1,1,1,0}
*												==>				{0,0,0,0,1}
*  APS = [5,1,5,9,11,12]										{0,0,0,0,0}
*																{0,0,0,1,0}
*
*/

void main() {	
	Sommet* vs1 = new Sommet{ 1 };
	Sommet* vs2 = new Sommet{ 2 };
	Sommet* vs3 = new Sommet{ 3 };
	Sommet* vs4 = new Sommet{ 4 };
	Sommet* vs5 = new Sommet{ 5 };
	Sommet* vs9 = new Sommet{ 9 };
	Sommet* vs11 = new Sommet{ 11 };
	Sommet* vs12 = new Sommet{ 12 };
	
	Sommet* null = new Sommet{ -1 };
	
	vector<Sommet*> fs = { vs2, vs3, vs4, null, vs2, vs3, vs4, null, vs5, null, null, vs4, null };
	vector<Sommet*> aps = { vs1, vs5, vs9, vs11, vs12 };
	
	Graphe* G = new Graphe{fs, aps};
	
	auto m = G->getMatrice();
	
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}