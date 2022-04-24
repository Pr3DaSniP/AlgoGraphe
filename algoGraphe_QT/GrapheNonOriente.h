#ifndef GRAPHENONORIENTE_H
#define GRAPHENONORIENTE_H

#include "Graphe.h"

class GrapheNonOriente : public Graphe {
private:
	virtual void initialisation() override;
public:
	GrapheNonOriente(vector<int> fs, vector<int> aps);
	GrapheNonOriente(vector<vector<int>> matrice);

	virtual ~GrapheNonOriente() = default;
};

#endif // !GRAPHENONORIENTE_H