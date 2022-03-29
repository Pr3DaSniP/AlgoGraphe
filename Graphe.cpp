#include "Graphe.h"

Graphe::Graphe() {}

Graphe::Graphe(vector<Sommet*> fs, vector<Sommet*> aps) : m_fs{ fs }, m_aps{ aps } { FsApsToMatrice(); }

Graphe::Graphe(vector<vector<int>> matrice) : m_matrice{ matrice } {
	MatriceToFsAps();
}

void Graphe::FsApsToMatrice() {
	int nombreSommet = m_aps.size();
	int nombreArc = m_fs.size() - nombreSommet;
	m_matrice.resize(nombreSommet);

	for (int i = 0; i < nombreSommet; ++i) {
		m_matrice[i].resize(nombreSommet);
	}

	for (int i = 1; i < nombreSommet; ++i) {
		for (int j = 1; j < nombreSommet; ++j) {
			m_matrice[i][j] = 0;
		}
	}

	int k = 0;
	for (int i = 0; i < nombreSommet; ++i) {
		k = m_aps[i]->getId() - 1;
		while (m_fs[k]->getId() != -1) {
			m_matrice[i][m_fs[k]->getId() - 1] = 1;
			k++;
		}
	}
}

void Graphe::MatriceToFsAps() {
	int nombreSommet = m_matrice.size();
	int nombreArc = m_matrice[0].size();
	m_aps.resize(nombreSommet);
	m_fs.resize(nombreSommet + nombreArc);
	int k = 1;
	for (int i = 1; i <= nombreSommet; ++i) {
		m_aps[i]->setId(k);
		for (int j = 1; j <= nombreSommet; ++j) {
			if (m_matrice[i][j] != 0) {
				m_fs[k++]->setId(j);
			}
		}
		m_fs[k++]->setId(0);
	}
}

void Graphe::addSommet(Sommet* s) {
	m_fs.push_back(s);
}

int Graphe::getNbSuccesseurs() {
	//
}
void Graphe::getNbPredecesseurs() {
	//
}
void Graphe::demi_degre_ext() {
	//
}
void Graphe::demi_degre_int() {
	//
}
void Graphe::rang() {
	//
}
void Graphe::distance() {
	//
}
vector<Sommet*> Graphe::getFS() {
	return m_fs;
}
vector<Sommet*> Graphe::getAPS() {
	return m_aps;
}
vector<Sommet*> Graphe::getDDE() {
	return m_dde;
}
vector<Sommet*> Graphe::getDDI() {
	return m_ddi;
}
vector<Sommet*> Graphe::getRang() {
	return m_rang;
}
vector<Sommet*> Graphe::getDistance() {
	return m_distance;
}
vector<vector<int>> Graphe::getMatrice() {
	return m_matrice;
}

void Graphe::afficher() {
	std::cout << "FS : ";
	for (int i = 0; i < m_fs.size(); ++i) {
		std::cout << m_fs[i]->getId() << " ";
	}
	std::cout << std::endl;
	std::cout << "APS : ";
	for (int i = 0; i < m_aps.size(); ++i) {
		std::cout << m_aps[i]->getId() << " ";
	}
}