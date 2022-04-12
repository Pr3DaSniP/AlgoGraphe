#ifndef GRAPHE_H
#define GRAPHE_H

#include <iostream>
#include <vector>

using std::vector;

class Graphe {
protected:
	vector<int> d_fs;
	vector<int> d_aps;

	vector<int> d_fp;
	vector<int> d_app;

	vector<int> d_rang;
	vector<int> d_ddi;
	vector<int> d_dde;
	vector<vector<int>> d_MatAdjacence;
	vector<vector<int>> d_MatDistance;
	vector<int> d_num;
	vector<int> d_prem;
	vector<int> d_pilch;
	vector<int> d_cfc;
	vector<int> d_tarj;
	vector<int> d_pred;
	vector<int> d_ro;
	vector<bool> d_entarj;

	// Graphe Reduit
	vector<int> d_fsr;
	vector<int> d_apsr;
	vector<int> d_br;

	// Ordonnancement
	vector<int> d_fpc;
	vector<int> d_appc;
	vector<int> d_lc;

	void empiler(int x, int* pilch);
	void empiler(int x, vector<int>& pilch);
	int depiler(vector<int>& v);
	void depiler(int s, vector<int>& v);
public:
	Graphe(vector<int> fs, vector<int> aps);
	Graphe(vector<vector<int>> MatAdjacence);

	vector<int> getFS();
	vector<int> getAPS();
	vector<int> getFP();
	vector<int> getAPP();
	vector<int> getRANG();
	vector<int> getDDI();
	vector<int> getDDE();
	vector<vector<int>> getADJACENCE();
	vector<vector<int>> getDISTANCE();
	vector<int> getNUM();
	vector<int> getPREM();
	vector<int> getPILCH();
	vector<int> getCFC();
	vector<int> getTARJ();
	vector<int> getPRED();
	vector<int> getRO();

	// Graphe Reduit
	vector<int> getFSR();
	vector<int> getAPSR();
	vector<int> getBR();

	// Ordonnancement
	vector<int> getFPC();
	vector<int> getAPPC();
	vector<int> getLC();

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

	// PROBLEM
	void det_app();

	// PROBLEM
	void det_fp();

	// TESTED
	void Mat_dist();

	void desc_large(int r, vector<int>& dist);

	// PROBLEM
	void traverse(int s);

	// PROBLEM
	void tarjan();

	// PROBLEM
	void graphe_reduit();

	// PROBLEM
	void base_graphe_reduit();

	// PROBLEM
	void ordonnancement(vector<int> d);

	int d_p;	// tarjan
};

#endif // !GRAPHE_H
