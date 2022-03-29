#ifndef GRAPHENONORIENTEVALUE_H
#define GRAPHENONORIENTEVALUE_H

#include <iostream>
#include <vector>
#include "GrapheNonOriente.h"

class GrapheNonOrienteValue : public GrapheNonOriente {
private:
	vector<Sommet*> d_kruskal;
public:
	GrapheNonOrienteValue();
	GrapheNonOrienteValue(vector<Sommet*> fs, vector<Sommet*> aps);
	GrapheNonOrienteValue(vector<vector<int>> distance);
	vector<Sommet*> getKruskal();

	void kruskal();

	virtual ~GrapheNonOrienteValue() = default:
};

#endif // !GRAPHENONORIENTEVALUE_H
