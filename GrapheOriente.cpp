#include "GrapheOriente.h"
#include <algorithm>

void GrapheOriente::initialisation() {
	calculDDI();
	calculDDE();
	FS_APS_to_FP_APP();
	calculMatDistance();
	calculRang();
	calculTarjan();
}

GrapheOriente::GrapheOriente(vector<int> fs, vector<int> aps) : Graphe(fs, aps) { initialisation(); }

GrapheOriente::GrapheOriente(vector<vector<int>> matrice) : Graphe(matrice) { initialisation(); }


vector<int> GrapheOriente::getFP() {
	return d_fp;
}

vector<int> GrapheOriente::getAPP() {
	return d_app;
}

vector<int> GrapheOriente::getDDI() {
	return d_ddi;
}

vector<int> GrapheOriente::getDDE() {
	return d_dde;
}

vector<vector<int>> GrapheOriente::getMATRICE_DISTANCE() {
	return d_matriceDistance;
}

vector<int> GrapheOriente::getRANG() {
	return d_rang;
}

vector<int> GrapheOriente::getTARJAN_CFC() {
	return d_tarjan_cfc;
}

vector<int> GrapheOriente::getTARJAN_NUM() {
	return d_tarjan_num;
}

vector<int> GrapheOriente::getTARJAN_PREM() {
	return d_tarjan_prem;
}

vector<int> GrapheOriente::getTARJAN_PILCH() {
	return d_tarjan_pilch;
}

vector<int> GrapheOriente::getFSR() {
	return d_fsr;
}

vector<int> GrapheOriente::getAPSR() {
	return d_apsr;
}

vector<int> GrapheOriente::getBR() {
    return d_br;
}

void GrapheOriente::calculDDI() {
	int n = d_aps[0];
	d_ddi.resize(n + 1);
	d_ddi[0] = n;
	for (int k = 1; k < d_fs[0]; ++k) {
		if (d_fs[k] != 0) {
			d_ddi[d_fs[k]]++;
		}
	}
}

void GrapheOriente::calculDDE() {
	int n = d_aps[0];
	d_dde.resize(n + 1);
	d_dde[0] = n;
	for (int s = 1; s < n; ++s) {
		d_dde[s] = d_aps[s + 1] - d_aps[s] - 1;
	}
	d_dde[n] = d_fs[0] - d_aps[n];
}

void GrapheOriente::FS_APS_to_FP_APP() {
	vector<vector<int>> transpose(d_matriceAdjacence.size(), vector<int>(d_matriceAdjacence[0].size()));
	for (int i = 1; i < transpose.size(); ++i) {
		for (int j = 1; j < transpose[i].size(); ++j) {
			transpose[j][i] = d_matriceAdjacence[i][j];
		}
	}

	transpose[0][0] = d_matriceAdjacence[0][0];
	transpose[0][1] = d_matriceAdjacence[0][1];

	int nbSommets = transpose[0][0];
	int nbArcs = transpose[0][1];
	d_app.resize(nbSommets + 1);
	d_app[0] = nbSommets;
	d_fp.resize(nbSommets + nbArcs + 1);
	d_fp[0] = nbSommets + nbArcs;
	int k = 1;
	for (int i = 1; i <= nbSommets; ++i) {
		d_app[i] = k;
		for (int j = 1; j <= nbSommets; ++j) {
			if (transpose[i][j] == 1) {
				d_fp[k++] = j;
			}
		}
		d_fp[k++] = 0;
	}
}

vector<int> GrapheOriente::distanceFrom(int s) {
	vector<int> tab;
	int n = d_aps[0];
	tab.resize(n + 1);
	for (int i = 1; i <= d_aps[0]; i++)
		tab[i] = -1;
	tab[s] = 0;
	vector<int> file(n + 1);
	for (int i = 0; i < n; ++i) {
		file[i] = 0;
	}
	int distance = 1;
	int indexFs;
	int debut = 1, courant = 0, fin = 1;
	file[debut] = s;
	while (courant < fin) {
		for (int i = courant + 1; i <= debut; i++) {
			indexFs = d_aps[file[i]];
			while (d_fs[indexFs] != 0) {
				if (tab[d_fs[indexFs]] == -1) {
					tab[d_fs[indexFs]] = distance;
					fin++;
					file[fin] = d_fs[indexFs];
				}
				indexFs++;
			}
		}
		courant = debut;
		debut = fin;
		distance++;
	}
	return tab;
}

