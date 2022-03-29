#include "VilleSommet.h"

VilleSommet::VilleSommet(int id, string nom) : Sommet(id), m_nom{ nom } {}

string VilleSommet::getNom() {
	return m_nom;
}

void VilleSommet::afficher() {
	cout << m_id << " " << m_nom << endl;
}
