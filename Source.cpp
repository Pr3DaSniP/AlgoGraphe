#include <iostream>
#include <vector>
#include <algorithm>

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
		//calculGrapheReduit();
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

	// DONE
	void calculTarjan() {
		int n = d_aps[0];
		vector<int> num(n + 1, -1), cfc(n + 1, -1);
		vector<bool> entarj(n + 1, false);
		vector<int> tarj;
		d_tarjan_prem.push_back(0);
		d_tarjan_pilch.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			if (num[i] == -1) {
				//afficher("NUM : ", num);
				//afficher("CFC : ", cfc);
				//afficher("TARJ : ", tarj);
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
	vector<int> d_dijkstra_d;
	vector<int> d_dijkstra_pred;

	// DANTZIG
	// C(out) & Dantzig_c
	vector<vector<int>> d_c;
	vector<vector<int>> d_dantzig_c;
	bool d_presence_circuit_absorbant = false;

public:
	// CONSTRUCTEUR
	GrapheOrienteValue(vector<int> fs, vector<int> aps, vector<vector<int>> cout) : Graphe(fs, aps), d_c{ cout } {}
	GrapheOrienteValue(vector<vector<int>> matrice, vector<vector<int>> cout) : Graphe(matrice), d_c{ cout } {}

	// GETTERS
	vector<int> getORDONNANCEMENTFPC() {
		return d_fpc;
	}
	vector<int> getORDONNANCEMENTAPPC() {
		return d_appc;
	}
	vector<int> getORDONNANCEMENTLC() {
		return d_lc;
	}
	vector<int> getDIJKSTRAD() {
		return d_dijkstra_d;
	}
	vector<int> getDIJKSTRAPRED() {
		return d_dijkstra_pred;
	}
	vector<vector<int>> getC() {
		return d_c;
	}
	vector<vector<int>> getDANTZIGC() {
		return d_dantzig_c;
	}
	bool isPresenceCircuitAbsorbant() {
		return d_presence_circuit_absorbant;
	}

	void ordonnancement() {}

	// DONE
	void dijkstra(int s) {
		if (verifDijkstra()) {
			int n = d_aps[0];
			vector<int> visited;
			vector<int> notvisited;
			visited.push_back(s);
			for (int i = 1; i <= n; ++i) {
				if (i != s) {
					notvisited.push_back(i);
				}
			}
			d_dijkstra_d = d_c[s];
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
						int v = d_dijkstra_d[j] + d_c[j][k];
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
	bool dijkstra_appartient(int k, vector<int> S) {
		for (int i = 0; i < S.size(); ++i)
		{
			if (S[i] == k)
				return true;
		}
		return false;
	}
	int dijkstra_dmin(vector<int>& S, vector<int>& d)
	{
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
	bool verifDijkstra() {
		for (int i = 1; i < d_c.size(); ++i) {
			for (int j = 1; j < d_c[i].size(); ++j) {
				if (d_c[i][j] < 0) {
					return false;
				}
			}
		}
		return true;
	}

	// A FIX
	void dantzig() {
		
		vector<vector<int>> dantzig_c;
		/*dantzig_c.resize(2);
		for (int i = 0; i < 2; ++i) {
			dantzig_c[i].resize(2);
		}
		for (int i = 1; i <= 2; ++i) {
			for (int j = 1; j <= 2; ++j) {
				dantzig_c[i-1][j-1] = d_c[i][j];
			}
		}*/
		
		dantzig_c = d_c;
		
		//while (dantzig_c.size() < d_c.size() - 1) {
			int n = d_c[0][0];
			int i, j, k;
			double x;
			for (k = 1; k < n; ++k) {
				//augmenteMatrice(dantzig_c);
				for (i = 1; i <= k; ++i) {
					for (j = 1; j <= k; ++j) {
						/*dantzig_c[i - 1][k] = min(d_c[i][j], d_c[j][k + 1]);
						dantzig_c[k][i - 1] = min(d_c[k + 1][i], d_c[j][i]);*/
						if ((x = d_c[i][j] + d_c[j][k + 1]) < (d_c[i][k + 1])) {
							dantzig_c[i - 1][k] = x;
						}
						if ((x = d_c[k + 1][j] + d_c[j][i]) < (d_c[k + 1][i])) {
							dantzig_c[k][i - 1] = x;
						}
					}
					if ((d_c[i][k + 1] + d_c[k + 1][i]) < 0) {
						d_presence_circuit_absorbant = true;
						return;
					}
				}
				for (i = 1; i < k; ++i) {
					/*int t = d_c[k + 1][j] + d_c[j][k + 1];
					if (t < 0) {
						d_presence_circuit_absorbant = true;
						return;
					}*/
					for (j = 1; j < k; ++j) {
						//dantzig_c[i - 1][j - 1] = min(d_c[i][j], d_c[i][k + 1] + d_c[k + 1][j]);
						if ((x = d_c[i][k + 1] + d_c[k + 1][j]) < d_c[i][j]) {
							dantzig_c[i - 1][j - 1] = x;
						}
					}
				}
			}
		//}

		d_dantzig_c.resize(d_c.size());
		for(int i = 0; i < d_c.size(); ++i) {
			d_dantzig_c[i].resize(d_c[i].size());
		}

		for(int i = 1; i < d_dantzig_c.size(); ++i) {
			for(int j = 1; j < d_dantzig_c[0].size(); ++j) {
				d_dantzig_c[i][j] = dantzig_c[i - 1][j - 1];
			}
		}

		d_dantzig_c[0][0] = d_c[0][0];
		d_dantzig_c[0][1] = d_c[0][1];

		//d_dantzig_c = d_c;
		//int n = d_c[0][0];
		//int i, j, k;
		//double x;
		//for (k = 1; k < n; k++) {
		//	for (i = 1; i <= k; i++) {
		//		for (j = 1; j <= k; j++) {
		//			
		//			d_dantzig_c[i][k + 1] = min(d_c[i][j], d_c[j][k + 1]);
		//			d_dantzig_c[k + 1][i] = min(d_c[k + 1][i], d_c[j][i]);
		//			
		//
		//			/*if ((x = d_c[i][j] + d_c[j][k + 1]) < (d_c[i][k + 1])) {
		//				d_dantzig_c[i][k + 1] = x;
		//			}
		//			if ((x = d_c[k + 1][j] + d_c[j][i]) < (d_c[k + 1][i])) {
		//				d_dantzig_c[k + 1][i] = x;
		//			}*/
		//		}
		//		/*if ((d_c[i][k + 1] + d_c[k + 1][i]) < 0) {
		//			d_presence_circuit_absorbant = true;
		//			return;
		//		}*/
		//	}
		//	for (i = 1; i <= k; i++) {
		//		int t = d_c[k + 1][j] + d_c[j][k + 1];
		//		if (t < 0) {
		//			d_presence_circuit_absorbant = true;
		//			return;
		//		}
		//		for (j = 1; j <= k; j++) {
		//			d_dantzig_c[i][j] = min(d_c[i][j], d_c[i][k + 1] + d_c[k + 1][j]);
		//			/*if ((x = d_c[i][k + 1] + d_c[k + 1][j]) < d_c[i][j]) {
		//				d_dantzig_c[i][j] = x;
		//			}*/
		//		}
		//	}
		//}
	}
	void augmenteMatrice(vector<vector<int>>& matrice) {
		matrice.resize(matrice.size() + 1);
		int n = matrice.size();
		for (int i = 0; i < n; ++i) {
			matrice[i].resize(n, -99);
		}
		matrice[n - 1][n - 1] = 0;
	}
	
};

class GrapheNonOrienteValue : public Graphe {
private:
	// C(out)
	vector<vector<int>> d_c;

	// KRUSKAL
	// PREM & PILCH & CFC
	vector<int> d_kruskal_prem;
	vector<int> d_kruskal_pilch;
	vector<int> d_kruskal_cfc;

public:
	// CONSTRUCTEUR
	GrapheNonOrienteValue(vector<int> fs, vector<int> aps, vector<vector<int>> cout) : Graphe(fs, aps), d_c{ cout } {}
	GrapheNonOrienteValue(vector<vector<int>> matrice, vector<vector<int>> cout) : Graphe(matrice), d_c{ cout } {}

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

	// STRUCTURE POUR KRUSKAL
	struct arete {
		int s, t;
		int cout;
	};
	
	// A VERIFIER
	void kruskal() {
		vector<arete> a;
		int n = d_aps[0];
		int m = d_fs[0] - n;
		int t;
		for (int u = 1; u < n; ++u) {
			for (int k = d_aps[u]; (t = d_fs[k]) != 0; ++k) {
				a.push_back({ u, t, d_c[u][t] });
			}
		}
		sort(a.begin(), a.end(), [](arete a, arete b) {
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
		
		vector<arete> Arbre(n - 1);
		int count = 0;
		int i = 0;
		while (count < n - 1) {
			arete currentArete = a[i];
			
			int src = findParent(currentArete.s, parent);
			int dest = findParent(currentArete.t, parent);
			
			if (src != dest) {
				
				d_kruskal_cfc[dest] = currentArete.s;
				d_kruskal_pilch[src] = currentArete.t;
				
				Arbre[count] = currentArete;
				count++;
				parent[src] = dest;
			}
			++i;
		}
	}
	int findParent(int v, vector<int> parent) {
		if (parent[v] == v) {
			return v;
		}
		else {
			return findParent(parent[v], parent);
		}
	}
};

class Arbre {
private:
	// FS & APS
	vector<int> d_fs;
	vector<int> d_aps;

	// MATRICE ADJACENCE
	vector<vector<int>> d_matriceAdjacence;

	// PRUFER
	// PRF
	vector<int> d_codage_prf;
	bool is_prf_encoded = false;
public :
	// CONSTRUCTEUR
	Arbre(vector<int> fs, vector<int> aps) : d_fs{ fs }, d_aps{ aps } {}
	Arbre(vector<vector<int>> matrice) : d_matriceAdjacence{ matrice } {}

	// GETTERS
	vector<int> getFS() {
		return d_fs;
	}
	vector<int> getAPS() {
		return d_aps;
	}
	vector<vector<int>> getMATRICE() {
		return d_matriceAdjacence;
	}
	vector<int> getPRF() {
		return d_codage_prf;
	}
	
	// DONE mais AFFICHAGE
	void decode_prufer() {
		if (is_prf_encoded) {
			int m = d_codage_prf[0];
			int n = m + 2;

			vector<int> arbre(n + 1, 0);

			for (int i = 1; i <= m; ++i) {
				arbre[d_codage_prf[i]]++;
			}

			for (int i = 1; i <= m; ++i) {
				cout << "[" << d_codage_prf[i];
				int k = 1;
				while (arbre[k] != 0) {
					k++;
				}
				cout << ", " << k << "]" << endl;
				arbre[k] = -1;
				arbre[d_codage_prf[i]]--;
			}

			cout << "[";
			for (int i = 1; i <= n; i++) {
				if (arbre[i] == 0) {
					cout << i << " ";
				}
			}
			cout << "]" << endl;
		}
	}

	// DONE
	void encode_prufer() {
		int n = d_matriceAdjacence[0][0];
		d_codage_prf.resize(n - 1);
		d_codage_prf[0] = n - 2;

		vector<vector<int>> matrice = d_matriceAdjacence;

		for (int i = 1; i <= n; ++i) {
			matrice[i][0] = 0;
			for(int j = 1; j <= n; ++j) {
				matrice[i][0] += matrice[i][j];
			}
		}

		for (int k = 1; k <= (n - 2); k++) {
			int i = 1;
			for (; matrice[i][0] != 1; i++);
			
			int j = 1;
			for (; matrice[i][j] != 1; j++);
			
			d_codage_prf[k] = j;
			matrice[i][j] = 0;
			matrice[j][i] = 0;
			matrice[i][0] = 0;
			matrice[j][0]--;
		}
		is_prf_encoded = true;
	}
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
	cout << "\t";
	for (int i = 1; i <= G.getNBSOMMETS(); ++i) {
		cout << i << "\t";
	}
	seperator();
}

void augmenteMatrice(vector<vector<int>>& matrice) {
	matrice.resize(matrice.size() + 1);
	int n = matrice.size();
	for (int i = 0; i < n; ++i) {
		matrice[i].resize(n, -1);
	}
	matrice[n - 1][n - 1] = 0;
}

bool Dantzig(vector<vector<int>>& c) {
	int n = c[0][0];
	int i, j, k;
	double x;
	for (k = 1; k < n; k++) {
		for (i = 1; i <= k; i++) {
			for (j = 1; j <= k; j++) {
				if ((x = c[i][j] + c[j][k + 1]) < (c[i][k + 1])) {
					c[i][k + 1] = x;
				}
				if ((x = c[k + 1][j] + c[j][i]) < (c[k + 1][i])) {
					c[k + 1][i] = x;
				}
			}
			if ((c[i][k + 1] + c[k + 1][i]) < 0) {
				printf("Présence d'un circuit absorbant passant par %d et %d \n", i, k + 1);
				return false;
			}
		}
		for (i = 1; i <= k; i++) {
			for (j = 1; j <= k; j++) {
				if ((x = c[i][k + 1] + c[k + 1][j]) < c[i][j]) {
					c[i][j] = x;
				}
			}
		}
	}
}


void main() {
	// RANG //
	
	/*
	vector<vector<int>> matrice =
	{
		{12,19,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,1,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,0,1,0},
		{0,0,0,1,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,10,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	Graphe G{ matrice };
	
	afficherSommet(G);
	
	afficher("RANG : ", G.getRANG());
	*/

	// FIN RANG //

	// DANTZIG //
	
	/*
	vector<int> fs = { 13,2,3,0,4,5,0,4,0,0,1,3,4,0 };
	vector<int> aps = { 5,1,4,7,9,10 };
	vector<vector<int>> c =
	{
		{5,8,0,0,0,0},
		{0,0,-2,4,99,99},
		{0,99,0,99,4,3},
		{0,99,99,0,1,99},
		{0,99,99,99,0,99},
		{0,0,99,-1,99,0}
	};
	
	GrapheOrienteValue G{fs, aps, c};

	G.dantzig();

	afficher("COUT : ", G.getC());
	afficher("DANTZIG : ", G.getDANTZIGC());
	*/
	
	// FIN DANTZIG //

	// DISKSTRA //
	
	/*
	vector<vector<int>> matrice =
	{
		{7,13,0,0,0,0,0,0},
		{0,0,1,1,0,1,0,1},
		{0,0,0,1,0,1,0,0},
		{0,0,0,0,0,1,1,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,1,0,0,1,0}
	};

	vector<vector<int>> c =
	{
		{7,13,0,0,0,0,0,0},
		{0,0,1,3,INT_MAX,2,INT_MAX,1},
		{0,INT_MAX,0,4,INT_MAX,1,INT_MAX,INT_MAX},
		{0,INT_MAX,INT_MAX,0,INT_MAX,3,1,INT_MAX},
		{0,INT_MAX,INT_MAX,1,0,INT_MAX,INT_MAX,INT_MAX},
		{0,INT_MAX,INT_MAX,INT_MAX,1,0,INT_MAX,INT_MAX},
		{0,INT_MAX,INT_MAX,INT_MAX,1,INT_MAX,0,INT_MAX},
		{0,INT_MAX,INT_MAX,1,INT_MAX,INT_MAX,3,0}
	};
	*/
	
	/*
	* EXEMPLE : https://www.youtube.com/watch?v=JPeCmKFrKio
	vector<vector<int>> matrice =
	{
		{5,7,0,0,0,0},
		{0,0,0,1,0,1},
		{0,1,0,1,0,0},
		{0,0,0,0,0,0},
		{0,0,1,0,0,0},
		{0,0,1,0,1,0}
	};

	vector<vector<int>> c =
	{
		{5,7,0,0,0,0},
		{0,0,INT_MAX,18,INT_MAX,3},
		{0,8,0,4,INT_MAX,INT_MAX},
		{0,INT_MAX,INT_MAX,0,INT_MAX,INT_MAX},
		{0,INT_MAX,1,INT_MAX,0,INT_MAX},
		{0,INT_MAX,10,INT_MAX,2,0}
	};
	
	GrapheOrienteValue G{ matrice, c };

	G.dijkstra(1);
	afficherSommet(G);
	afficher("D : ", G.getDIJKSTRAD());
	afficher("PRED : ", G.getDIJKSTRAPRED());
	*/
		
	// FIN DISKSTRA //

	// KRUSKAL //

	/*
	vector<vector<int>> cost =
	{
		{8,26,0,0,0,0,0,0,0},
		{0,0,1,INT_MAX,INT_MAX,2,INT_MAX,INT_MAX,INT_MAX},
		{0,1,0,2,1,1,INT_MAX,INT_MAX,INT_MAX},
		{0,0,2,0,1,INT_MAX,INT_MAX,INT_MAX,1},
		{0,INT_MAX,1,1,0,0,0,2,INT_MAX},
		{0,2,1,INT_MAX,0,0,0,INT_MAX,INT_MAX},
		{0,INT_MAX,INT_MAX,INT_MAX,0,0,0,1,INT_MAX},
		{0,INT_MAX,INT_MAX,INT_MAX,2,INT_MAX,1,0,1},
		{0,INT_MAX,INT_MAX,1,INT_MAX,INT_MAX,INT_MAX,1,0}
	};

	vector<vector<int>> matrice =
	{
		{8,26,0,0,0,0,0,0,0},
		{0,0,1,0,0,1,0,0,0},
		{0,1,0,1,1,1,0,0,0},
		{0,0,1,0,1,0,0,0,1},
		{0,0,1,1,0,1,1,1,0},
		{0,1,1,0,1,0,1,0,0},
		{0,0,0,0,1,1,0,1,0},
		{0,0,0,0,1,0,1,0,1},
		{0,0,0,1,0,0,0,1,0}
	};
	*/

	/*
	vector<vector<int>> matrice =
	{
		{4,12,0,0,0},
		{0,0,1,1,1},
		{0,1,0,1,1},
		{0,1,1,0,1},
		{0,1,1,1,0}
	};

	vector<vector<int>> cost =
	{
		{4,12,0,0,0},
		{0,0,1,1,2},
		{0,1,0,1,2},
		{0,1,1,0,2},
		{0,2,2,2,0}
	};
	
	GrapheNonOrienteValue G{ matrice, cost };

	G.kruskal();

	afficherSommet(G);

	afficher("PREM : ", G.getKRUSKALPREM());
	afficher("PILCH : ", G.getKRUSKALPILCH());
	afficher("CFC : ", G.getKRUSKALCFC());
	*/
	
	// FIN KRUSKAL //

	// PRUFER //

	
	vector<vector<int>> matrice =
	{
		{8,15,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0},
		{0,1,1,0,1,1,1,0,0},
		{0,0,0,1,0,0,0,1,1},
		{0,0,0,1,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0},
		{0,0,0,0,1,0,0,0,0}
	};

	Arbre A{ matrice };

	A.encode_prufer();
	A.decode_prufer();

	//afficher("PRF : ", A.getPRF());

	// FIN PRUFER //
}