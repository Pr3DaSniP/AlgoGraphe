#include <iostream>
#include <vector>

using namespace std;

class Graphe {
private:
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

public:
	// CONSTRUCTEUR
	Graphe(vector<int> fs, vector<int> aps) : d_fs{ fs }, d_aps{ aps } { FS_APS_to_MATRICE(); initialisation(); }
	Graphe(vector<vector<int>> matrice) : d_matriceAdjacence{ matrice } { MATRICE_to_FS_APS(); initialisation(); }

	// GETTER
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

	void initialisation() {
		calculDDI();
		calculDDE();
		FS_APS_to_FP_APP();
		calculMatDistance();
		calculRang();
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
	void empiler(int x, vector<int>& pilch)	{
		pilch[x] = pilch[0];
		pilch[0] = x;
	}
};

void afficher(string s, vector<int> tab) {
	cout << s;
	for (int i = 0; i < tab.size(); ++i) {
		cout << tab[i] << "\t";
	}
	cout << endl;
}
void afficher(string s, vector<vector<int>> tab) {
	cout << s;
	for (int i = 0; i < tab.size(); ++i) {
		for (int j = 0; j < tab[i].size(); ++j) {
			cout << tab[i][j] << "\t";
		}
		cout << endl;
	}
}

void main() {
	
	vector<int> fs = { 12,2,3,0,4,5,0,2,4,0,5,0,0 };
	vector<int> aps = { 5,1,4,7,10,11 };

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
	//Graphe G{ matrice };
	cout << "\n=============================\n";
	for (int i = 0; i <= G.getNBSOMMETS(); ++i) {
		cout << i << "\t";
	}
	cout << "\n=============================\n";

	afficher("Mat : \n", G.getMATRICEADJACENCE());
	cout << "\n=============================\n";

	afficher("Rang : \n", G.getRANG());

}