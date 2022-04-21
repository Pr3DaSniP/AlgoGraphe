#ifndef GRAPHEORIENTEVALUE_H
#define GRAPHEORIENTEVALUE_H

#include "GrapheOriente.h"

class GrapheOrienteValue : public GrapheOriente {
private:
	// ORDONNANCEMENT
	// FPC & APPC & LC
	vector<int> d_fpc;
	vector<int> d_appc;
	vector<int> d_lc;

	// DISKSTRA
	// D(istance) & PRED
	vector<int> d_dijkstra_d;
	vector<int> d_dijkstra_pred;

	// DANTZIG
	// C(out) & Dantzig_c
	vector<vector<int>> d_cost;
	vector<vector<int>> d_dantzig_cost;
	bool d_presence_circuit_absorbant = false;

	bool dijkstra_appartient(int k, vector<int> S);
	int dijkstra_dmin(vector<int>& S, vector<int>& d);
	bool verifDijkstra();
public:
	GrapheOrienteValue(vector<int> fs, vector<int> aps, vector<vector<int>> cout);
	GrapheOrienteValue(vector<vector<int>> matrice, vector<vector<int>> cout);

	vector<int> getORDONNANCEMENT_FPC();
	vector<int> getORDONNANCEMENT_APPC();
	vector<int> getORDONNANCEMENT_LC();
	vector<int> getDIJKSTRA_D();
	vector<int> getDIJKSTRA_PRED();
	vector<vector<int>> get_COST();
	vector<vector<int>> getDANTZIG_COST();
	bool isPresenceCircuitAbsorbant();

	void ordonnancement();

	void dijkstra(int s);
	
	void dantzig();

	virtual ~GrapheOrienteValue() = default;
};

#endif // !GRAPHEORIENTEVALUE_H