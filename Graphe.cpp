#include "Graphe.h"

Graphe::Graphe(vector<int> fs, vector<int> aps) : d_fs{ fs }, d_aps{ aps } { fsapsToMATRICE(); init(); }
Graphe::Graphe(vector<vector<int>> MatAdjacence) : d_MatAdjacence{ MatAdjacence } { matriceToFSAPS(); init(); }

vector<int> Graphe::getFS() { return d_fs; }
vector<int> Graphe::getAPS() { return d_aps; }
vector<int> Graphe::getRANG() { return d_rang; }
vector<int> Graphe::getDDI() { return d_ddi; }
vector<int> Graphe::getDDE() { return d_dde; }
vector<vector<int>> Graphe::getADJACENCE() { return d_MatAdjacence; }
vector<vector<int>> Graphe::getDISTANCE() { return d_MatDistance; }

void Graphe::empiler(int x, int* pilch) {
	pilch[x] = pilch[0];
	pilch[0] = x;
}

void Graphe::init() {
	rang();
	demi_degre_int();
	demi_degre_ext();
	Mat_dist();
}

void Graphe::matriceToFSAPS() {
	int nbSommets = d_MatAdjacence[0][0];
	int nbArcs = d_MatAdjacence[0][1];
	d_aps.resize(nbSommets + 1);
	d_aps[0] = nbSommets;
	d_fs.resize(nbSommets + nbArcs + 1);
	d_fs[0] = nbSommets + nbArcs;
	int k = 1;
	for (int i = 1; i <= nbSommets; ++i) {
		d_aps[i] = k;
		for (int j = 1; j <= nbSommets; ++j) {
			if (d_MatAdjacence[i][j] == 1) {
				d_fs[k++] = j;
			}
		}
		d_fs[k++] = 0;
	}
}

void Graphe::fsapsToMATRICE() {
	int nbSommets = d_aps[0];
	int nbArcs = d_fs[0] - nbSommets;
	d_MatAdjacence.resize(nbSommets + 1);
	for (int i = 0; i <= nbSommets; ++i) {
		d_MatAdjacence[i].resize(nbSommets + 1);
	}
	for (int i = 1; i <= nbSommets; ++i) {
		for (int j = 1; j <= nbSommets; ++j) {
			d_MatAdjacence[i][j] = 0;
		}
	}
	int k = 0;
	for (int i = 1; i <= nbSommets; ++i) {
		k = d_aps[i];
		while (d_fs[k] != 0) {
			d_MatAdjacence[i][d_fs[k]] = 1;
			k++;
		}
	}
}

void Graphe::rang() {
	int nbSommets = d_aps[0], taillefs = d_fs[0], s, k, h, t;
	d_rang.resize(nbSommets + 1);
	int* ddi = new int[nbSommets + 1];
	int* pilch = new int[nbSommets + 1];
	int* prem = new int[nbSommets + 1];

	for (int i = 1; i <= nbSommets; i++)
		ddi[i] = 0;

	for (int i = 1; i <= taillefs; i++) {
		s = d_fs[i];
		if (s > 0)
			ddi[s]++;
	}

	pilch[0] = 0;
	for (s = 1; s <= nbSommets; s++) {
		d_rang[s] = -1;
		if (ddi[s] == 0)
			empiler(s, pilch);
	}

	k = -1;
	s = pilch[0];
	prem[0] = s;
	while (pilch[0] > 0) {
		k++;
		pilch[0] = 0;
		while (s > 0)
		{
			d_rang[s] = k;
			h = d_aps[s];
			t = d_fs[h];
			while (t > 0) {
				ddi[t]--;
				if (ddi[t] == 0)
					empiler(t, pilch);
				h++;
				t = d_fs[h];
			}
			s = pilch[s];
		}
		s = pilch[0];
		prem[k + 1] = s;
	}
}

void Graphe::demi_degre_int() {
	int nbSommets = d_aps[0];
	d_ddi.resize(nbSommets + 1);
	d_ddi[0] = nbSommets;
	for (int i = 1; i <= nbSommets; ++i) {
		d_ddi[i] = 0;
	}
	for (int i = 1; i <= nbSommets; ++i) {
		if (d_fs[i] != 0) {
			d_ddi[d_fs[i]]++;
		}
	}
}

void Graphe::demi_degre_ext() {
	int nbSommets = d_aps[0];
	d_dde.resize(nbSommets + 1);
	for (int i = 1; i <= nbSommets; ++i) {
		int nbSuccesseurs = 0; int j = d_aps[i];
		while (d_fs[j] != 0) {
			nbSuccesseurs++;
			j++;
		}
		d_dde[i] = nbSuccesseurs;
	}
	d_dde[0] = nbSommets;
}

void Graphe::Mat_dist() {
	int nombreSommet = d_aps[0];
	d_MatDistance.resize(nombreSommet + 1);
	for (int i = 0; i < d_MatDistance.size(); ++i) {
		d_MatDistance[i].resize(nombreSommet + 1);
	}

	for (int i = 1; i <= nombreSommet; ++i) {
		desc_large(i, d_MatDistance[i]);
	}
	d_MatDistance[0][0] = nombreSommet;
}

void Graphe::desc_large(int r, vector<int>& dist) {
	int nb_som = d_aps[0];
	int i = 0, j = 1, k = 0, ifin, s, t, it;
	int* fil = new int[nb_som + 1];
	fil[0] = nb_som;
	fil[1] = r;
	for (int h = 1; h <= nb_som; h++)
		dist[h] = -1;
	dist[r] = 0;
	while (i < j) {
		k++;
		ifin = j;
		while (i < ifin) {
			i++;
			s = fil[i];
			it = d_aps[s];
			t = d_fs[it];
			while (t > 0) {
				if (dist[t] == -1) {
					j++;
					fil[j] = t;
					dist[t] = k;
				}
				t = d_fs[++it];
			}
		}
	}
}