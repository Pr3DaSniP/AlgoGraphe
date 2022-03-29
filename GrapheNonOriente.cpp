#include "GrapheNonOriente.h"

GrapheNonOriente::GrapheNonOriente() {}
GrapheNonOriente::GrapheNonOriente(vector<Sommet*> fs, vector<Sommet*> aps)	: Graphe(fs, aps) {}

GrapheNonOriente::GrapheNonOriente(vector<vector<int>> distance) : Graphe(distance) {}

vector<Sommet*> GrapheNonOriente::getCPrufer() {
	return d_cprufer;
}

void GrapheNonOriente::prufer() {
	//
}