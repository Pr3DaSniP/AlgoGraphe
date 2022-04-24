#ifndef ARBRE_H
#define ARBRE_H

#include "GrapheNonOriente.h"

class Arbre : public GrapheNonOriente {
private:
	// PRUFER
	// PRF
	vector<int> d_codage_prf;
	bool d_is_prf_encoded;

	virtual void initialisation() override;
public:
	Arbre(vector<int> fs, vector<int> aps);
	Arbre(vector<vector<int>> matrice);

	vector<int> getPRUFER_CODE();
	
	bool is_prf_encoded();

	void decode_prufer();
	void encode_prufer();
};

#endif // !ARBRE_H