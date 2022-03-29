#include "GrapheOrienteValue.h"

GrapheOrienteValue::GrapheOrienteValue() {}
GrapheOrienteValue::GrapheOrienteValue(vector<Sommet*> fs, vector<Sommet*> aps)	: GrapheOriente(fs, aps) {}
GrapheOrienteValue::GrapheOrienteValue(vector<vector<int>> distance) : GrapheOriente(distance) {}

void GrapheOrienteValue::ordonnancement() {
	//
}
void GrapheOrienteValue::dantzig() {
	//
}
