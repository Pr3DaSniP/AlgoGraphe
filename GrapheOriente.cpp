#include "GrapheOriente.h"

GrapheOriente::GrapheOriente() {}
GrapheOriente::GrapheOriente(vector<Sommet*> fs, vector<Sommet*> aps) : Graphe(fs, aps) {}
GrapheOriente::GrapheOriente(vector<vector<int>> distance) : Graphe(distance) {}

vector<Sommet*> GrapheOriente::getPile() {
	return d_pile;
}
vector<Sommet*> GrapheOriente::getPilch() {
	return d_pilch;
}
vector<Sommet*> GrapheOriente::getPrem() {
	return d_prem;
}
vector<Sommet*> GrapheOriente::getCFC() {
	return d_cfc;
}
vector<Sommet*> GrapheOriente::getRO() {
	return d_ro;
}
void GrapheOriente::dijkstra() {
	//
}
void GrapheOriente::tarjan() {
	//
}
