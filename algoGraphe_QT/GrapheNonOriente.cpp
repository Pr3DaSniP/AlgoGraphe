#include "GrapheNonOriente.h"

void GrapheNonOriente::initialisation() {
	// Juste parce que c'est obligatoire, mais la fonction n'est pas utile
}

GrapheNonOriente::GrapheNonOriente(vector<int> fs, vector<int> aps) : Graphe(fs, aps) {}

GrapheNonOriente::GrapheNonOriente(vector<vector<int>> matrice) : Graphe(matrice) {}