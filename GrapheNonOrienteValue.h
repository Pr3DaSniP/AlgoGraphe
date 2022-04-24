#ifndef GRAPHENONORIENTEVALUE_H
#define GRAPHENONORIENTEVALUE_H

#include "GrapheNonOriente.h"
#include "Arbre.h"
class GrapheNonOrienteValue : public GrapheNonOriente {
private:
	// C(out)
	vector<vector<int>> d_cost;

	// KRUSKAL
	// PREM & PILCH & CFC
	vector<int> d_kruskal_prem;
	vector<int> d_kruskal_pilch;
	vector<int> d_kruskal_cfc;
	
    // STRUCTURE POUR KRUSKAL
    struct arete {
        int s, t;
        int cout;
    };

	int findParent(int v, vector<int> parent);
public:
	GrapheNonOrienteValue(vector<int> fs, vector<int> aps, vector<vector<int>> cout);
	GrapheNonOrienteValue(vector<vector<int>> matrice, vector<vector<int>> cout);

    vector<vector<int>> get_COST();

	vector<int> getKRUSKAL_PREM();
	vector<int> getKRUSKAL_PILCH();
    vector<int> getKRUSKAL_CFC();

    Arbre* kruskal();

	virtual ~GrapheNonOrienteValue() = default;
};

#endif // !GRAPHENONORIENTEVALUE_H
