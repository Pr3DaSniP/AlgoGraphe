#include "GrapheOrienteValue.h"
#include <climits>

GrapheOrienteValue::GrapheOrienteValue(vector<int> fs, vector<int> aps, vector<vector<int>> cout) 
	: GrapheOriente(fs, aps), d_cost{ cout } 
{}

GrapheOrienteValue::GrapheOrienteValue(vector<vector<int>> matrice, vector<vector<int>> cout)
	: GrapheOriente(matrice), d_cost{ cout }
{}

vector<int> GrapheOrienteValue::getORDONNANCEMENT_FPC() {
	return d_fpc;
}

vector<int> GrapheOrienteValue::getORDONNANCEMENT_APPC() {
	return d_appc;
}

vector<int> GrapheOrienteValue::getORDONNANCEMENT_LC() {
	return d_lc;
}

vector<int> GrapheOrienteValue::getDIJKSTRA_D() {
	return d_dijkstra_d;
}

vector<int> GrapheOrienteValue::getDIJKSTRA_PRED() {
	return d_dijkstra_pred;
}

vector<vector<int>> GrapheOrienteValue::get_COST() {
	return d_cost;
}

vector<vector<int>> GrapheOrienteValue::getDANTZIG_COST() {
	return d_dantzig_cost;
}

bool GrapheOrienteValue::isPresenceCircuitAbsorbant() {
	return d_presence_circuit_absorbant;
}

void GrapheOrienteValue::ordonnancement() {
	// TODO : ordonnancement
}

void GrapheOrienteValue::dijkstra(int s) {
	if (verifDijkstra()) {
        d_dijkstra_d.clear();
        d_dijkstra_pred.clear();
		int n = d_aps[0];
		vector<int> visited;
		vector<int> notvisited;
		visited.push_back(s);
		for (int i = 1; i <= n; ++i) {
			if (i != s) {
				notvisited.push_back(i);
			}
		}
		d_dijkstra_d = d_cost[s];
		d_dijkstra_pred.resize(n + 1, s);

		int j = dijkstra_dmin(notvisited, d_dijkstra_d);
		while (!notvisited.empty()) {
			for (int i = 0; i < notvisited.size(); ++i) {
				if (notvisited[i] == j) {
					notvisited.erase(notvisited.begin() + i);
				}
			}
			visited.push_back(j);
			int k = d_fs[d_aps[j]];
			while (k != 0) {
				if (dijkstra_appartient(k, notvisited)) {
					int v = d_dijkstra_d[j] + d_cost[j][k];
					if (v < d_dijkstra_d[k]) {
						d_dijkstra_d[k] = v;
						d_dijkstra_pred[k] = j;
					}
				}
				k = d_fs[d_aps[j]++];
			}
			j = dijkstra_dmin(notvisited, d_dijkstra_d);
		}
		d_dijkstra_d[0] = n;
		d_dijkstra_pred[0] = n;
	}
}

bool GrapheOrienteValue::dijkstra_appartient(int k, vector<int> S) {
	for (int i = 0; i < S.size(); ++i)
	{
		if (S[i] == k)
			return true;
	}
	return false;
}

int GrapheOrienteValue::dijkstra_dmin(vector<int>& S, vector<int>& d) {
	if (!S.empty()) {
		int mini = INT_MAX;
		int indice = 0;
		for (unsigned int i = 0; i < S.size(); ++i) {
			if (mini > d[S[i]]) {
				mini = d[S[i]];
				indice = i;
			}
		}
		return S[indice];
	}
	else return INT_MAX;
}

bool GrapheOrienteValue::verifDijkstra() {
	for (int i = 1; i < d_cost.size(); ++i) {
		for (int j = 1; j < d_cost[i].size(); ++j) {
			if (d_cost[i][j] < 0) {
				return false;
			}
		}
	}
	return true;
}

void GrapheOrienteValue::dantzig() {
	// TODO : dantzig
}
