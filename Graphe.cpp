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
vector<int> Graphe::getNUM() { return d_num; }
vector<int> Graphe::getPREM() { return d_prem; }
vector<int> Graphe::getPILCH() { return d_pilch; }
vector<int> Graphe::getCFC() { return d_cfc; }
vector<int> Graphe::getTARJ() { return d_tarj; }
vector<int> Graphe::getPRED() { return d_pred; }
vector<int> Graphe::getRO() { return d_ro; }
vector<int> Graphe::getFSR() { return d_fsr; }
vector<int> Graphe::getAPSR() { return d_apsr; }
vector<int> Graphe::getBR() { return d_br; }
vector<int> Graphe::getFP() { return d_fp; }
vector<int> Graphe::getAPP() { return d_app; }

void Graphe::empiler(int x, int* pilch) {
	pilch[x] = pilch[0];
	pilch[0] = x;
}

void Graphe::empiler(int x, vector<int>& pilch) {
	pilch[x] = pilch[0];
	pilch[0] = x;
}

int Graphe::depiler(vector<int>& v) {
	int n = v.back();
	v.pop_back();
	return n;
}

void Graphe::depiler(int s, vector<int>& v) {
	v[s] = 0;
}

void Graphe::init() {
	rang();
	demi_degre_int();
	demi_degre_ext();
	det_fp();
	det_app();
	Mat_dist();
	tarjan();
	graphe_reduit();
	base_graphe_reduit();
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

void Graphe::det_app() {
	/*
	int n = d_aps[0];
	d_app.resize(n + 1);
	d_app[0] = n;
	d_app[1] = 1;
	for (int i = 1; i < n; ++i) {
		d_app[i + 1] = d_app[i] + d_ddi[i] + 1;
	}
	*/
}

void Graphe::det_fp() {
	/*
	int n = d_aps[0];
	int m = d_fs[0];
	d_fp.resize(m + 1);
	d_fp[0] = m;

	int k = 1, j;
	for (int i = 1; i <= n; ++i) {
		while ((j = d_fs[k]) > 0) {
			d_fp[d_app[j]] = i;
			d_app[j]++;
			k++;
		}
		k++;
	}
	d_fp[d_app[n]] = 0;
	for (int i = n - 1; i >= 1; --i) {
		d_fp[d_app[i]] = 0;
		d_app[i + 1] = d_app[i] + 1;
	}
	d_app[1] = 1;
	*/
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

void Graphe::traverse(int s) {
	/*
	int t, a = 0, u;
	d_p++;
	d_num[s] = d_p;
	d_ro[s] = d_p;
	empiler(s, d_tarj);
	d_entarj[s] = true;
	for (int k = d_aps[s]; (t = d_fs[k]) != 0; ++k) {
		if (d_num[t] == 0) {
			d_pred[t] = s;
			traverse(t);
			if (d_ro[t] < d_ro[s]) {
				d_ro[s] = d_ro[t];
			}
			else {
				if ((d_num[t] < d_ro[s]) && d_entarj[t]) {
					d_ro[s] = d_num[t];
				}
			}
		}
	}
	if (d_ro[s] == d_num[s]) {
		a++;
		do {
			u = depiler(d_tarj);
			d_entarj[u] = false;
			empiler(u, d_pilch);
			d_cfc[u] = a;
		} while (u != s);
		d_prem[a] = d_pilch[0];
		d_pilch[0] = 0;
	}
	*/
}

void Graphe::tarjan() {
	/*
	int n = d_aps[0];
	d_prem.resize(n + 1);
	d_pilch.resize(n + 1);
	d_cfc.resize(n + 1);
	d_pred.resize(n + 1);
	d_tarj.resize(n + 1);
	d_entarj.resize(n + 1);
	d_num.resize(n + 1);
	d_ro.resize(n + 1);
	int k = 0;
	for (int i = 1; i <= n; ++i) {
		d_num[i] = 0;
		d_pred[i] = 0;
		d_ro[i] = 0;
		d_entarj[i] = false;
	}
	d_pilch[0] = 0;
	d_tarj[0] = 0;
	for (int s = 1; s <= n; ++s) {
		if (d_num[s] == 0)
			traverse(s);
	}
	d_prem[0] = k;
	*/
}

void Graphe::graphe_reduit() {
	/*
	int s, kr = 1, nbc = d_prem[0];
	bool* deja_mis = new bool[nbc + 1];
	d_fsr.resize(d_fs[0] + 1);
	d_apsr.resize(d_aps[0] + 1);
	d_apsr[0] = kr;
	for (int i = 1; i < nbc; ++i) {
		d_apsr[i] = kr;
		for (int j = 1; j <= nbc; ++j) {
			deja_mis[j] = false;
		}
		deja_mis[i] = true;
		s = d_prem[0];
		while (s != 0) {
			for (int t = d_aps[s]; d_fs[t] != 0; ++t) {
				if (deja_mis[d_cfc[d_fs[t]]] == false) {
					d_fs[kr] = d_cfc[d_fs[t]];
					kr++;
					deja_mis[d_cfc[d_fs[t]]] = true;
				}
			}
			s = d_pilch[s];
		}
		d_fsr[kr] = 0;
		kr++;
	}
	d_fsr[0] = kr - 1;
	*/
}

void Graphe::base_graphe_reduit() {
	/*
	int nr = d_apsr[0];
	d_br.resize(nr + 1);
	int* ddir = new int[nr + 1];
	for (int i = 0; i <= nr; ++i) {
		ddir[i] = 0;
	}
	for (int kr = 1; kr <= d_fsr[kr]; ++kr) {
		ddir[d_fsr[kr]]++;
	}
	int nb = 0;
	for (int c = 1; c <= nr; ++c) {
		if (ddir[c] == 0)
			d_br[++nb] = c;
	}
	d_br[0] = nb;
	*/
}

void Graphe::ordonnancement(vector<int> d) {
	/*
	int n = d_app[0], m = d_fp[0];
	d_fpc.resize(m + 1);
	d_appc.resize(n + 1);
	d_appc[0] = n;
	d_lc.resize(n + 1);
	d_lc[0] = n;

	int kc, t, lg;
	d_lc[1] = 0;
	d_fpc[1] = 0;
	d_appc[1] = 1;

	kc = 1;
	for (int s = 2; s <= n; s++) {
		d_lc[s] = 0;
		d_appc[s] = kc + 1;
		for (int k = d_app[s]; (t = d_fp[k]) != 0; ++k) {
			lg = d_lc[t] + d[t];
			if (lg >= d_lc[s]) {
				if (lg > d_lc[s]) {
					d_lc[s] = lg;
					kc = d_appc[s];
					d_fpc[kc] = t;
				}
				else {
					kc++;
					d_fpc[kc] = t;
				}
			}
		}
		kc++;
		d_fpc[kc] = 0;
	}
	d_fpc[0] = kc;
	*/
}