void GrapheOriente::calculMatDistance() {
	int n = d_aps[0];
	d_matriceDistance.resize(n + 1);
	for (int i = 0; i <= n; ++i) {
		d_matriceDistance[i].resize(n + 1);
	}
	for (int i = 1; i <= n; ++i) {
		d_matriceDistance[i] = distanceFrom(i);
	}
	d_matriceDistance[0][0] = n;
	d_matriceDistance[0][1] = d_fs[0] - n;
}

void GrapheOriente::empiler(int x, vector<int>& pilch) {
	pilch[x] = pilch[0];
	pilch[0] = x;
}

void GrapheOriente::calculRang() {
	int n = d_aps[0], taillefs = d_fs[0], s, k, h, t;
	d_rang.resize(n + 1);
	vector<int> ddi(n + 1), pilch(n + 1), prem(n + 1);
	// calcul de ddi
	for (int i = 1; i <= taillefs; ++i) {
		s = d_fs[i];
		if (s > 0) {
			ddi[s]++;
		}
	}
	// calcul du rang
	pilch[0] = 0;
	for (s = 1; s <= n; ++s) {
		d_rang[s] = -1;
		if (ddi[s] == 0) {
			empiler(s, pilch);
		}
	}
	k = -1;
	s = pilch[0];
	prem[0] = s;
	while (pilch[0] > 0) {
		k++;
		pilch[0] = 0;
		while (s > 0) {
			d_rang[s] = k;
			h = d_aps[s];
			t = d_fs[h];
			while (t > 0) {
				ddi[t]--;
				if (ddi[t] == 0) {
					empiler(t, pilch);
				}
				h++;
				t = d_fs[h];
			}
			s = pilch[s];
		}
		s = pilch[0];
		prem[k + 1] = s;
	}
	d_rang[0] = n;
}

void GrapheOriente::calculTarjan() {
	int n = d_aps[0];
	vector<int> num(n + 1, -1), cfc(n + 1, -1);
	vector<bool> entarj(n + 1, false);
	vector<int> tarj;
	d_tarjan_prem.push_back(0);
	d_tarjan_pilch.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (num[i] == -1) {
			dfs(i, num, cfc, tarj, entarj);
		}
	}
	d_tarjan_num = num;
	d_tarjan_num[0] = d_tarjan_num.size() - 1;
	d_tarjan_cfc = cfc;
	d_tarjan_cfc[0] = d_tarjan_cfc.size() - 1;
	d_tarjan_prem[0] = d_tarjan_prem.size() - 1;
}

void GrapheOriente::dfs(int u, vector<int>& num, vector<int>& cfc, vector<int>& tarj, vector<bool>& entarj) {
	static int time = 1;
	num[u] = cfc[u] = time;
	time += 1;
	tarj.push_back(u);
	entarj[u] = true;

	int t;
	for (int k = d_aps[u]; (t = d_fs[k]) != 0; ++k) {
		if (num[t] == -1) {
			dfs(t, num, cfc, tarj, entarj);
			cfc[u] = std::min(cfc[u], cfc[t]);
		}
		else if (entarj[t]) {
			cfc[u] = std::min(cfc[u], num[t]);
		}
	}

	if (cfc[u] == num[u]) {
		int tmp = tarj.back();
		tarj.pop_back();
		while (tmp != u) {
			entarj[tmp] = false;
			empiler(tmp, d_tarjan_pilch);
			tmp = tarj.back();
			tarj.pop_back();
		}
		entarj[u] = false;
		empiler(u, d_tarjan_pilch);
		d_tarjan_prem.push_back(u);
		d_tarjan_pilch[0] = 0;
	}
}

void GrapheOriente::calculGrapheReduit() {
	// TODO : calcul du graphe reduit
}

void GrapheOriente::calculBaseReduit() {
	// TODO : calcul de la base reduite
}
