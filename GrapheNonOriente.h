#ifndef GRAPHENONORIENTE_H
#define GRAPHENONORIENTE_H

#include <iostream>
#include <vector>
#include "Graphe.h"

class GrapheNonOriente : public Graphe {
protected:
	vector<Sommet*> d_cprufer;
public:
	GrapheNonOriente();
	GrapheNonOriente(vector<Sommet*> fs, vector<Sommet*> aps);
	GrapheNonOriente(vector<vector<int>> distance);

	vector<Sommet*> getCPrufer();

	void prufer();

	virtual ~GrapheNonOriente() = default;
};

#endif // !GRAPHENONORIENTE_H
