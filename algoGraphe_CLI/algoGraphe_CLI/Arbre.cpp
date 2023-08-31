#include "Arbre.h"

#include <iostream>

using std::cout;
using std::endl;

void Arbre::initialisation() {
	d_is_prf_encoded = false;
}

Arbre::Arbre(vector<int> fs, vector<int> aps) : GrapheNonOriente(fs, aps) { initialisation(); }

Arbre::Arbre(vector<vector<int>> matrice) : GrapheNonOriente(matrice) { initialisation(); }

vector<int> Arbre::getPRUFER_CODE() {
	return d_codage_prf;
}

bool Arbre::is_prf_encoded() {
	return d_is_prf_encoded;
}

void Arbre::decode_prufer() {
	if (d_is_prf_encoded) {
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
		d_is_prf_encoded = false;
	}
}

void Arbre::encode_prufer() {
	int n = d_matriceAdjacence[0][0];
	d_codage_prf.resize(n - 1);
	d_codage_prf[0] = n - 2;

	vector<vector<int>> matrice = d_matriceAdjacence;

	for (int i = 1; i <= n; ++i) {
		matrice[i][0] = 0;
		for (int j = 1; j <= n; ++j) {
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
	d_is_prf_encoded = true;
}
