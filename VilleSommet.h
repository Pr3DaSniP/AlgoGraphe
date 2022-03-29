#ifndef VILLESOMMET_H
#define VILLESOMMET_H

#include <iostream>
#include "Sommet.h"
#include <string>

using std::string;

class VilleSommet : public Sommet {
private:
	string m_nom;
public:
	VilleSommet(int id, string nom);

	string getNom();
	
	virtual void afficher() override;

	virtual ~VilleSommet() = default;
};

#endif // !VILLESOMMET_H
