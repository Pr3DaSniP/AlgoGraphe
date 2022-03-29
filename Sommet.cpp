#include "Sommet.h"

Sommet::Sommet(int id) : m_id{ id } {}

int Sommet::getId() {
	return m_id;
}
void Sommet::setId(int id) {
	m_id = id;
}

void Sommet::afficher() {
	cout << m_id << endl;
}