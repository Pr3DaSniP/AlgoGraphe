#include "GrapheNonOrienteValue.h"
#include <algorithm>

int GrapheNonOrienteValue::findParent(int v, vector<int> parent) {
	if (parent[v] == v) {
		return v;
	}
	else {
		return findParent(parent[v], parent);
	}
}

GrapheNonOrienteValue::GrapheNonOrienteValue(vector<int> fs, vector<int> aps, vector<vector<int>> cout) : GrapheNonOriente(fs, aps), d_cost{ cout } {}

GrapheNonOrienteValue::GrapheNonOrienteValue(vector<vector<int>> matrice, vector<vector<int>> cout) : GrapheNonOriente(matrice), d_cost{ cout } {}

vector<vector<int>> GrapheNonOrienteValue::get_COST()
{
    return d_cost;
}

vector<int> GrapheNonOrienteValue::getKRUSKAL_PREM()
{
	return d_kruskal_prem;
}

vector<int> GrapheNonOrienteValue::getKRUSKAL_PILCH()
{
	return d_kruskal_pilch;
}

vector<int> GrapheNonOrienteValue::getKRUSKAL_CFC()
{
	return d_kruskal_cfc;
}

Arbre* GrapheNonOrienteValue::kruskal() {
	vector<arete> a;
	int n = d_aps[0];

    vector<vector<int>> matriceArbre(n+1, vector<int>(n+1));

	int t;
	for (int u = 1; u < n; ++u) {
		for (int k = d_aps[u]; (t = d_fs[k]) != 0; ++k) {
			a.push_back({ u, t, d_cost[u][t] });
		}
	}
	std::sort(a.begin(), a.end(), [](arete a, arete b) {
		return a.cout < b.cout;
	});

	d_kruskal_cfc.resize(n + 1);
	d_kruskal_prem.resize(n + 1);
	d_kruskal_pilch.resize(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		d_kruskal_cfc[i] = i;
		d_kruskal_prem[i] = i;
	}
	d_kruskal_cfc[0] = n;
	d_kruskal_prem[0] = n;
	d_kruskal_pilch[0] = n;

	vector<int> parent(n + 1);
	for (int i = 0; i <= n; ++i) {
		parent[i] = i;
	}

    vector<arete> _Arbre(n - 1);
	int count = 0;
	int i = 0;
	while (count < n - 1) {
		arete currentArete = a[i];

		int src = findParent(currentArete.s, parent);
		int dest = findParent(currentArete.t, parent);

		if (src != dest) {

			d_kruskal_cfc[dest] = currentArete.s;
			d_kruskal_pilch[src] = currentArete.t;
            matriceArbre[currentArete.s][currentArete.t] = 1;
            matriceArbre[currentArete.t][currentArete.s] = 1;

            _Arbre[count] = currentArete;
			count++;
			parent[src] = dest;
		}
		++i;
	}
    matriceArbre[0][0] = n;
    matriceArbre[0][1] = count*2;
    return new Arbre{matriceArbre};
}
