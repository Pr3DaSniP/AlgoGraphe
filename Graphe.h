#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>

using std::vector;

class Graphe {
protected:
	// FS & APS
	vector<int> d_fs;
	vector<int> d_aps;

	// MATRICE ADJACENCE
	vector<vector<int>> d_matriceAdjacence;

private:
	void FS_APS_to_MATRICE();
	void MATRICE_to_FS_APS();
	
public:
	Graphe(vector<int> fs, vector<int> aps);
	Graphe(vector<vector<int>> matrice);
	
	int getNBSOMMETS();
	vector<int> getFS();
	vector<int> getAPS();
	vector<vector<int>> getMATRICEADJACENCE();

	virtual void initialisation() = 0;	

	virtual ~Graphe() = default;
};

#endif // !GRAPHE_H