#ifndef GRAPHEORIENTEVALUE_H
#define GRAPHEORIENTEVALUE_H

#include <iostream>
#include <vector>
#include "GrapheOriente.h"

class GrapheOrienteValue : public GrapheOriente {
public:
	GrapheOrienteValue();
	GrapheOrienteValue(vector<Sommet*> fs, vector<Sommet*> aps);
	GrapheOrienteValue(vector<vector<int>> distance);

	void ordonnancement();
	void dantzig();

	virtual ~GrapheOrienteValue() = default;
};

#endif // !GRAPHEORIENTEVALUE_H
