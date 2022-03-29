#ifndef GRAPHE_H
#define GRAPHE_H

#include <iostream>
#include <vector>
#include "Sommet.h"

using std::vector;

class Graphe {
protected:
	vector<Sommet*> m_fs;
	vector<Sommet*> m_aps;
	vector<Sommet*> m_dde;
	vector<Sommet*> m_ddi;
	vector<Sommet*> m_rang;
	vector<Sommet*> m_distance;
	vector<vector<int>> m_matrice;
	
	void FsApsToMatrice();
	
	void MatriceToFsAps();
	
public:
	Graphe();
	Graphe(vector<Sommet*> fs, vector<Sommet*> aps);
	Graphe(vector<vector<int>> matrice);
	
	void addSommet(Sommet* s);
	int getNbSuccesseurs();
	void getNbPredecesseurs();
	void demi_degre_ext();
	void demi_degre_int();
	void rang();
	void distance();
	
	vector<Sommet*> getFS();
	vector<Sommet*> getAPS();
	vector<Sommet*> getDDE();
	vector<Sommet*> getDDI();
	vector<Sommet*> getRang();
	vector<Sommet*> getDistance();
	vector<vector<int>> getMatrice();

	void afficher();
	
	virtual ~Graphe() = default;
};

#endif // !GRAPHE_H
