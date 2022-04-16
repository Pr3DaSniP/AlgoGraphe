#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graphe {
protected:
	// FS & APS
	vector<int> d_fs;
	vector<int> d_aps;

	// MATRICE ADJACENCE
	vector<vector<int>> d_matriceAdjacence;

	// FP & APP
	vector<int> d_fp;
	vector<int> d_app;

	// DDI & DDE
	vector<int> d_ddi;
	vector<int> d_dde;

	// MATRICE DES DISTANCES
	vector<vector<int>> d_matriceDistance;

	// RANG
	vector<int> d_rang;

	// TARJAN
	vector<int> d_tarjan_num;
	vector<int> d_tarjan_prem;
	vector<int> d_tarjan_pilch;
	vector<int> d_tarjan_cfc;

	// FSR & APSR
	vector<int> d_fsr;
	vector<int> d_apsr;

	// BR
	vector<int> d_br;

public:
	// CONSTRUCTEUR
	Graphe(vector<int> fs, vector<int> aps) : d_fs{ fs }, d_aps{ aps } { FS_APS_to_MATRICE(); initialisation(); }
	Graphe(vector<vector<int>> matrice) : d_matriceAdjacence{ matrice } { MATRICE_to_FS_APS(); initialisation(); }

	// GETTERS
	int getNBSOMMETS() {
		return d_aps[0];
	}
	vector<int> getFS() {
		return d_fs;
	}
	vector<int> getAPS() {
		return d_aps;
	}
	vector<vector<int>> getMATRICEADJACENCE() {
		return d_matriceAdjacence;
	}
	vector<int> getFP() {
		return d_fp;
	}
	vector<int> getAPP() {
		return d_app;
	}
	vector<int> getDDI() {
		return d_ddi;
	}
	vector<int> getDDE() {
		return d_dde;
	}
	vector<vector<int>> getMATRICEDISTANCE() {
		return d_matriceDistance;
	}
	vector<int> getRANG() {
		return d_rang;
	}
	vector<int> getTARJCFC() {
		return d_tarjan_cfc;
	}
	vector<int> getTARJNUM() {
		return d_tarjan_num;
	}
	vector<int> getTARJPREM() {
		return d_tarjan_prem;
	}
	vector<int> getTARJPILCH() {
		return d_tarjan_pilch;
	}
	vector<int> getFSR() {
		return d_fsr;
	}
	vector<int> getAPSR() {
		return d_apsr;
	}

	void initialisation() {
		calculDDI();
		calculDDE();
		FS_APS_to_FP_APP();
		calculMatDistance();
		calculRang();
		calculTarjan();
		calculGrapheReduit();
	}

	// UTILS
	int depiler(vector<int>& v)
	{
		int tmp = v.back();
		v.pop_back();
		return tmp;
	}
	void empiler(int x, vector<int>& pilch) {
		pilch[x] = pilch[0];
		pilch[0] = x;
	}

	// DONE
	void FS_APS_to_MATRICE() {
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
	// DONE
	void MATRICE_to_FS_APS() {
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

	// A VERIFIER
	void calculDDI() {
		int n = d_aps[0];
		d_ddi.resize(n + 1);
		d_ddi[0] = n;
		for (int k = 1; k < d_fs[0]; ++k) {
			if (d_fs[k] != 0) {
				d_ddi[d_fs[k]]++;
			}
		}
	}

	// A VERIFIER
	void calculDDE() {
		int n = d_aps[0];
		d_dde.resize(n + 1);
		d_dde[0] = n;
		for (int s = 1; s < n; ++s) {
			d_dde[s] = d_aps[s + 1] - d_aps[s] - 1;
		}
		d_dde[n] = d_fs[0] - d_aps[n];
	}
	
	// DONE
	void FS_APS_to_FP_APP() {
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

	// A VERIFIER
	vector<int> distanceFrom(int s) {
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

	// A VERIFIER
	void calculMatDistance() {
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

	// DONE
	void calculRang() {
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

	// A VERIFIER
	void calculTarjan() {
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
	void dfs(int u, vector<int>& num, vector<int>& cfc, vector<int>& tarj, vector<bool>& entarj) {
		static int time = 1;
		num[u] = cfc[u] = time;
		time += 1;
		tarj.push_back(u);
		entarj[u] = true;

		int t;
		for (int k = d_aps[u]; (t = d_fs[k]) != 0; ++k) {
			if (num[t] == -1) {
				dfs(t, num, cfc, tarj, entarj);
				cfc[u] = min(cfc[u], cfc[t]);
			}
			else if(entarj[t]) {
				cfc[u] = min(cfc[u], num[t]);
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

	// A FIX
	void calculGrapheReduit() {
		/*int s, kr = 1, nbc = d_tarjan_prem[0];
		vector<bool> deja_mis(nbc + 1, false);
		d_fsr.resize(d_fs[0] + 1);
		d_apsr.resize(nbc + 1);
		d_apsr[0] = kr;
		for (int i = 1; i < nbc; ++i) {
			d_apsr[i] = kr;
			deja_mis[i] = true;
			s = d_tarjan_prem[0];
			while (s != 0) {
				for (int t = d_aps[s]; d_fs[t] != 0; ++t) {
					if (deja_mis[d_tarjan_cfc[d_fs[t]]] == false) {
						d_fsr[kr] = d_tarjan_cfc[d_fs[t]];
						kr++;
						deja_mis[d_tarjan_cfc[d_fs[t]]] = true;
					}
				}
				s = d_tarjan_pilch[s];
			}
			d_fsr[kr] = 0;
			kr++;
		}
		d_fsr[0] = kr - 1;*/

		vector<bool> marque(d_aps[0], false);
		int kr = 1;
		int s;
		int t;
		d_apsr.push_back(0);
		for (int c = 1; c <= d_tarjan_prem[0]; ++c) {
			marque[c] = true;
			s = d_tarjan_prem[c];
			d_apsr.push_back(kr);
			while (s != 0) {
				for (int k = d_aps[s]; (t = d_fs[k]) != 0; ++k) {
					if (marque[d_tarjan_cfc[t]] == false) {
						++kr;
						d_fsr.push_back(d_tarjan_cfc[t]);
						marque[d_tarjan_cfc[t]] = true;
					}
				}
				s = d_tarjan_pilch[s];
			}
			++kr;
			d_fsr.push_back(0);
		}
		d_apsr[0] = d_tarjan_prem.size();
		d_fsr[0] = kr;
	}
	void calculBaseReduit() {
		int n = d_apsr[0];
		d_br.resize(n + 1);
		vector<int> ddir(n + 1, 0);
		for (int kr = 1; kr <= d_fsr[0]; ++kr) {
			ddir[d_fsr[kr]]++;
		}
		int nb = 0;
		for (int c = 1; c <= n; ++c) {
			if (ddir[c] == 0) {
				d_br[++nb] = c;
			}
		}
		d_br[0] = nb;
	}
};


class GrapheOrienteValue : public Graphe {
private:
	// ORDONNANCEMENT
	// FPC & APPC & LC
	vector<int> d_fpc;
	vector<int> d_appc;
	vector<int> d_lc;

	// DISKSTRA
	// D(istance) & PRED
	vector<int> d_d;
	vector<int> d_pred;

	// DANTZIG
	// C(out)
	vector<vector<int>> d_c;

public:
	// CONSTRUCTEUR
	GrapheOrienteValue(vector<int> fs, vector<int> aps) : Graphe(fs,aps) {}
	GrapheOrienteValue(vector<vector<int>> matrice) : Graphe(matrice) {}

	// GETTERS
	vector<int> getFPC() {
		return d_fpc;
	}
	vector<int> getAPPC() {
		return d_appc;
	}
	vector<int> getLC() {
		return d_lc;
	}
	vector<int> getD() {
		return d_d;
	}
	vector<int> getPRED() {
		return d_pred;
	}
	vector<vector<int>> getC() {
		return d_c;
	}

	void ordonnancement() {}

	void dijkstra() {}

	void dantzig() {}
};

class GrapheNonOrienteValue : public Graphe {
private:
	// KRUSKAL
	// PREM & PILCH & CFC
	vector<int> d_kruskal_prem;
	vector<int> d_kruskal_pilch;
	vector<int> d_kruskal_cfc;

	// PRUFER
	// PRF
	vector<int> d_prf;

public:
	// CONSTRUCTEUR
	GrapheNonOrienteValue(vector<int> fs, vector<int> aps) : Graphe(fs, aps) {}
	GrapheNonOrienteValue(vector<vector<int>> matrice) : Graphe(matrice) {}

	// GETTERS
	vector<int> getKRUSKALPREM() {
		return d_kruskal_prem;
	}
	vector<int> getKRUSKALPILCH() {
		return d_kruskal_pilch;
	}
	vector<int> getKRUSKALCFC() {
		return d_kruskal_cfc;
	}
	vector<int> getPRF() {
		return d_prf;
	}

	void kruskal() {}

	void prufer() {}
};


void afficher(string s, vector<int> tab) {
	cout << s << endl;
	for (int i = 0; i < tab.size(); ++i) {
		cout << tab[i] << "\t";
	}
	cout << endl;
}
void afficher(string s, vector<vector<int>> tab) {
	cout << s << endl;
	for (int i = 0; i < tab.size(); ++i) {
		for (int j = 0; j < tab[i].size(); ++j) {
			cout << tab[i][j] << "\t";
		}
		cout << endl;
	}
}
void seperator() {
	cout << "\n===========================================================================\n";
}
void afficherSommet(Graphe& G) {
	seperator();
	for (int i = 0; i <= G.getNBSOMMETS(); ++i) {
		cout << i << "\t";
	}
	seperator();
}

void main() {

	//vector<int> fs = { 12,2,3,0,4,5,0,2,4,0,5,0,0 };
	//vector<int> aps = { 5,1,4,7,10,11 };

	//vector<int> fs = { 22,2,3,4,0,0,6,0,7,0,1,2,6,0,3,4,7,8,0,4,0,7,0 };
	//vector<int> aps = { 8,1,5,6,8,10,14,19,21 };

	/*vector<vector<int>> matrice =
	{
		{8,13,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0,1},
		{0,0,0,0,0,0,1,0,0},
		{0,1,0,0,0,0,0,1,0},
		{0,1,0,1,0,1,0,0,0},
		{0,0,0,0,1,0,1,0,0}
	};*/

	//vector<int> fs = { 13,2,0,3,0,1,4,0,5,0,6,0,4,0 };
	//vector<int> aps = { 6,1,3,5,8,10,12 };
	vector<int> fs = {
		24,
		2,3,0,
		4,5,0,
		0,
		6,0,
		6,0,
		7,0,
		3,5,0,
		1,0,
		10,0,
		4,8,9,0
	};
	vector<int> aps = {10,1,4,7,8,10,12,14,17,19,21};

	vector<vector<int>> matrice =
	{
		{5, 7, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0, 0, 1, 0, 0, 1},
		{0, 0, 0, 0, 0, 1},
		{0, 0, 1, 0, 0, 0}
	};

	Graphe G{ fs,aps };

	afficherSommet(G);

	afficher("FS : ", G.getFS());
	afficher("APS : ", G.getAPS());

	seperator();

	afficher("FSR : ", G.getFSR());
	afficher("APSR : ", G.getAPSR());

	
	/*seperator();

	afficher("CFC : ", G.getTARJCFC());
	afficher("NUM : ", G.getTARJNUM());
	afficher("PREM : ", G.getTARJPREM());
	afficher("PILCH : ", G.getTARJPILCH());*/

}