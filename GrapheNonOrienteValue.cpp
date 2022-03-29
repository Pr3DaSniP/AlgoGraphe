#include "GrapheNonOrienteValue.h"

GrapheNonOrienteValue::GrapheNonOrienteValue() {}
GrapheNonOrienteValue::GrapheNonOrienteValue(vector<Sommet*> fs, vector<Sommet*> aps) : GrapheNonOriente(fs, aps) {}
GrapheNonOrienteValue::GrapheNonOrienteValue(vector<vector<int>> distance) : GrapheNonOriente(distance) {}

vector<Sommet*> GrapheNonOrienteValue::getKruskal() {
	return d_kruskal;
}

void GrapheNonOrienteValue::kruskal() {
	//
}