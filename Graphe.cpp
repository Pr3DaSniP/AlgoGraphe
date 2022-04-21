#include "Graphe.h"

Graphe::Graphe(vector<int> fs, vector<int> aps) : d_fs{ fs }, d_aps{ aps } { FS_APS_to_MATRICE(); }

Graphe::Graphe(vector<vector<int>> matrice) : d_matriceAdjacence{ matrice } { MATRICE_to_FS_APS(); }

void Graphe::FS_APS_to_MATRICE() {
	int n = d_aps[0];
	d_matriceAdjacence.resize(n + 1);
	for (int i = 0; i <= n; ++i) {
		d_matriceAdjacence[i].resize(n + 1);
	}
	d_matriceAdjacence[0][0] = n;
	d_matriceAdjacence[0][1] = d_fs[0] - n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			d_matriceAdjacence[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		int k = d_aps[i];
		while (d_fs[k] != 0) {
			d_matriceAdjacence[i][d_fs[k++]] = 1;
		}
	}
}

void Graphe::MATRICE_to_FS_APS() {
	int nbSommets = d_matriceAdjacence[0][0];
	int nbArcs = d_matriceAdjacence[0][1];
	d_aps.resize(nbSommets + 1);
	d_aps[0] = nbSommets;
	d_fs.resize(nbSommets + nbArcs + 1);
	d_fs[0] = nbSommets + nbArcs;
	int k = 1;
	for (int i = 1; i <= nbSommets; ++i) {
		d_aps[i] = k;
		for (int j = 1; j <= nbSommets; ++j) {
			if (d_matriceAdjacence[i][j] == 1) {
				d_fs[k++] = j;
			}
		}
		d_fs[k++] = 0;
	}
}

int Graphe::getNBSOMMETS()
{
    return d_aps[0];
}

vector<int> Graphe::getFS()
{
    return d_fs;
}

vector<int> Graphe::getAPS()
{
    return d_aps;
}

vector<vector<int>> Graphe::getMATRICEADJACENCE()
{
	return d_matriceAdjacence;
}
