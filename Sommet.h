#ifndef SOMMET_H
#define SOMMET_H

#include <iostream>

using std::cout;
using std::endl;

class Sommet {
protected:
	int m_id;
public:
	Sommet(int id);

	int getId();
	void setId(int id);

	virtual void afficher();

	virtual ~Sommet() = default;
};

#endif // !SOMMET_H
