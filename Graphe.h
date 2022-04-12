#ifndef GRAPHE_H
#define GRAPHE_H

#include <iostream>
#include <vector>

using std::vector;

class Graphe {
protected:
	vector<int> d_fs;
	vector<int> d_aps;
	vector<int> d_rang;
	vector<int> d_ddi;
	vector<int> d_dde;
	vector<vector<int>> d_MatAdjacence;
	vector<vector<int>> d_MatDistance;

	void empiler(int x, int* pilch);
public:
	Graphe(vector<int> fs, vector<int> aps);
	Graphe(vector<vector<int>> MatAdjacence);

	vector<int> getFS();
	vector<int> getAPS();
	vector<int> getRANG();
	vector<int> getDDI();
	vector<int> getDDE();
	vector<vector<int>> getADJACENCE();
	vector<vector<int>> getDISTANCE();

	virtual ~Graphe() = default;
private:
	void init();

	// TESTED
	void matriceToFSAPS();

	// TESTED
	void fsapsToMATRICE();

	// TESTED
	void rang();

	// TESTED
	void demi_degre_int();

	// TESTED
	void demi_degre_ext();

	// TESTED
	void Mat_dist();

	void desc_large(int r, vector<int>& dist);
};

#endif // !GRAPHE_H
