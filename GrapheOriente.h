#ifndef GRAPHEORIENTE_H
#define GRAPHEORIENTE_H

#include <iostream>
#include <vector>
#include "Graphe.h"

using std::vector;

class GrapheOriente : public Graphe {
private:
	vector<Sommet*> d_pile;
	vector<Sommet*> d_pilch;
	vector<Sommet*> d_prem;
	vector<Sommet*> d_cfc;
	vector<Sommet*> d_ro;
public:
	GrapheOriente();
	GrapheOriente(vector<Sommet*> fs, vector<Sommet*> aps);
	GrapheOriente(vector<vector<int>> distance);
	
	vector<Sommet*> getPile();
	vector<Sommet*> getPilch();
	vector<Sommet*> getPrem();
	vector<Sommet*> getCFC();
	vector<Sommet*> getRO();
	
	void dijkstra();
	void tarjan();

	virtual ~GrapheOriente() = default;
};

#endif // !GRAPHEORIENTE_H
